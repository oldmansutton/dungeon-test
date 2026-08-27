// neural.c
//
// Copyright (c) 2026 - oldmansutton
//

#include "neural.h"

static float relu(float value) {
    return value > 0.0f ? value: 0.0f;
}

void neuralLoadParameters(Neural_Network *network, const NN_Parameters *parameters) {
    netowrk->parameters = *parameters;
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
        for (i = 0; i < NN_OUTPUT_COUNT; i++) {
            network->output[j] += network->hidden2[i] * network->parameters.hidden2Output[i][j];
        }
    }
}
