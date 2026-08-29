// position.c
//
// Copyright (c) 2026 - oldmansutton
// 

#include <stddef.h>
#include "position.h"
#include "component.h"

static Position positions[ENTITY_MAX + 1] = {0};

Position *positionGet(Entity entity) {
    if (!hasComponent(entity, COMPONENT_POSITION)) {
        return NULL;
    }
    return &positions[entity];
}

void addPosition(Entity entity, int x, int y) {
    positions[entity].x = x;
    positions[entity].y = y;
    addComponent(entity, COMPONENT_POSITION);
}

void removePosition(Entity entity) {
    removeComponent(entity, COMPONENT_POSITION);
    positions[entity] = (Position){0};
}
