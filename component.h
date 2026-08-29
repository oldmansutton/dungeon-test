// component.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include "entity.h"

typedef enum {
    COMPONENT_POSITION,
    COMPONENT_HEALTH,
    COMPONENT_ATTRIBUTES,
    COMPONENT_MOTIVES,
    COMPONENT_GENOME,
    COMPONENT_NEURAL,
    COMPONENT_COUNT
} COMPONENT_TYPE;

typedef struct {
    const char *name;
    COMPONENT_TYPE type;
} Component_Type_Name;

static const Component_Type_Name componentTypeNames[] = {
    {"POSITION", COMPONENT_POSITION},
    {"HEALTH", COMPONENT_HEALTH},
    {"ATTRIBUTES", COMPONENT_ATTRIBUTES},
    {"MOTIVES", COMPONENT_MOTIVES},
    {"GENOME", COMPONENT_GENOME},
    {"NEURAL", COMPONENT_NEURAL}
};

int componentHas(Entity entity, COMPONENT_TYPE component);
void componentAdd(Entity entity, COMPONENT_TYPE component);
void componentRemove(Entity entity, COMPONENT_TYPE component);
void componentRemoveAll(Entity entity);
int getComponentType(const char *name, COMPONENT_TYPE *type);

#endif
