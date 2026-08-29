// entity_definitions.c
//
// Copyright (c) 2026 - oldmansutton
//

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "entity_definitions.h"

#define ENTITY_DEFINITION_MAX 256

typedef enum {
    ENTITY_PARSE_ERROR,
    ENTITY_PARSE_IGNORE,
    ENTITY_PARSE_COMPONENT,
    ENTITY_PARSE_NEW_ENTITY
} ENTITY_PARSE_RESULT;

static Entity_Definition entityDefinitions[ENTITY_DEFINITION_MAX] = {0};
static int entityDefinitionCount = 0;

static int registerEntityDefinition(const Entity_Definition *definition)
{
    if (!definition || definition->name[0] == '\0') {
        return 0;
    }
    if (entityDefinitionCount >= ENTITY_DEFINITION_MAX) {
        return 0;
    }
    entityDefinitions[entityDefinitionCount] = *definition;
    entityDefinitionCount++;
    return 1;
}

static ENTITY_PARSE_RESULT parseEntityDefinitionLine(Entity_Definition *definition, const char *line, char *newEntityName) {
    Entity_Definition_Component *component;
    char buffer[256];
    char *token;
    char *part;
    int length;

    if (!definition || !line || !newEntityName) {
        return ENTITY_PARSE_ERROR;
    }
    if (strlen(line) >= sizeof(buffer)) {
        return ENTITY_PARSE_ERROR;
    }
    strcpy(buffer, line);
    buffer[strcspn(buffer, "\r\n")] = '\0';
    if (buffer[0] == '\0') {
        return ENTITY_PARSE_IGNORE;
    }
    length = strlen(buffer);
    if (length < 2 || buffer[0] != '[' || buffer[length - 1] != ']') {
        return ENTITY_PARSE_ERROR;
    }
    buffer[length - 1] = '\0';
    token = strtok(buffer + 1, ":");
    if (!token) {
        return ENTITY_PARSE_ERROR;
    }
    if (strcmp(token, "ENTITY") == 0) {
        part = strtok(NULL, ":");
        if (!part || strlen(part) >= ENTITY_DEFINITION_NAME_LENGTH) {
            return ENTITY_PARSE_ERROR;
        }
        strcpy(newEntityName, part);
        return ENTITY_PARSE_NEW_ENTITY;
    }
    if (definition->componentCount >= ENTITY_DEFINITION_MAX_COMPONENTS) {
        return ENTITY_PARSE_ERROR;
    }
    component = &definition->components[definition->componentCount];
    *component = (Entity_Definition_Component){0};
    if (!getComponentType(token, &component->type)) {
        return ENTITY_PARSE_ERROR;
    }
    while ((part = strtok(NULL, ":")) != NULL) {
        if (component->argumentCount >= ENTITY_DEFINITION_MAX_ARGUMENTS) {
            return ENTITY_PARSE_ERROR;
        }
        if (strlen(part) >= ENTITY_DEFINITION_ARGUMENT_LENGTH) {
            return ENTITY_PARSE_ERROR;
        }
        strcpy(component->arguments[component->argumentCount], part);
        component->argumentCount++;
    }
    definition->componentCount++;
    return ENTITY_PARSE_COMPONENT;
}

static int loadEntityDefinitionFile(const char *filename) {
    FILE *file;
    Entity_Definition definition = {0};
    ENTITY_PARSE_RESULT result;
    char newEntityName[ENTITY_DEFINITION_NAME_LENGTH] = {0};
    char line[256];
    int hasDefinition = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    while (fgets(line, sizeof(line), file) != NULL) {
        newEntityName[0] = '\0';
        result = parseEntityDefinitionLine(&definition, line, newEntityName);
        if (result == ENTITY_PARSE_ERROR) {
            fclose(file);
            return 0;
        }
        if (result == ENTITY_PARSE_IGNORE) {
            continue;
        }
        if (result == ENTITY_PARSE_COMPONENT && !hasDefinition) {
            fclose(file);
            return 0;
        }
        if (result == ENTITY_PARSE_NEW_ENTITY) {
            if (hasDefinition) {
                if (!registerEntityDefinition(&definition)) {
                    fclose(file);
                    return 0;
                }
            }
            definition = (Entity_Definition){0};
            strcpy(definition.name, newEntityName);
            hasDefinition = 1;
        }
    }
    if (hasDefinition) {
        if (!registerEntityDefinition(&definition)) {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

void loadEntityDefinitions(const char *path) {
    DIR *directory;
    struct dirent *entry;
    char filename[512];
    int loadResult;

    directory = opendir(path);
    if (directory == NULL) {
        return;
    }
    while ((entry = readdir(directory)) != NULL) {
        printf("%s: ", entry->d_name);
        if (entry->d_type == DT_REG) {
            strcpy(filename, path);
            strcat(filename, "/");
            strcat(filename, entry->d_name);
            loadResult = loadEntityDefinitionFile(filename);
            if (loadResult) {
                printf(" parsed.\n");
            } else {
                printf(" ...ERROR!\n");
            }
        } else {
            printf(" skipped.\n");
        }
    }

    closedir(directory);
}

int getEntityDefinitionCount(void) {
    return entityDefinitionCount;
}

const Entity_Definition *getEntityDefinition(int index) {
    if (index < 0 || index >= entityDefinitionCount) {
        return NULL;
    }
    return &entityDefinitions[index];
}

const Entity_Definition *getEntityDefinitionByName(const char *name) {
    int i;
    if (!name) {
        return NULL;
    }
    for (i = 0; i < entityDefinitionCount; i++) {
        if (strcmp(entityDefinitions[i].name, name) == 0) {
            return &entityDefinitions[i];
        }
    }
    return NULL;
}
