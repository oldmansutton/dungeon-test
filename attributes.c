// attributes.c
//
// Copyright (c) 2026 - Ryan Sutton
//

#include <stdio.h>
#include <stdlib.h>
#include "attributes.h"
#include "helper.h"

static Attributes attributes[ENTITY_MAX + 1] = {0};

const Attributes *getAttributes(Entity entity)
{
    if (!hasComponent(entity, COMPONENT_ATTRIBUTES)) {
        return NULL;
    }
    return &attributes[entity];
}

int initAttributes(Entity entity, const Entity_Definition_Component *component)
{
    int i;
    int minAttribute, maxAttribute;
    int tmpArg;
    int attribute = 0;
    int *attributeFields[] = {
        &attributes[entity].strength,
        &attributes[entity].dexterity,
        &attributes[entity].constitution,
        &attributes[entity].intelligence,
        &attributes[entity].wisdom,
        &attributes[entity].resolve,
        &attributes[entity].presence,
        &attributes[entity].charisma,
        &attributes[entity].nerve,
        &attributes[entity].luck
    };
    
    if (component->argumentCount != 20) {
        printf("Could not initialize attributes for entity %d\n", entity);
        printf("Expected 20 arguments, received %d\n", component->argumentCount);
        return 0;
    }
    for (i = 0; i < 20; i += 2) {
        if (!parseInt(component->arguments[i], &minAttribute) || !parseInt(component->arguments[i + 1], &maxAttribute)) {
            printf("Could not initialize attributes for entity %d\n", entity);
            printf("Attributes arguments must be integers\n");
            return 0;
        }
        if (minAttribute > maxAttribute) {
            tmpArg = minAttribute;
            minAttribute = maxAttribute;
            maxAttribute = tmpArg;
        }
        *attributeFields[attribute] = randr(minAttribute, maxAttribute);
        attribute++;
    }
    return 1;
}
