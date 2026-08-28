// entity_definitions.c
//
// Copyright (c) 2026 - oldmansutton
//

#include "entity_definitions.h"

void entityDefinitionAddComponent(Entity_Definition *definition, COMPONENT_TYPE component) {
    definition->components[component] = 1;
}

int entityDefinitionHasComponent(const Entity_Definition * definition, COMPONENT_TYPE component) {
    return definition->components[component];
}
