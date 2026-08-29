// component.c
//
// Copyright (c) 2026 - oldmansutton
//

#include <string.h>
#include "component.h"

static unsigned char components[ENTITY_MAX + 1][COMPONENT_COUNT] = {0};

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

int hasComponent(Entity entity, COMPONENT_TYPE component) {
    return components[entity][component];
}

void addComponent(Entity entity, COMPONENT_TYPE component) {
    components[entity][component] = 1;
}

void removeComponent(Entity entity, COMPONENT_TYPE component) {
    components[entity][component] = 0;
}

void removeAllComponents(Entity entity) {
    int i;

    for (i = 0; i < COMPONENT_COUNT; i++) {
        components[entity][i] = 0;
    }
}

int getComponentType(const char *name, COMPONENT_TYPE *type)
{
    int i;

    for (i = 0; i < COMPONENT_COUNT; i++) {
        if (strcmp(name, componentTypeNames[i].name) == 0) {
            *type = componentTypeNames[i].type;
            return 1;
        }
    }
    return 0;
}

void initComponents(Entity entity, Entity_Definition *definition) {
    int i;

    for (i = 0; i < definition->componentCount; i++) {
        switch (definition->components[i].type) {
            case COMPONENT_HEALTH:
                addComponent(entity, COMPONENT_HEALTH);
                initHealth(entity, &definition->components[i]);
                break;
            default:
                break;
        }
    }
}
