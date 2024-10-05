#pragma once

#include <stdbool.h>

#include "personEntry.h"

typedef struct {
    int entriesCount, entriesCapacity;
    PersonEntry **entries;
} Database;

/// @brief Each operation with database (except dispose) yields result
typedef enum {
    /// @brief Operation is successful
    DB_SUCCESS = 0,

    /// @brief IO error (file does not exist / open in other process / etc)
    DB_IO_ERROR = 1,

    /// @brief Specified pointer is null
    DB_NULL_POINTER = 2,

    /// @brief Allocation error
    DB_ALLOCATION_ERROR = 3,

    /// @brief Invalid file format (when reading)
    DB_INVALID_FORMAT = 4,

    /// @brief Unknown error
    DB_UNKNOWN_ERROR = -1
} DBResult;

/// @brief Creates empty database
/// @param database Pointer to write result to
/// @return `DB_SUCCESS`, `DB_NULL_POINTER`, `DB_ALLOCATION_ERROR`
DBResult createDatabase(Database **database);

/// @brief Adds a person entry to database
/// @param database Pointer to database
/// @param entry Entry to add (can be `NULL`)
/// @return `DB_SUCCESS`, `DB_NULL_POINTER`, `DB_ALLOCATION_ERROR`
DBResult addEntry(Database *database, PersonEntry *entry);

/// @brief Saves database to specified file path (will OVERWRITE existing file contents)
/// @param input Path to save database to
/// @param database Pointer to database
/// @return `DB_SUCCESS`, `DB_IO_ERROR`, `DB_NULL_POINTER`
DBResult saveDatabase(const char *path, Database *database);

/// @brief Loads database from specified file path
/// @param input Path to load database from
/// @param database Pointer to write result to
/// @return `DB_SUCCESS`, `DB_IO_ERROR`, `DB_NULL_POINTER`, `DB_ALLOCATION_ERROR`, `DB_INVALID_FORMAT`
DBResult loadDatabase(const char *path, Database **database);

/// @brief Disposes database and all of its entries
/// @param database Database to dispose (can be `NULL`)
void disposeDatabase(Database *database);
