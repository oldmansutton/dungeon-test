#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entity_definitions.h"
#include "entity.h"
#include "component.h"
#include "health.h"
#include "attributes.h"
#include "motives.h"

int main(void)
{
    const Entity_Definition *definition;
    int i;
    int j;
    int k;

    srand(time(NULL));

    loadEntityDefinitions("data/entities");

    printf("Definitions loaded: %d\n", getEntityDefinitionCount());

    for (i = 0; i < getEntityDefinitionCount(); i++) {
        definition = getEntityDefinition(i);

        printf("\nEntity: %s\n", definition->name);
        printf("Components: %d\n", definition->componentCount);

        for (j = 0; j < definition->componentCount; j++) {
            printf("  Component type: %d\n", definition->components[j].type);

            for (k = 0; k < definition->components[j].argumentCount; k++) {
                printf("    Arg %d: %s\n",
                    k,
                    definition->components[j].arguments[k]);
            }
        }
    }

    Entity tmpEntity[3];
    const Entity_Definition *goblinDefinition = getEntityDefinition(0);
    const Entity_Definition *orcDefinition = getEntityDefinition(1);
    const Entity_Definition *ogreDefinition = getEntityDefinition(2);
    tmpEntity[0] = createEntity(goblinDefinition);
    tmpEntity[1] = createEntity(orcDefinition);
    tmpEntity[2] = createEntity(ogreDefinition);
    const Health *entityHealth;
    const Attributes *entityAttributes;
    const Motives *entityMotives;
    
    for (i = 0; i < 3; i++) {
        Entity curEntity;
        curEntity = tmpEntity[i];

        printf("\nInitializing entity %d from %s\n", curEntity, getEntityDefinitionForEntity(curEntity)->name);
        printf("Has health: %d\n", hasComponent(curEntity, COMPONENT_HEALTH));

        entityHealth = getHealth(curEntity);
        if (entityHealth) {
            printf("Current health: %d\n", entityHealth->currentHealth);
            printf("Max health: %d\n", entityHealth->maxHealth);
        }

        entityAttributes = getAttributes(curEntity);
        if (entityAttributes) {
            printf("Attributes: \n");
            printf("  STR: %d\n", entityAttributes->strength);
            printf("  DEX: %d\n", entityAttributes->dexterity);
            printf("  CON: %d\n", entityAttributes->constitution);
            printf("  INT: %d\n", entityAttributes->intelligence);
            printf("  WIS: %d\n", entityAttributes->wisdom);
            printf("  RES: %d\n", entityAttributes->resolve);
            printf("  PRE: %d\n", entityAttributes->presence);
            printf("  CHA: %d\n", entityAttributes->charisma);
            printf("  NRV: %d\n", entityAttributes->nerve);
            printf("  LUC: %d\n", entityAttributes->luck);        
        }

        entityMotives = getMotives(curEntity);
        if (entityMotives) {
            printf("Motives: \n");
            for (i = 0; i < MOTIVE_COUNT; i++) {
                printf("  %s: %f\n", getMotiveName(i), entityMotives->weight[i]);
            }
        }
    }
    return 0;
}
