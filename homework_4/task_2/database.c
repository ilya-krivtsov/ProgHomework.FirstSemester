#include "database.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_SIGNATURE "#!hw_phonebook"
#define DB_BEGIN "{{"
#define DB_END "}}"

Database *createDatabase() {
    Database *database = malloc(sizeof(Database));
    if (database == NULL) {
        return NULL;
    }
    database->entriesCount = 0;

    return database;
}

bool addEntry(Database *database, PersonEntry entry) {
    if (database == NULL) {
        return false;
    }

    // entries count cannot be more than DB_MAX_ENTRIES, but check this case too
    if (database->entriesCount >= DB_MAX_ENTRIES) {
        return false;
    }

    database->entries[database->entriesCount] = entry;
    ++database->entriesCount;
    return true;
}

#pragma region Save/Load

bool saveDatabase(FILE *stream, Database *database) {
    if (stream == NULL) {
        return false;
    }

    if (database == NULL) {
        return false;
    }

    fprintf(stream, "%s\n", DB_SIGNATURE);
    fprintf(stream, "%s\n", DB_BEGIN);

    for (int i = 0; i < database->entriesCount; ++i) {
        PersonEntry entry = database->entries[i];
        fprintf(stream, "%s\n", entry.personName);
        fprintf(stream, "%s\n", entry.phoneNumber);
    }

    fprintf(stream, "%s\n", DB_END);

    return true;
}

// reads line and sets first '\n' to '\0'
bool tryReadLine(char *buffer, int count, FILE *file) {
    if (fgets(buffer, count, file) == NULL || feof(file)) {
        return false;
    }

    for (int i = 0; i < count; ++i) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
    }

    return true;
}

Database *loadDatabase(FILE *stream) {
    if (stream == NULL) {
        return NULL;
    }

    Database *database = createDatabase();

    if (database == NULL) {
        return NULL;
    }

    char buffer[256] = { 0 };

    if (!tryReadLine(buffer, sizeof(buffer), stream) && strcmp(buffer, DB_SIGNATURE) != 0) {
        return NULL;
    }

    if (!tryReadLine(buffer, sizeof(buffer), stream) && strcmp(buffer, DB_BEGIN) != 0) {
        return NULL;
    }

    while (true) {
        // person name or db end anchor
        if (!tryReadLine(buffer, sizeof(buffer), stream)) {
            return NULL;
        }

        if (strcmp(buffer, DB_END) == 0) {
            break;
        }

        char *personName = strdup(buffer);
        if (personName == NULL) {
            return NULL;
        }

        // phone number
        if (!tryReadLine(buffer, sizeof(buffer), stream)) {
            return NULL;
        }

        PhoneNumber phoneNumber;
        if (!tryParsePhoneNumber(buffer, &phoneNumber)) {
            return NULL;
        }

        PersonEntry entry = {
            .personName = personName,
            .phoneNumber = phoneNumber
        };

        if (!addEntry(database, entry)) {
            // no space left, not an error
            break;
        }
    }

    return database;
}

#pragma endregion

void disposeDatabase(Database *database) {
    if (database == NULL) {
        return;
    }

    for (int i = 0; i < database->entriesCount; ++i) {
        disposeEntry(&database->entries[i]);
    }
    free(database);
}
