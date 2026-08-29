// component.c
//
// Copyright (c) 2026 - oldmansutton
//

#include <string.h>
#include "component.h"
#include "entity_definitions.h"
#include "health.h"
#include "attributes.h"

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

int initComponents(Entity entity, const Entity_Definition *definition) {
    int i;

    for (i = 0; i < definition->componentCount; i++) {
        switch (definition->components[i].type) {
            case COMPONENT_HEALTH:
                if (initHealth(entity, &definition->components[i])) {
                    addComponent(entity, COMPONENT_HEALTH);
                } else {
                    return 0;
                }
                break;
            case COMPONENT_ATTRIBUTES:
                if (initAttributes(entity, &definition->components[i])) {
                    addComponent(entity, COMPONENT_ATTRIBUTES);
                } else {
                    return 0;
                }
                break;
            default:
                break;
        }
    }
    return 1;
}
