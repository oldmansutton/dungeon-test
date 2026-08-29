// entity.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef ENTITY_H
#define ENTITY_H

#define ENTITY_NONE 0
#define ENTITY_PLAYER_CHARACTER 1
#define ENTITY_MAX 4096

typedef unsigned int Entity;

typedef struct Entity_Definition Entity_Definition;

const Entity_Definition *getEntityDefinitionForEntity(Entity entity);
Entity createEntity(const Entity_Definition *definition);

#endif
