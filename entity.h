// entity.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef ENTITY_H
#define ENTITY_H

#define ENTITY_NONE 0
#define ENTITY_PLAYER 1
#define ENTITY_MAX 4096

typedef unsigned int Entity;

const Entity_Definition *getEntityDefinitionForEntity(Entity entity);

#endif
