#pragma once

typedef enum {
    CONNECTION_OK,
    CONNECTION_ALLOCATION_ERROR,
    CONNECTION_ALREADY_EXISTS
} ConnectionResult;

typedef struct GraphNode GraphNode;

bool createNode(GraphNode **node);

ConnectionResult connect(GraphNode *nodeA, GraphNode *nodeB, int distance);

void disposeNode(GraphNode *node);

typedef struct Country Country;

bool createCountries(GraphNode **capitals, Country ***countries, int capitalsCount);

bool getAllCities(Country *country, GraphNode ***nodes, int *length);

void disposeCountry(Country *country);
