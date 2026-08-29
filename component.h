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

int hasComponent(Entity entity, COMPONENT_TYPE component);
void addComponent(Entity entity, COMPONENT_TYPE component);
void removeComponent(Entity entity, COMPONENT_TYPE component);
void removeAllComponents(Entity entity);
int getComponentType(const char *name, COMPONENT_TYPE *type);

#endif
