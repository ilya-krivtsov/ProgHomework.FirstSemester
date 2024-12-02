#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("graph.txt", "r");
    if (file == NULL) {
        printf("couldn't open file\n");
        return 1;
    }

    int nodeCount = 0;
    if (fscanf(file, "%d", &nodeCount) != 1) {
        printf("couldn't read node count\n");
        return 1;
    }

    int connectionsCount = 0;
    if (fscanf(file, "%d", &connectionsCount) != 1) {
        printf("couldn't read connections count\n");
        return 1;
    }

    GraphNode **nodes = calloc(nodeCount, sizeof(GraphNode *));
    if (nodes == NULL) {
        printf("allocation error\n");
        return 1;
    }

    bool failed = false;
    for (int i = 0; i < nodeCount; ++i) {
        if (!createNode(&nodes[i])) {
            printf("allocation error\n");
            failed = true;
            break;
        }
    }

    if (failed) {
        for (int i = 0; i < nodeCount; ++i) {
            disposeNode(nodes[i]);
        }
        free(nodes);

        return 1;
    }

    for (int i = 0; i < connectionsCount; ++i) {
        int nodeAIndex = -1;
        int nodeBIndex = -1;
        int distance = -1;
        if (fscanf(file, "%d %d %d", &nodeAIndex, &nodeBIndex, &distance) != 3) {
            printf("couldn't read connection\n");
            failed = true;
            break;
        }

        if (nodeAIndex < 0 || nodeAIndex >= nodeCount) {
            printf("warning: node #%d does not exist, connection skipped\n", nodeAIndex);
            continue;
        }

        if (nodeBIndex < 0 || nodeBIndex >= nodeCount) {
            printf("warning: node #%d does not exist, connection skipped\n", nodeBIndex);
            continue;
        }

        switch (connect(nodes[nodeAIndex], nodes[nodeBIndex], distance))
        {
        case CONNECTION_ALLOCATION_ERROR:
            printf("allocation error\n");
            failed = true;
            break;

        case CONNECTION_ALREADY_EXISTS:
            printf("warning: connection between node #%d and #%d already exists, skipped\n", nodeAIndex, nodeBIndex);
            break;

        case CONNECTION_OK:
            break;
        }

        if (failed) {
            break;
        }
    }

    if (failed) {
        for (int i = 0; i < nodeCount; ++i) {
            disposeNode(nodes[i]);
        }
        free(nodes);

        return 1;
    }

    int capitalsCount = 0;
    if (fscanf(file, "%d", &capitalsCount) != 1) {
        printf("couldn't read capitals count\n");
        for (int i = 0; i < nodeCount; ++i) {
            disposeNode(nodes[i]);
        }
        free(nodes);

        return 1;
    }

    GraphNode **capitals = calloc(capitalsCount, sizeof(GraphNode *));
    if (capitals == NULL) {
        printf("allocation error\n");
        for (int i = 0; i < nodeCount; ++i) {
            disposeNode(nodes[i]);
        }
        free(nodes);

        return 1;
    }

    for (int i = 0; i < capitalsCount; ++i) {
        int capitalIndex = -1;
        if (fscanf(file, "%d", &capitalIndex) != 1) {
            printf("couldn't read capital index\n");
            failed = true;
            break;
        }
        capitals[i] = nodes[capitalIndex];
    }

    if (failed) {
        for (int i = 0; i < nodeCount; ++i) {
            disposeNode(nodes[i]);
        }
        free(nodes);
        free(capitals);

        return 1;
    }

    Country **countries = NULL;
    if (!createCountries(capitals, &countries, capitalsCount)) {
        printf("allocation error\n");
        for (int i = 0; i < nodeCount; ++i) {
            disposeNode(nodes[i]);
        }
        free(nodes);
        free(capitals);

        return 1;
    }

    printf("countries:\n");
    printf("\n");
    for (int i = 0; i < capitalsCount; ++i) {
        printf("country #%d:\n", i + 1);
        Country *country = countries[i];
        GraphNode **cities = NULL;
        int cityCount = 0;
        if (!getAllCities(country, &cities, &cityCount)) {
            printf("allocation error\n");
            failed = true;
            break;
        }

        for (int j = 0; j < cityCount; ++j) {
            GraphNode *node = cities[j];
            for (int k = 0; k < nodeCount; ++k) {
                if (nodes[k] == node) {
                    printf("  city #%d\n", k);
                    break;
                }
            }
        }

        free(cities);
    }

    for (int i = 0; i < nodeCount; ++i) {
        disposeNode(nodes[i]);
    }

    free(nodes);
    free(capitals);

    for (int i = 0; i < capitalsCount; ++i) {
        disposeCountry(countries[i]);
    }
    free(countries);

    if (failed) {
        return 1;
    }
}
