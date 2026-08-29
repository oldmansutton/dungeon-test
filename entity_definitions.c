// entity_definitions.c
//
// Copyright (c) 2026 - oldmansutton
//

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "entity_definitions.h"

static int entityDefinitionParseLine(Entity_Definition *definition, const char *line) {
    Entity_Definition_Entry *entry;
    char buffer[256];
    char *part;
    int length;

    if (!definition || !line) {
        return 0;
    }
    if (definition->entryCount >= ENTITY_DEFINITION_MAX_ENTRIES) {
        return 0;
    }
    if (snprintf(buffer, sizeof(buffer), "%s", line) >= sizeof(buffer)) {
        return 0;
    }
    buffer[strcspn(buffer, "\r\n")] = '\0';
    length = strlen(buffer);
    if (length < 2 || buffer[0] != '[' || buffer[length - 1] != ']') {
        return 0;
    }
    buffer[length - 1] = '\0';
    entry = &definition->entries[definition->entryCount];
    *entry = (Entity_Definition_Entry){0};
    part = strtok(buffer + 1, ":");
    if (!part) {
        return 0;
    }
    snprintf(entry->token, sizeof(entry->token), "%s", part);
    while ((part = strtok(NULL, ":")) != NULL) {
        if (entry->argumentCount >= ENTITY_DEFINITION_MAX_ARGUMENTS) {
            return 0;
        }
        snprintf(entry->arguments[entry->argumentCount], sizeof(entry->arguments[entry->argumentCount]), "%s", part);
        entry->argumentCount++;
    }
    definition->entryCount++;
    return 1;
}

static int entityDefinitionLoadFile(const char *filename, Entity_Definition *definition) {
    FILE *file;
    char line[256];
    file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    while (fgets(line, sizeof(line), file) != NULL) {
        entityDefinitionParseLine(definition, line);
    }
    fclose(file);
    return 1;
}

void loadEntityDefinitions(const char *path) {
    DIR *directory;
    struct dirent *entry;
    directory = opendir(path);
    if (directory == NULL) {
        return;
    }
    while ((entry = readdir(directory)) != NULL) {
        printf("%s: ", entry->d_name);
        if (entry->d_type == DT_REG) {
            // loadResult = entityDefinitionLoadFile(entry->d_name, SomeEntityDefinition);
            // no idea where that entity definition comes from
            // add if branch for load result logging
            printf(" parsed.\n");
        } else {
            printf(" skipped.\n");
        }
    }

    closedir(directory);
}
