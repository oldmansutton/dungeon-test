#include <stdio.h>
#include "entity_definitions.h"

int main(void)
{
    const Entity_Definition *definition;
    int i;
    int j;
    int k;

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

    return 0;
}
