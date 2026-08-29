// entity_definitions.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef ENTITY_DEFINITION_H
#define ENTITY_DEFINITION_H

#include "component.h"

#define ENTITY_DEFINITION_MAX_COMPONENTS 32
#define ENTITY_DEFINITION_MAX_ARGUMENTS 32
#define ENTITY_DEFINITION_NAME_LENGTH 32
#define ENTITY_DEFINITION_ARGUMENT_LENGTH 32

typedef struct {
    COMPONENT_TYPE type;
    char arguments[ENTITY_DEFINITION_MAX_ARGUMENTS][ENTITY_DEFINITION_ARGUMENT_LENGTH];
    int argumentCount;
} Entity_Definition_Component;

typedef struct Entity_Definition {
    char name[ENTITY_DEFINITION_NAME_LENGTH];
    Entity_Definition_Component components[ENTITY_DEFINITION_MAX_COMPONENTS];
    int componentCount;
} Entity_Definition;

void loadEntityDefinitions(const char *path);
int getEntityDefinitionCount(void);
const Entity_Definition *getEntityDefinition(int index);
const Entity_Definition *getEntityDefinitionByName(const char *name);

#endif
