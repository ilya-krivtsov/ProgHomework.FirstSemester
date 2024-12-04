#pragma once

#include <stdio.h>

#include "graph.h"

typedef enum {
    READ_OK,
    READ_ALLOCATION_ERROR,
    READ_FILE_ERROR,
} ReadResult;

ReadResult readGraphFromFileAndCreateCountries(FILE *file, GraphNode ***nodes, int *nodeCount, Country ***countries, int *countryCount, FILE *warningAndErrorOutput);
