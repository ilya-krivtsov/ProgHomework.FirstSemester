#pragma once

#include <stdbool.h>
#include <stdio.h>

#include "personEntry.h"

#define DB_MAX_ENTRIES 100

typedef struct {
    int entriesCount;
    PersonEntry entries[DB_MAX_ENTRIES];
} Database;

/// @brief Creates empty database
/// @return `Database` if created successfully, `NULL` otherwise
Database *createDatabase();

/// @brief Adds a person entry to database
/// @param database Pointer to database
/// @param entry Entry to add
/// @return `true` if added successfully, `false` otherwise (no space in database left)
bool addEntry(Database *database, PersonEntry entry);

/// @brief Saves database to specified stream
/// @param stream Stream to save database to
/// @param database Pointer to database
/// @return `true` if saved successfully, `false` otherwise
bool saveDatabase(FILE *stream, Database *database);

/// @brief Loads database from specified file stream
/// @param stream Stream to load database from
/// @return `Database` if loaded successfully, `NULL` otherwise
Database *loadDatabase(FILE *stream);

/// @brief Disposes database and all of its entries
/// @param database Database to dispose (can be `NULL`)
void disposeDatabase(Database *database);
