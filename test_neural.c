#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "neural.h"


int main(void) {
    NN_Parameters parameters;
    Neural_Network network;

    float input[NN_INPUT_COUNT] = {
        0
    };

    float target[NN_OUTPUT_COUNT] = {
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };

    srand(1);

    neuralRandomizeParameters(&parameters);
    neuralLoadParameters(&network, &parameters);
   
    for (int i = 0; i < 1000; i++) {
        neuralForward(&network, input);
        neuralBackProp(&network, target, 0.01f);
    }


    neuralForward(&network, input);

    for (int i = 0; i < NN_OUTPUT_COUNT; i++) {
        printf("Output %d: %f\n", i, network.output[i]);
    }

    return 0;
}

