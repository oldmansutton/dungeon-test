#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entity_definitions.h"
#include "component.h"
#include "health.h"
#include "attributes.h"

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

    Entity entity = 1;
    const Health *entityHealth;
    const Attributes *entityAttributes;

    definition = getEntityDefinition(0);

    printf("\nInitializing entity %d from %s\n", entity, definition->name);

    initComponents(entity, definition);

    printf("Has health: %d\n", hasComponent(entity, COMPONENT_HEALTH));

    entityHealth = getHealth(entity);
    if (entityHealth) {
        printf("Current health: %d\n", entityHealth->currentHealth);
        printf("Max health: %d\n", entityHealth->maxHealth);
    }

    entityAttributes = getAttributes(entity);
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
    return 0;
}
