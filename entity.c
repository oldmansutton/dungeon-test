// entity.c
//
// Copyright (c) 2026 - ryan sutton
//

static Entity nextEntity = 2;
static const Entity_Definition *entityDefinitions[ENTITY_MAX + 1] = {0};

const Entity_Definition *getEntityDefinitionForEntity(Entity entity) {
    return &entityDefinitions[entity];
}

Entity createEntity(const Entity_Definition *definition)
{
    Entity entity;

    if (!definition) return ENTITY_NONE;
    if (nextEntity > ENTITY_MAX) return ENTITY_NONE;
    entity = nextEntity;
    nextEntity++;
    if (!initComponents(entity, definition)) {
        removeAllComponents(entity);
        return ENTITY_NONE;
    }
    entityDefinitions[entity] = definition;
    return entity;
}
