// health.c
//
// Copyright (c) 2026 - Ryan Sutton
//

#include <stdio.h>
#include <stdlib.h>
#include "health.h"

static Health health[ENTITY_MAX + 1] = {0};

static int getRandomHealth(int minHealth, int maxHealth) {
    return (rand() % maxHealth) + minHealth;
}

const Health *getHealth(Entity entity)
{
    if (!hasComponent(entity, COMPONENT_HEALTH)) {
        return NULL;
    }
    return &health[entity];
}

// in future, extend arguments to accept genome information as well, or separate initHealthFromGenetics
void initHealth(Entity entity, const Entity_Definition_Component *component)
{
    int entityHealth;
    int tmpArg;
    
    if (component->argumentCount <> 2) {
        printf("Could not initialize health for entity %d\n", entity);
        printf("Expected 2 arguments, received %d\n", component->argumentCount);
        return;
    }
    if (component->arguments[0] > component->arguments[1]) {
        tmpArg = component->arguments[0];
        component->arguments[0] = component->arguments[1];
        component->arguments[1] = tmpArg;
    }
    entityHealth = getRandomHealth(component->arguments[0], component->arguments[1]);
    health[entity]->currentHealth = entityHealth;
    health[entity]->maxHealth = entityHealth;
    return;
}
