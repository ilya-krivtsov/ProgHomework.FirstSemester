#pragma once

#include <stdbool.h>

typedef enum {
    CONNECTION_OK,
    CONNECTION_ALLOCATION_ERROR,
    CONNECTION_ALREADY_EXISTS
} ConnectionResult;

/// @brief Node of a graph
typedef struct GraphNode GraphNode;

/// @brief Creates new `GraphNode`
/// @param node Pointer to store `GraphNode` to
/// @return `true` if created successfully, `false` otherwise (allocation failed)
bool createNode(GraphNode **node);

/// @brief Connect two graph nodes
/// @param nodeA First node
/// @param nodeB Second node
/// @param distance Distance between nodes
/// @return `CONNECTION_OK` if connected successfully
///
/// `CONNECTION_ALREADY_EXISTS` if specified nodes were already connected
///
/// `CONNECTION_ALLOCATION_ERROR` if allocation failed
ConnectionResult connect(GraphNode *nodeA, GraphNode *nodeB, int distance);

/// @brief Disposes node
/// @note This method expects that ALL nodes created with `createNode()` will be disposed at once, for example in a single for loop
/// @param node Node to dispose
void disposeNode(GraphNode *node);

/// @brief Country that contains array of cities
typedef struct Country Country;

/// @brief Creates countries using specified capitals by capturing cities that are closest to a capital
/// @param capitals Capitals to base countries on
/// @param countries Pointer to store array of countries to
/// @param capitalsCount Capitals count (same as countries count)
/// @return `true` if created successfully, `false` otherwise (allocation failed)
bool createCountries(GraphNode **capitals, Country ***countries, int capitalsCount);

/// @brief Gets all cities in a country
/// @param country Country to get cities from
/// @param nodes Pointer to store array of cities to
/// @param length Pointer to store length of array
/// @return `true` if created successfully, `false` otherwise (allocation failed)
bool getAllCities(Country *country, GraphNode ***nodes, int *length);

/// @brief Disposes country
/// @note This method DOES NOT dispose cities in that country, dispose them separately
/// @param country Country to dispose
void disposeCountry(Country *country);
