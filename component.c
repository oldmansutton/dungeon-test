// component.c
//
// Copyright (c) 2026 - oldmansutton
//

#include "component.h"

static unsigned char components[ENTITY_MAX + 1][COMPONENT_COUNT] = {0};

int componentHas(Entity entity, COMPONENT_TYPE component) {
    return components[entity][component];
}

void componentAdd(Entity entity, COMPONENT_TYPE component) {
    components[entity][component] = 1;
}

void componentRemove(Entity entity, COMPONENT_TYPE component) {
    components[entity][component] = 0;
}

void componentRemoveAll(Entity entity) {
    int i;

    for (i = 0; i < COMPONENT_COUNT; i++) {
        components[entity][i] = 0;
    }
}
