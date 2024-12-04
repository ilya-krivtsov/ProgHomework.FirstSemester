#pragma once

#include <stdio.h>

#include "graph.h"

typedef enum {
    READ_OK,
    READ_ALLOCATION_ERROR,
    READ_FILE_ERROR,
} ReadResult;

/// @brief Reads graph from file and creates countries
/// @param file File to read graph from
/// @param nodes Pointer to store array of nodes to
/// @param nodeCount Pointer to store nodes count
/// @param countries Pointer to store array of countries to
/// @param countryCount Pointer to store countries count
/// @param warningAndErrorOutput File to write warning or error messages, can be `NULL`
/// @return `READ_OK` if read file and created countries successfully
///
/// `READ_FILE_ERROR` if file has incorrect format
///
/// `READ_ALLOCATION_ERROR` if allocation failed
ReadResult readGraphFromFileAndCreateCountries(FILE *file, GraphNode ***nodes, int *nodeCount, Country ***countries, int *countryCount, FILE *warningAndErrorOutput);
