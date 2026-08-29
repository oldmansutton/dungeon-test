// health.c
//
// Copyright (c) 2026 - Ryan Sutton
//

#include <stdio.h>
#include <stdlib.h>
#include "health.h"
#include "helper.h"

static Health health[ENTITY_MAX + 1] = {0};

const Health *getHealth(Entity entity)
{
    if (!hasComponent(entity, COMPONENT_HEALTH)) {
        return NULL;
    }
    return &health[entity];
}

// in future, extend arguments to accept genome information as well, or separate initHealthFromGenetics
int initHealth(Entity entity, const Entity_Definition_Component *component)
{
    int entityHealth;
    int minHealth, maxHealth;
    int tmpArg;
    
    if (component->argumentCount != 2) {
        printf("Could not initialize health for entity %d\n", entity);
        printf("Expected 2 arguments, received %d\n", component->argumentCount);
        return 0;
    }
    if (!parseInt(component->arguments[0], &minHealth) || !parseInt(component->arguments[1], &maxHealth)) {
        printf("Could not initialize health for entity %d\n", entity);
        printf("Health arguments must be integers\n");
        return 0;
    }
    if (minHealth > maxHealth) {
        tmpArg = minHealth;
        minHealth = maxHealth;
        maxHealth = tmpArg;
    }
    entityHealth = randr(minHealth, maxHealth);
    health[entity].currentHealth = entityHealth;
    health[entity].maxHealth = entityHealth;
    return 1;
}
