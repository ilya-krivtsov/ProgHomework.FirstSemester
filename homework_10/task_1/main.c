#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "fileGraphReader.h"

int main() {
    FILE *file = fopen("graph.txt", "r");
    if (file == NULL) {
        printf("couldn't open file\n");
        return 1;
    }

    GraphNode **nodes = NULL;
    int nodeCount = 0;
    Country **countries = NULL;
    int countryCount = 0;
    switch (readGraphFromFileAndCreateCountries(file, &nodes, &nodeCount, &countries, &countryCount, stdout)) {
    case READ_OK:
        break;
    case READ_ALLOCATION_ERROR:
        printf("allocation error\n");
        return 1;
    case READ_FILE_ERROR:
        return 1;
    }

    bool failed = false;

    printf("countries:\n");
    printf("\n");
    for (int i = 0; i < countryCount; ++i) {
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

    for (int i = 0; i < countryCount; ++i) {
        disposeCountry(countries[i]);
    }
    free(countries);

    if (failed) {
        return 1;
    }
}
