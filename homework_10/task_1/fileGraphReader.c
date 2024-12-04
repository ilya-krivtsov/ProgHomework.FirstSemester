#include "fileGraphReader.h"

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

ReadResult readGraphFromFileAndCreateCountries(FILE *file, GraphNode ***nodes, int *nodeCount, Country ***countries, int *countryCount, FILE *warningAndErrorOutput) {
    int storedNodeCount = 0;
    if (fscanf(file, "%d", &storedNodeCount) != 1) {
        if (warningAndErrorOutput != NULL) {
            fprintf(warningAndErrorOutput, "couldn't read node count\n");
        }
        return READ_FILE_ERROR;
    }

    int connectionsCount = 0;
    if (fscanf(file, "%d", &connectionsCount) != 1) {
        if (warningAndErrorOutput != NULL) {
            fprintf(warningAndErrorOutput, "couldn't read connections count\n");
        }
        return READ_FILE_ERROR;
    }

    GraphNode **storedNodes = calloc(storedNodeCount, sizeof(GraphNode *));
    if (storedNodes == NULL) {
        return READ_ALLOCATION_ERROR;
    }

    ReadResult result = READ_OK;
    for (int i = 0; i < storedNodeCount; ++i) {
        if (!createNode(&storedNodes[i])) {
            result = READ_ALLOCATION_ERROR;
            break;
        }
    }

    if (result != READ_OK) {
        for (int i = 0; i < storedNodeCount; ++i) {
            disposeNode(storedNodes[i]);
        }
        free(storedNodes);

        return result;
    }

    for (int i = 0; i < connectionsCount; ++i) {
        int nodeAIndex = -1;
        int nodeBIndex = -1;
        int distance = -1;
        if (fscanf(file, "%d %d %d", &nodeAIndex, &nodeBIndex, &distance) != 3) {
            if (warningAndErrorOutput != NULL) {
                fprintf(warningAndErrorOutput, "couldn't read connection\n");
            }
            result = READ_FILE_ERROR;
            break;
        }

        if (nodeAIndex < 0 || nodeAIndex >= storedNodeCount) {
            if (warningAndErrorOutput != NULL) {
                fprintf(warningAndErrorOutput, "warning: node #%d does not exist, connection skipped\n", nodeAIndex);
            }
            continue;
        }

        if (nodeBIndex < 0 || nodeBIndex >= storedNodeCount) {
            if (warningAndErrorOutput != NULL) {
                fprintf(warningAndErrorOutput, "warning: node #%d does not exist, connection skipped\n", nodeBIndex);
            }
            continue;
        }

        switch (connect(storedNodes[nodeAIndex], storedNodes[nodeBIndex], distance))
        {
        case CONNECTION_ALLOCATION_ERROR:
            result = READ_ALLOCATION_ERROR;
            break;

        case CONNECTION_ALREADY_EXISTS:
            if (warningAndErrorOutput != NULL) {
                fprintf(warningAndErrorOutput, "warning: connection between node #%d and #%d already exists, skipped\n", nodeAIndex, nodeBIndex);
            }
            break;

        case CONNECTION_OK:
            break;
        }

        if (result != READ_OK) {
            break;
        }
    }

    if (result != READ_OK) {
        for (int i = 0; i < storedNodeCount; ++i) {
            disposeNode(storedNodes[i]);
        }
        free(storedNodes);

        return result;
    }

    int capitalsCount = 0;
    if (fscanf(file, "%d", &capitalsCount) != 1) {
        if (warningAndErrorOutput != NULL) {
            fprintf(warningAndErrorOutput, "couldn't read capitals count\n");
        }

        for (int i = 0; i < storedNodeCount; ++i) {
            disposeNode(storedNodes[i]);
        }
        free(storedNodes);

        return READ_FILE_ERROR;
    }

    GraphNode **capitals = calloc(capitalsCount, sizeof(GraphNode *));
    if (capitals == NULL) {
        for (int i = 0; i < storedNodeCount; ++i) {
            disposeNode(storedNodes[i]);
        }
        free((storedNodes));

        return READ_ALLOCATION_ERROR;
    }

    for (int i = 0; i < capitalsCount; ++i) {
        int capitalIndex = -1;
        if (fscanf(file, "%d", &capitalIndex) != 1) {
            if (warningAndErrorOutput != NULL) {
                fprintf(warningAndErrorOutput, "couldn't read capital index\n");
            }
            result = READ_FILE_ERROR;
            break;
        }
        capitals[i] = storedNodes[capitalIndex];
    }

    if (result != READ_OK) {
        for (int i = 0; i < storedNodeCount; ++i) {
            disposeNode(storedNodes[i]);
        }
        free(storedNodes);
        free(capitals);

        return result;
    }

    if (!createCountries(capitals, countries, capitalsCount)) {
        for (int i = 0; i < storedNodeCount; ++i) {
            disposeNode(storedNodes[i]);
        }
        free(storedNodes);
        free(capitals);

        return READ_ALLOCATION_ERROR;
    }

    *nodes = storedNodes;
    *nodeCount = storedNodeCount;
    *countryCount = capitalsCount;

    free(capitals);
    return READ_OK;
}
