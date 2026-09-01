// motives.c
//
// Copyright (c) 2026 - oldmansutton
//

#include <stdio.h>
#include <string.h>
#include "motives.h"
#include "helper.h"

static Motives motives[ENTITY_MAX + 1] = {0};

typedef struct {
    const char *name;
    MOTIVE_TYPE type;
} Motive_Type_Name;

static const Motive_Type_Name motiveTypeNames[] = {
    {"SELF_PRESERVATION", MOTIVE_SELF_PRESERVATION},
    {"GROUP_SAFETY", MOTIVE_GROUP_SAFETY},
    {"GOAL_PROGRESS", MOTIVE_GOAL_PROGRESS},
    {"RESOURCES", MOTIVE_RESOURCES},
    {"STATUS", MOTIVE_STATUS},
    {"TERRITORY", MOTIVE_TERRITORY},
    {"MALEVOLENCE", MOTIVE_MALEVOLENCE},
    {"OBEDIENCE", MOTIVE_OBEDIENCE},
    {"HUNGER", MOTIVE_HUNGER},
    {"DOMINANCE", MOTIVE_DOMINANCE},
    {"ALTRUISM", MOTIVE_ALTRUISM},
    {"GREED", MOTIVE_GREED},
    {"CURIOSITY", MOTIVE_CURIOSITY},
    {"VENGEANCE", MOTIVE_VENGEANCE},
    {"KINSHIP", MOTIVE_KINSHIP},
    {"FREEDOM", MOTIVE_FREEDOM},
    {"HONOR", MOTIVE_HONOR},
    {"PAIN_AVOIDANCE", MOTIVE_PAIN_AVOIDANCE}
};

static void clamp(float min, float max, float *value) {
    if (*value < min) {
        *value = min;
    } else if (*value > max) {
        *value = max;
    }
} 

const Motives *getMotives(Entity entity)
{
    if (!hasComponent(entity, COMPONENT_MOTIVES)) {
        return NULL;
    }
    return &motives[entity];
}

int getMotiveType(const char *name, MOTIVE_TYPE *type)
{
    int i;

    for (i = 0; i < MOTIVE_COUNT; i++) {
        if (strcmp(name, motiveTypeNames[i].name) == 0) {
            *type = motiveTypeNames[i].type;
            return 1;
        }
    }
    return 0;
}

int initMotives(Entity entity, const Entity_Definition_Component *component)
{
    MOTIVE_TYPE type;
    float minWeight, maxWeight, weight;

    if (component->argumentCount < 2 || component->argumentCount > 3) {
        return 0;
    }
    if (!getMotiveType(component->arguments[0], &type)) {
        return 0;
    }
    if (!parseFloat(component->arguments[1], &minWeight)) {
        return 0;
    }
    clamp(0.0f, 1.0f, &minWeight);
    if (component->argumentCount == 2) {
        weight = minWeight;
    } else {
        if (!parseFloat(component->arguments[2], &maxWeight)) {
            return 0;
        }

        if (minWeight > maxWeight) {
            float temp = minWeight;
            minWeight = maxWeight;
            maxWeight = temp;
        }

        weight = randFloat(minWeight, maxWeight);
    }
    if (weight < 0.0f || weight > 1.0f) {
        return 0;
    }
    motives[entity].weight[type] = weight;
    return 1;
}

float motivesGetReward(const Motives *motives, const Motive_State *before, const Motive_State *after) {
    int i;
    float reward = 0.0f;

    for (i = 0; i < MOTIVE_COUNT; i++) {
        reward += (after->state[i] - before->state[i]) * motives->weight[i];
    }

    return reward;
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
