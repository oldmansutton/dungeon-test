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

int componentHas(Entity entity, COMPONENT_TYPE component);
void componentAdd(Entity entity, COMPONENT_TYPE component);
void componentRemove(Entity entity, COMPONENT_TYPE component);
void componentRemoveAll(Entity entity);

#endif
