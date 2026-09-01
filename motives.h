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
    float state[MOTIVE_COUNT];
} Motives;

const Motives *getMotives(Entity entity);
int getMotiveType(const char *name, MOTIVE_TYPE *type);
const char *getMotiveName(int type);
int initMotives(Entity entity, const Entity_Definition_Component *component);


#endif
