#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "personEntry.h"

typedef enum {
    Exit,
    Error,
    Menu,
    AddingEntry,
    PrintingAllEntries,
    FindNumberByName,
    FindNameByPhone,
    SaveDatabase
} State;

State readCommand(void) {
    int command = -1;
    if (scanf("%d", &command) != 1) {
    }
    while (getchar() != '\n') {}
    switch (command)
    {
    case 0:
        return Exit;
    case 1:
        return AddingEntry;
    case 2:
        return PrintingAllEntries;
    case 3:
        return FindNumberByName;
    case 4:
        return FindNameByPhone;
    case 5:
        return SaveDatabase;
    default:
        printf("Error: unknown command\n");
        return Menu;
    }
}

char *readLine(const char *prompt) {
    char buffer[1024] = { 0 };
    printf("%s", prompt);

    bool overflow = true;
    for (int i = 0; i < sizeof(buffer) - 1; ++i) {
        char c = getchar();
        if (c == '\n' || c == EOF) {
            overflow = false;
            break;
        }
        buffer[i] = c;
    }
    if (overflow) {
        while (getchar() != '\n') {}
    }

    return strdup(buffer);
}

State addEntryCommand(Database *database) {
    if (database->entriesCount == DB_MAX_ENTRIES) {
        printf("Error: entries slots maxed out\n");
        return Menu;
    }

    char *name = readLine("Enter name: ");
    if (name == NULL) {
        printf("Error: cannot read name");
        return Menu;
    }

    char *rawPhoneNumber = readLine("Enter phone number: ");
    if (rawPhoneNumber == NULL) {
        printf("Error: cannot read phone number");
        return Menu;
    }

    PhoneNumber phoneNumber;
    if (!tryParsePhoneNumber(rawPhoneNumber, &phoneNumber)) {
        printf("Error: phone number is in incorrect format");
        free(rawPhoneNumber);
        return Menu;
    }
    free(rawPhoneNumber);

    PersonEntry entry = {
        .personName = name,
        .phoneNumber = phoneNumber
    };

    if (!addEntry(database, entry)) {
        printf("Error: cannot add new entry\n");
        return Menu;
    }

    printf("Added entry successfully\n");

    int slotsLeft = DB_MAX_ENTRIES - database->entriesCount;
    if (slotsLeft == 0) {
        printf("Warning: no entry slots left in database for new entries\n");
    } else if (slotsLeft <= 10) {
        printf("Warning: %d entry slots left in database\n", slotsLeft);
    }

    return Menu;
}

State printDatabaseCommand(Database *database) {
    for (int i = 0; i < database->entriesCount; ++i) {
        PersonEntry entry = database->entries[i];
        printf("%s : %s\n", entry.personName, entry.phoneNumber);
    }

    return Menu;
}

State saveDatabaseCommand(Database *database, const char *path) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        printf("IO error: cannot save database\n");
        return Menu;
    }
    if (!saveDatabase(file, database)) {
        printf("Error: cannot save database\n");
    }
    fclose(file);
    printf("Saved successfully\n");
    return Menu;
}

bool doConversation(void) {
    const char *databasePath = "./phoneDatabase";
    Database *database;
    FILE *file = fopen(databasePath, "r");
    if (file == NULL) {
        database = createDatabase();
    } else {
        database = loadDatabase(file);
        fclose(file);
    }

    printf("Phone database\n");
    printf("Available commands: \n");
    printf("  0 - exit;\n");
    printf("  1 - add new entry;\n");
    printf("  2 - print all entries;\n");
    printf("  3 - find phone number by name;\n");
    printf("  4 - find name by phone number;\n");
    printf("  5 - save database.\n");

    State state = Menu;
    while (true) {
        switch (state)
        {
        case Exit:
            printf("Exiting...\n");
            disposeDatabase(database);
            return true;

        case Error:
            disposeDatabase(database);
            return false;

        case Menu:
            printf("phonedb> ");
            state = readCommand();
            break;

        case AddingEntry:
            state = addEntryCommand(database);
            break;

        case PrintingAllEntries:
            state = printDatabaseCommand(database);
            break;

        case FindNumberByName:
        case FindNameByPhone:
            state = Menu;
            break;

        case SaveDatabase:
            state = saveDatabaseCommand(database, databasePath);
            break;

        default:
            printf("Error: Unknown state\n");
            disposeDatabase(database);
            return false;
        }
    }
}

int main(void) {
    bool conversationResult = doConversation();
    return conversationResult ? 0 : 1;
}
