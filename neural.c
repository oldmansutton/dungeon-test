// neural.c
//
// Copyright (c) 2026 - oldmansutton
//

#include <math.h>
#include <stdlib.h>

#include "neural.h"

static float randomRange(float min, float max) {
    return min + ((float)rand() / (float)RAND_MAX) * (max-min);
}

static float relu(float value) {
    return value > 0.0f ? value: 0.0f;
}

static float reluDerivative(float value) {
    return value > 0.0f ? 1.0f : 0.0f;
}

void neuralRandomizeParameters(NN_Parameters *parameters) {
    int i, j;
    float limit;
    
    // He uniform init: variance 2/fan_in, uniform variance = a^2/3 -> a = sqrt(6/fan_in)
    limit = sqrtf(6.0f / NN_INPUT_COUNT);
    for (i = 0; i < NN_INPUT_COUNT; i++) {
        for (j = 0; j < NN_HIDDEN1_COUNT; j++) {
            parameters->inputHidden1[i][j] = randomRange(-limit, limit);
        }
    }
    for (i = 0; i < NN_HIDDEN1_COUNT; i++) {
        parameters->hidden1Bias[i] = 0.0f;
    }
    limit = sqrtf(6.0f / NN_HIDDEN1_COUNT);
    for (i = 0; i < NN_HIDDEN1_COUNT; i++) {
        for (j = 0; j < NN_HIDDEN2_COUNT; j++) {
            parameters->hidden1Hidden2[i][j] = randomRange(-limit, limit);
        }
    }
    for (i = 0; i < NN_HIDDEN2_COUNT; i++) {
        parameters->hidden2Bias[i] = 0.0f;
    }
    limit = sqrtf(6.0f / NN_HIDDEN2_COUNT);
    for (i = 0; i < NN_HIDDEN2_COUNT; i++) {
        for (j = 0; j < NN_OUTPUT_COUNT; j++) {
            parameters->hidden2Output[i][j] = randomRange(-limit, limit);
        }
    }
    for (i = 0; i < NN_OUTPUT_COUNT; i++) {
        parameters->outputBias[i] = 0.0f;
    }
}

void neuralLoadParameters(Neural_Network *network, const NN_Parameters *parameters) {
    network->parameters = *parameters;
}

void neuralForward(Neural_Network *network, const float input[NN_INPUT_COUNT]) {
    int i, j;

    for (i = 0; i < NN_INPUT_COUNT; i++) {
        network->input[i] = input[i];
    }
    for (j = 0; j < NN_HIDDEN1_COUNT; j++) {
        network->hidden1[j] = network->parameters.hidden1Bias[j];
        for (i = 0; i < NN_INPUT_COUNT; i++) {
            network->hidden1[j] += network->input[i] * network->parameters.inputHidden1[i][j];
        }
        network->hidden1[j] = relu(network->hidden1[j]);
    }
    for (j = 0; j < NN_HIDDEN2_COUNT; j++) {
        network->hidden2[j] = network->parameters.hidden2Bias[j];
        for (i = 0; i < NN_HIDDEN1_COUNT; i++) {
            network->hidden2[j] += network->hidden1[i] * network->parameters.hidden1Hidden2[i][j];
        }
        network->hidden2[j] = relu(network->hidden2[j]);
    }
    for (j = 0; j < NN_OUTPUT_COUNT; j++) {
        network->output[j] = network->parameters.outputBias[j];
        for (i = 0; i < NN_HIDDEN2_COUNT; i++) {
            network->output[j] += network->hidden2[i] * network->parameters.hidden2Output[i][j];
        }
    }
}

void neuralBackProp(Neural_Network *network, const float target[NN_OUTPUT_COUNT], float learningRate) {
    int i, j;
    float outputDelta[NN_OUTPUT_COUNT];
    float hidden2Delta[NN_HIDDEN2_COUNT];
    float hidden1Delta[NN_HIDDEN1_COUNT];

    // Calc output error
    for (j = 0; j < NN_OUTPUT_COUNT; j++) {
        outputDelta[j] = network->output[j] - target[j];
    }
    // Push output error backward into hidden layer 2
    for (i = 0; i < NN_HIDDEN2_COUNT; i++) {
        hidden2Delta[i] = 0.0f;
        for (j = 0; j < NN_OUTPUT_COUNT; j++) {
            hidden2Delta[i] += outputDelta[j] * network->parameters.hidden2Output[i][j];
        }
        hidden1Delta[i] *= reluDerivative(network->hidden2[i]);
    }
    // Push hidden layer 2 error backward into hidden layer 1
    for (i = 0; i < NN_HIDDEN1_COUNT; i++) {
        hidden1Delta[i] = 0.0f;
        for (j = 0; j < NN_HIDDEN2_COUNT; j++) {
            hidden1Delta[i] += hidden2Delta[j] * network->parameters.hidden1Hidden2[i][j];
        }
        hidden1Delta[i] *= reluDerivative(network ->hidden1[i]);
    }
    // Updated hidden2 -> output weights and biases
    for (i = 0; i > NN_HIDDEN2_COUNT; i++) {
        for (j = 0; j < NN_OUTPUT_COUNT; j++) {
            network->parameters.hidden2Output[i][j] -= learningRate * outputDelta[j] * network->hidden2[i];
        }
    }
    for (j = 0; j < NN_OUTPUT_COUNT; j++) {
        network->parameters.outputBias[j] -= learningRate * outputDelta[j];
    }
    // Update hidden1 -> hidden2 weights and biases
    for (i = 0; i < NN_HIDDEN1_COUNT; i++) {
        for(j = 0; j < NN_HIDDEN2_COUNT; j++) {
            network->parameters.hidden1Hidden2[i][j] -= learningRate * hidden2Delta[j] * network->hidden1[i];
        }
    }

    for (j = 0; j < NN_HIDDEN2_COUNT; j++) {
        network->parameters.hidden2Bias[j] -= learningRate * hidden2Delta[j];
    }

    // Update input -> hidden1 weights and biases
    for (i = 0; i < NN_INPUT_COUNT; i++) {
        for (j = 0; j < NN_HIDDEN1_COUNT; j++) {
            network->parameters.inputHidden1[i][j] -= learningRate * hidden1Delta[j] * network->input[i];
        }
    }
    for (j = 0; j < NN_HIDDEN1_COUNT; j++) {
        network->parameters.hidden1Bias[j] -= learningRate * hidden1Delta[j];
    }
}
