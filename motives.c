// motives.c
//
// Copyright (c) 2026 - oldmansutton
//

#include "motives.h"

float motivesGetReward(const Motives *motives, const Motive_State *before, const Motive_State *after) {
    int i;
    float reward = 0.0f;

    for (i = 0; i < MOTIVE_COUNT; i++) {
        reward += (after->state[i] - before->state[i]) * motives->weight[i];
    }

    return reward;
}

static void clamp(float min, float max, float *value) {
    if (*value < min) {
        *value = min;
    } else if (*value > max) {
        *value = max;
    }
} 

static float motivesEvaluateSelfPreservation(int health, int maxHealth, float threat) {
    float healthState, safetyState;

    healthState = maxHealth > 0 ? (float)health / (float)maxHealth : 0.0f;
    clamp(0.0f, 1.0f, &healthState);
    clamp(0.0f, 1.0f, &threat); 
    safetyState = 1.0f - threat;
    return healthState * safetyState;    
}

void motivesEvaluateState(int health, int maxHealth, float threat, Motive_State *state) {
    int i;

    for (i = 0; i < MOTIVE_COUNT; i++) {
        state->state[i] = 0.0f;
    }

    state->state[MOTIVE_SELF_PRESERVATION] = motivesEvaluateSelfPreservation(health, maxHealth, threat);
}
