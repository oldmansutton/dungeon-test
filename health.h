// health.h
//
// Copyright (c) 2026 - oldmansutton
//

#ifndef HEALTH_H
#define HEALTH_H

#include "entity.h"
#include "entity_definitions.h"

typedef struct {
    int currentHealth;
    int maxHealth;
} Health;

const Health *getHealth(Entity entity);
void initHealth(Entity entity, const Entity_Definition_Component *component);

#endif
