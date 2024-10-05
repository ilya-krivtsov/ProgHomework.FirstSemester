#include "database.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_SIGNATURE "#!hw_phonebook"
#define DB_BEGIN "{{"
#define DB_END "}}"
#define DB_ENTRY_BEGIN "[["
#define DB_ENTRY_END "]]"
#define DB_ENTRY_NULL "__NULL__"

DBResult createDatabase(Database **database) {
    if (database == NULL) {
        return DB_NULL_POINTER;
    }

    Database *db = malloc(sizeof(Database));
    if (db == NULL) {
        *database = NULL;
        return DB_ALLOCATION_ERROR;
    }
    db->entriesCount = 0;
    db->entriesCapacity = 4;
    db->entries = malloc(db->entriesCapacity * sizeof(PersonEntry *));

    if (db->entries == NULL) {
        *database = NULL;
        return DB_ALLOCATION_ERROR;
    }

    *database = db;

    return DB_SUCCESS;
}

DBResult addEntry(Database *database, PersonEntry *entry) {
    if (database == NULL) {
        return DB_NULL_POINTER;
    }

    if (database->entriesCount == database->entriesCapacity) {
        database->entriesCapacity *= 2;
        PersonEntry **entries = realloc(database->entries, database->entriesCapacity * sizeof(PersonEntry **));
        if (entries == NULL) {
            return DB_ALLOCATION_ERROR;
        }
        database->entries = entries;
    }
    database->entries[database->entriesCount] = entry;
    ++database->entriesCount;
    return DB_SUCCESS;
}

#pragma region Save/Load

DBResult saveDatabase(const char *path, Database *database) {
    if (database == NULL) {
        return DB_NULL_POINTER;
    }

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        return DB_IO_ERROR;
    }

    fprintf(file, "%s\n", DB_SIGNATURE);
    fprintf(file, "%s\n", DB_BEGIN);

    for (int i = 0; i < database->entriesCount; ++i) {
        fprintf(file, "%s\n", DB_ENTRY_BEGIN);

        PersonEntry *entry = database->entries[i];

        if (entry == NULL) {
            fprintf(file, "%s\n", DB_ENTRY_NULL);
        } else {
            fprintf(file, "%s\n", entry->personName);

            for (int j = 0; j < entry->phoneNumbersCount; ++j) {
                fprintf(file, "%s\n", entry->phoneNumbers[j].number);
            }
        }

        fprintf(file, "%s\n", DB_ENTRY_END);
    }

    fprintf(file, "%s\n", DB_END);

    fclose(file);

    return DB_SUCCESS;
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

DBResult loadFromFile(Database *database, FILE *file) {
    char buffer[256] = { 0 };

    if (!tryReadLine(buffer, sizeof(buffer), file) && strcmp(buffer, DB_SIGNATURE) != 0) {
        return DB_INVALID_FORMAT;
    }

    if (!tryReadLine(buffer, sizeof(buffer), file) && strcmp(buffer, DB_BEGIN) != 0) {
        return DB_INVALID_FORMAT;
    }

    bool finishedScanning = false;

    DBResult result;

    while (true) {
        // entry begin anchor or db end anchor
        if (!tryReadLine(buffer, sizeof(buffer), file)) {
            return DB_INVALID_FORMAT;
        }

        if (strcmp(buffer, DB_END) == 0) {
            finishedScanning = true;
            break;
        }

        if (strcmp(buffer, DB_ENTRY_BEGIN) != 0) {
            return DB_INVALID_FORMAT;
        }

        // name or null keyword
        if (!tryReadLine(buffer, sizeof(buffer), file)) {
            return DB_INVALID_FORMAT;
        }

        if (strcmp(buffer, DB_ENTRY_NULL) == 0) {
            result = addEntry(database, NULL);
            if (result != DB_SUCCESS) {
                return result;
            }
            if (!tryReadLine(buffer, sizeof(buffer), file) || strcmp(buffer, DB_ENTRY_END) != 0) {
                return DB_INVALID_FORMAT;
            }
            continue;
        }

        PersonEntry *entry;
        if (!tryCreateEntry(&entry, buffer)) {
            return DB_ALLOCATION_ERROR;
        }

        while (true) {
            // phone number or entry end anchor
            if (!tryReadLine(buffer, sizeof(buffer), file)) {
                return DB_INVALID_FORMAT;
            }

            if (strcmp(buffer, DB_ENTRY_END) == 0) {
                break;
            }

            PhoneNumber number;
            if (!tryParsePhoneNumber(buffer, &number)) {
                return DB_INVALID_FORMAT;
            }
            tryAddPhoneNumber(entry, number);
        }

        result = addEntry(database, entry);
        if (result != DB_SUCCESS) {
            return result;
        }
    }

    return finishedScanning ? DB_SUCCESS : DB_INVALID_FORMAT;
}

DBResult loadDatabase(const char *path, Database **database) {
    if (database == NULL) {
        return DB_NULL_POINTER;
    }

    FILE *file = fopen(path, "r");

    if (file == NULL) {
        *database = NULL;
        return DB_IO_ERROR;
    }

    Database *db;

    DBResult result = createDatabase(&db);
    if (result == DB_SUCCESS) {
        result = loadFromFile(db, file);
    }

    *database = result == DB_SUCCESS ? db : NULL;

    fclose(file);

    return result;
}

#pragma endregion

void disposeDatabase(Database *database) {
    if (database == NULL) {
        return;
    }

    for (int i = 0; i < database->entriesCount; ++i) {
        disposeEntry(database->entries[i]);
    }
    free(database->entries);
    free(database);
}
