#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "motives.h"


int main(void) {
    Motives motives = {0};
    Motive_State before;
    Motive_State after;
    motives.weight[MOTIVE_SELF_PRESERVATION] = 2.0f;
    motivesEvaluateState(100, 100, 0.0f, &before);
    motivesEvaluateState(100, 100, 0.5f, &after);
    printf("Reward: %f\n", motivesGetReward(&motives, &before, &after));
    return 0;
}

