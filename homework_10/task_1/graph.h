#pragma once

typedef struct GraphNode GraphNode;

bool createNode(GraphNode **node);

bool connect(GraphNode *nodeA, GraphNode *nodeB, int distance);

bool getAllNeighbors(GraphNode *node, GraphNode ***neighbors, int *length);

typedef struct Country Country;

bool createCountries(GraphNode **capitals, Country ***countries, int capitalsCount);

bool getAllCities(Country *country, GraphNode **nodes, int *length);
