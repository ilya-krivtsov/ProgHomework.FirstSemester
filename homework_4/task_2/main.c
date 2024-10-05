#include <stdio.h>

#include "database.h"
#include "personEntry.h"

void printDatabase(Database *database) {
    printf("database:\n");
    for (int i = 0; i < database->entriesCount; ++i) {
        PersonEntry *entry = database->entries[i];

        if (entry == NULL) {
            printf("- null;\n\n");
            continue;
        }

        printf("- %s:\n", entry->personName);

        for (int j = 0; j < entry->phoneNumbersCount; ++j) {
            printf("  * %s\n", entry->phoneNumbers[j].number);
        }
        printf("\n");
    }
}

bool doStuff(Database *database) {
    PersonEntry *entry, *entry2, *entry3;
    if (!tryCreateEntry(&entry, "Kris")) {
        return false;
    }
    if (!tryAddRawPhoneNumber(entry, "+7 901 123 45 67")) {
        return false;
    }
    if (!tryAddRawPhoneNumber(entry, "+7 912 345 67 89")) {
        return false;
    }
    if (addEntry(database, entry) != DB_SUCCESS) {
        return false;
    }

    if (!tryCreateEntry(&entry2, "Susie")) {
        return false;
    }
    if (!tryAddRawPhoneNumber(entry2, "+1 (301) 124-45-75")) {
        return false;
    }
    if (!tryAddRawPhoneNumber(entry2, "+1 (212) 325-38-68")) {
        return false;
    }
    if (addEntry(database, entry2) != DB_SUCCESS) {
        return false;
    }

    if (addEntry(database, NULL) != DB_SUCCESS) {
        return false;
    }

    if (!tryCreateEntry(&entry3, "Noelle")) {
        return false;
    }
    if (!tryAddRawPhoneNumber(entry3, "+3 (111) 222-33-44")) {
        return false;
    }
    if (!tryAddRawPhoneNumber(entry3, "+3 (222) 999-22-11")) {
        return false;
    }
    if (!tryAddRawPhoneNumber(entry3, "+3 (355) 532-23-45")) {
        return false;
    }
    if (!tryAddRawPhoneNumber(entry3, "+3 (234) 342-64-41")) {
        return false;
    }
    if (!tryAddRawPhoneNumber(entry3, "+3 (974) 756-33-64")) {
        return false;
    }
    if (!tryAddRawPhoneNumber(entry3, "+3 (535) 463-22-53")) {
        return false;
    }
    if (addEntry(database, entry3) != DB_SUCCESS) {
        return false;
    }

    printDatabase(database);

    switch (saveDatabase("./db.txt", database))
    {
    case DB_IO_ERROR:
        printf("write io error\n");
        return false;

    case DB_SUCCESS:
        printf("saved\n");
        break;
    }

    Database *db2;

    switch (loadDatabase("./db.txt", &db2))
    {
    case DB_IO_ERROR:
        printf("read io error\n");
        return false;

    case DB_INVALID_FORMAT:
        printf("invalid file format\n");
        return false;

    case DB_ALLOCATION_ERROR:
        printf("alloc error\n");
        break;

    case DB_SUCCESS:
        printf("loaded\n");
        break;
    }

    printf("loaded db:\n");

    printDatabase(db2);

    disposeDatabase(db2);

    return true;
}

int main(void) {
    Database *database = NULL;

    if (createDatabase(&database) != DB_SUCCESS || !doStuff(database)) {
        printf("something is very wrong :((\n");
    }

    disposeDatabase(database);
}
