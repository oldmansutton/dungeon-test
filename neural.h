// neural.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef NEURAL_H
#define NEURAL_H

#define NN_INPUT_COUNT      12
#define NN_HIDDEN1_COUNT    12
#define NN_HIDDEN2_COUNT    6
#define NN_OUTPUT_COUNT     6

typedef struct {
    float inputHidden1[NN_INPUT_COUNT][NN_HIDDEN1_COUNT];
    float hidden1Bias[NN_HIDDEN1_COUNT];

    float hidden1Hidden2[NN_HIDDEN1_COUNT][NN_HIDDEN2_COUNT];
    float hidden2Bias[NN_HIDDEN2_COUNT];

    float hidden2Output[NN_HIDDEN2_COUNT][NN_OUTPUT_COUNT];
    float outputBias[NN_OUTPUT_COUNT];
} NN_Parameters;

typedef struct {
    NN_Parameters parameters;
    
    float input[NN_INPUT_COUNT];
    float hidden1[NN_HIDDEN1_COUNT];
    float hidden2[NN_HIDDEN2_COUNT];
    float output[NN_OUTPUT_COUNT];
} Neural_Network;

void neuralRandomizeParameters(NN_Parameters *parameters);
void neuralLoadParameters(Neural_Network *network, const NN_Parameters *parameters);
void neuralForward(Neural_Network *network, const float input[NN_INPUT_COUNT]);
void neuralBackProp(Neural_Network *network, const float target[NN_OUTPUT_COUNT], float learningRate);

#endif
