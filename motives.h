// motives.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef MOTIVES_H
#define MOTIVES_H

#include "entity.h"
#include "entity_definitions.h"

typedef enum {
    MOTIVE_SELF_PRESERVATION,
    MOTIVE_GROUP_SAFETY,
    MOTIVE_GOAL_PROGRESS,
    MOTIVE_RESOURCES,
    MOTIVE_STATUS,
    MOTIVE_TERRITORY,
    MOTIVE_MALEVOLENCE,
    MOTIVE_OBEDIENCE,
    MOTIVE_HUNGER,
    MOTIVE_DOMINANCE,
    MOTIVE_ALTRUISM,
    MOTIVE_GREED,
    MOTIVE_CURIOSITY,
    MOTIVE_VENGEANCE,
    MOTIVE_KINSHIP,
    MOTIVE_FREEDOM,
    MOTIVE_HONOR,
    MOTIVE_PAIN_AVOIDANCE,
    MOTIVE_COUNT
} MOTIVE_TYPE; 

typedef struct {
    float weight[MOTIVE_COUNT];
} Motives;

// Motive_State.state[] should range from 0.0f to 1.0f, 0.0 = fully unsatisfied, 1.0 = fully satisfied
typedef struct {
    float state[MOTIVE_COUNT];
} Motive_State;

// Difference between two valid Motive_State values
// -1.0 = maximum negative change, 0.0 = no change, 1.0 = maximum positive change
typedef struct {
    float delta[MOTIVE_COUNT];
} Motive_Delta;

const Motives *getMotives(Entity entity);
int getMotiveType(const char *name, MOTIVE_TYPE *type);
const char *getMotiveName(int type);
int initMotives(Entity entity, const Entity_Definition_Component *component);

float motivesGetReward(const Motives *motives, const Motive_State *before, const Motive_State *after);
void motivesEvaluateState(int health, int maxHealth, float threat, Motive_State *state);

#endif
