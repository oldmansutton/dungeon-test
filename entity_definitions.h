// entity_definitions.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef ENTITY_DEFINITION_H
#define ENTITY_DEFINITION_H

#include "component.h"

#define ENTITY_DEFINITION_MAX_ENTRIES 64
#define ENTITY_DEFINITION_MAX_ARGUMENTS 8
#define ENTITY_DEFINITION_TOKEN_LENGTH 32
#define ENTITY_DEFINITION_ARGUMENT_LENGTH 64

typedef struct {
    char token[ENTITY_DEFINITION_TOKEN_LENGTH];
    char arguments[ENTITY_DEFINITION_MAX_ARGUMENTS][ENTITY_DEFINITION_ARGUMENT_LENGTH];
    int argumentCount;
} Entity_Definition_Entry;

typedef struct {
    unsigned char components[COMPONENT_COUNT];
    Entity_Definition_Entry entries[ENTTY_DEFINITION_MAX_ENTRIES];
    int entryCount;
} Entity_Definition;

void entityDefinitionAddComponent(Entity_Definition *definition, COMPONENT_TYPE component);
int entityDefinitionHasComponent(const Entity_Definition *definition, COMPONENT_TYPE component);

#endif
