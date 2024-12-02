#include "graph.h"

#include <stdlib.h>
#include <string.h>

static bool tryExtendArrayByOne(void **elements, int count, int *capacity) {
    if (count + 1 >= *capacity) {
        *capacity *= 4;
        void *newData = realloc(*elements, *capacity);
        if (newData == NULL) {
            return false;
        }
        *elements = newData;
    }

    return true;
}

typedef struct {
    GraphNode *node;
    int distance;
} NodeData;

#pragma region NodeHashtable

typedef struct {
    NodeData *data;
    int count;
    int capacity;
} Bucket;

typedef struct {
    Bucket *buckets;
    int count;
    int capacity;
} NodeHashtable;

typedef struct {
    NodeHashtable *hashtable;
    int bucketIndex;
    int listIndex;
} HashtableIterator;

HashtableIterator getIterator(NodeHashtable *hashtable) {
    return (HashtableIterator) { .hashtable = hashtable, .bucketIndex = 0, .listIndex = 0 };
}

bool moveNext(HashtableIterator *iterator) {
    for (; iterator->bucketIndex < iterator->hashtable->capacity; ++iterator->bucketIndex) {
        NodeList bucket = iterator->hashtable->buckets[iterator->bucketIndex];
        for (; iterator->listIndex < bucket.count; ++iterator->listIndex) {
            return true;
        }
    }
    return false;
}

NodeData getCurrent(HashtableIterator iterator) {
    return iterator.hashtable->buckets[iterator.bucketIndex].data[iterator.listIndex];
}

static void disposeBuckets(NodeHashtable *hashtable) {
    for (int i = 0; i < hashtable->capacity; ++i) {
        free(hashtable->buckets[i].data);
    }
}

static bool createHashtable(NodeHashtable **hashtable, int capacity) {
    NodeHashtable *newHashtable = malloc(sizeof(NodeHashtable));

    if (newHashtable == NULL) {
        return false;
    }

    newHashtable->count = 0;
    newHashtable->capacity = capacity;
    newHashtable->buckets = calloc(newHashtable->capacity, sizeof(Bucket));

    if (newHashtable->buckets == NULL) {
        free(newHashtable);
        return false;
    }

    bool failed = false;
    for (int i = 0; i < newHashtable->capacity; ++i) {
        Bucket bucket = newHashtable->buckets[i];
        bucket.count = 0;
        bucket.capacity = 8;
        bucket.data = calloc(bucket.capacity, sizeof(NodeData));
        if (bucket.data == NULL) {
            failed = false;
            break;
        }
    }

    if (failed) {
        disposeBuckets(newHashtable);
        free(newHashtable);
        return false;
    }

    *hashtable = newHashtable;
    return true;
}

bool addDistanceToHashtable(NodeHashtable *hashtable, GraphNode *node, int distance, bool *replacedValue);

static bool expandHashtable(NodeHashtable *hashtable) {
    int newCapacity = hashtable->capacity * 4;

    NodeHashtable *newHashtable = NULL;
    if (!createHashtable(&newHashtable, newCapacity)) {
        return false;
    }

    HashtableIterator iterator = getIterator(hashtable);
    while (moveNext(&iterator)) {
        NodeData data = getCurrent(iterator);
        addDistanceToHashtable(newHashtable, data.node, data.distance, NULL);
    }

    disposeBuckets(hashtable);

    *hashtable = *newHashtable;

    free(newHashtable);

    return true;
}

bool addDistanceToHashtable(NodeHashtable *hashtable, GraphNode *node, int distance, bool *replacedValue) {
    if ((float)hashtable->count / hashtable->capacity > 4.0) {
        expandHashtable(hashtable);
    }

    int bucketIndex = (size_t)node % hashtable->capacity;
    Bucket bucket = hashtable->buckets[bucketIndex];

    for (int i = 0; i < bucket.count; ++i) {
        if (bucket.data[i].node == node) {
            if (replacedValue != NULL) {
                *replacedValue = true;
            }

            bucket.data[i].distance = distance;
            return true;
        }
    }

    if (!tryExtendArrayByOne((void**)&bucket.data, bucket.count, &bucket.capacity)) {
        return false;
    }

    bucket.data[bucket.count].node = node;
    bucket.data[bucket.count].distance = distance;

    ++bucket.count;

    if (replacedValue != NULL) {
        *replacedValue = false;
    }

    return true;
}

bool getDistanceFromHashtable(NodeHashtable *hashtable, GraphNode *node, int *distance) {
    int bucketIndex = (size_t)node % hashtable->capacity;
    Bucket bucket = hashtable->buckets[bucketIndex];

    for (int i = 0; i < bucket.count; ++i) {
        if (bucket.data[i].node == node) {
            if (distance != NULL) {
                *distance = bucket.data[i].distance;
            }
            return true;
        }
    }

    return false;
}

void disposeHashtable(NodeHashtable *hashtable) {
    if (hashtable == NULL) {
        return;
    }
    disposeBuckets(hashtable);
    free(hashtable);
}

#pragma endregion

#pragma region Queue

typedef struct QNode {
    NodeData data;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *first;
} Queue;

bool createQueue(Queue **queue) {
    *queue = calloc(1, sizeof(Queue));
    if (*queue == NULL) {
        return false;
    }
    return true;
}

bool enqueue(Queue *queue, GraphNode *node, int distance) {
    QNode *qnode = malloc(sizeof(QNode));
    if (qnode == NULL) {
        return false;
    }

    qnode->data = (NodeData){ .node = node, .distance = distance };
    qnode->next = NULL;

    if (queue->first == NULL) {
        queue->first = qnode;
        return true;
    }

    if (distance < queue->first->data.distance) {
        qnode->next = queue->first;
        queue->first = qnode;
        return true;
    }

    QNode *last = queue->first;
    while (last->next != NULL) {
        if (last->next->data.distance > distance) {
            break;
        }

        last = last->next;
    }

    qnode->next = last->next;
    last->next = qnode;

    return true;
}

bool isEmpty(Queue *queue) {
    if (queue->first == NULL) {
        return false;
    }
    return true;
}

bool dequeueWithMinDistance(Queue *queue, GraphNode **node, int *distance) {
    if (!isEmpty(queue)) {
        return false;
    }

    QNode *first = queue->first;

    if (node != NULL) {
        *node = first->data.node;
    }

    if (distance != NULL) {
        *distance = first->data.distance;
    }

    queue->first = first->next;

    free(first);

    return true;
}

void disposeQueue(Queue *queue) {
    if (queue == NULL) {
        return;
    }
    QNode *node = queue->first;
    while (node != NULL) {
        QNode *next = node->next;
        free(node);
        node = next;
    }
    free(queue);
}

#pragma endregion

typedef struct GraphNode {
    NodeHashtable *neighbors;
} GraphNode;

bool createNode(GraphNode **node) {
    GraphNode *newNode = malloc(sizeof(GraphNode));
    if (newNode == NULL) {
        return false;
    }

    if (!createHashtable(&newNode->neighbors, 64)) {
        free(newNode);
        return false;
    }

    *node = newNode;

    return true;
}

static bool addNeighbor(GraphNode *node, GraphNode *neighbor, int distance) {
    bool wasReplaced = false;
    if (!addDistanceToHashtable(node->neighbors, neighbor, distance, &wasReplaced)) {
        return false;
    }

    if (wasReplaced) {
        // TODO: do something
    }

    return true;
}

bool connect(GraphNode *nodeA, GraphNode *nodeB, int distance) {
    return addNeighbor(nodeA, nodeB, distance) && addNeighbor(nodeB, nodeA, distance);
}

bool getAllNeighbors(GraphNode *node, GraphNode ***neighbors, int *length) {
    *neighbors = calloc(node->neighbors->count, sizeof(GraphNode *));
    if (*neighbors == NULL) {
        return false;
    }

    int count = 0;
    HashtableIterator iterator = getIterator(node->neighbors);
    while (moveNext(&iterator)) {
        neighbors[count] = getCurrent(iterator).node;
        ++count;
    }

    *length = count;
    return true;
}

typedef struct Country {
    GraphNode **nodes;
    int count;
} Country;

bool createCountries(GraphNode **capitals, Country ***countries, int capitalsCount) {
    NodeHashtable *capturedCities = NULL;
    if (!createHashtable(&capturedCities, 64)) {
        return false;
    }

    Queue **queues = calloc(capitalsCount, sizeof(Queue *));
    if (queues == NULL) {
        disposeHashtable(capturedCities);
        return false;
    }

    NodeHashtable **countriesWithDistances = calloc(capitalsCount, sizeof(NodeHashtable *));
    if (countries == NULL) {
        disposeHashtable(capturedCities);
        free(queues);
        return false;
    }

    int *nodesPerCountry = calloc(capitalsCount, sizeof(int));
    if (nodesPerCountry == NULL) {
        disposeHashtable(capturedCities);
        free(queues);
        free(countriesWithDistances);
        return false;
    }

    bool failed = false;
    for (int i = 0; i < capitalsCount; ++i) {
        if (!createQueue(&queues[i])) {
            failed = true;
            break;
        }

        if (!createHashtable(&countriesWithDistances[i], 64)) {
            failed = true;
            break;
        }

        if (!enqueue(queues[i], capitals[i], 0)) {
            failed = true;
            break;
        }

        if (addDistanceToHashtable(countriesWithDistances[i], capitals[i], 0, NULL)) {
            failed = true;
            break;
        }
    }

    if (failed) {
        for (int i = 0; i < capitalsCount; ++i) {
            disposeQueue(queues[i]);
            disposeHashtable(countriesWithDistances[i]);
        }
        disposeHashtable(capturedCities);
        return false;
    }

    int step = -1;
    while (true) {
        int emptyCount = 0;
        for (int i = 0; i < capitalsCount; ++i) {
            if (isEmpty(queues[i])) {
                ++emptyCount;
            }
        }

        if (emptyCount == capitalsCount) {
            break;
        }

        ++step;
        step %= capitalsCount;
        Queue *countryQueue = queues[step];

        GraphNode *closestNode = NULL;
        bool queueIsEmpty = false;
        while (true) {
            if (!dequeueWithMinDistance(countryQueue, &closestNode, NULL)) {
                queueIsEmpty = true;
                break;
            }

            if (!getDistanceFromHashtable(capturedCities, closestNode, NULL)) {
                queueIsEmpty = false;
                break;
            }
        }

        if (queueIsEmpty) {
            continue;
        }

        int distanceToCapital = 0;
        if (!getDistanceFromHashtable(countriesWithDistances[step], closestNode, &distanceToCapital)) {
            failed = true;
            break;
        }

        HashtableIterator iterator = getIterator(closestNode->neighbors);
        while (moveNext(&iterator)) {
            NodeData neighborData = getCurrent(iterator);
            GraphNode *neighbor = neighborData.node;

            if (getDistanceFromHashtable(capturedCities, neighbor, NULL)) {
                continue;
            }

            int neighborDistanceToCapital = distanceToCapital + neighborData.distance;
            if (!enqueue(countryQueue, neighbor, neighborDistanceToCapital)) {
                failed = true;
                break;
            }

            int newDistance = neighborDistanceToCapital;
            int storedDistance = 0;
            if (getDistanceFromHashtable(countriesWithDistances[step], neighbor, &storedDistance)) {
                newDistance = newDistance < storedDistance ? newDistance : storedDistance;
            }

            if (!addDistanceToHashtable(countriesWithDistances[step], neighbor, newDistance, NULL)) {
                failed = true;
                break;
            }
        }

        if (failed) {
            break;
        }

        ++nodesPerCountry[step];
    }

    for (int i = 0; i < capitalsCount; ++i) {
        disposeQueue(queues[i]);
    }
    free(queues);
    disposeHashtable(capturedCities);

    if (failed) {
        for (int i = 0; i < capitalsCount; ++i) {
            disposeHashtable(countriesWithDistances[i]);
        }
        free(countriesWithDistances);
        free(nodesPerCountry);
        return false;
    }

    *countries = calloc(capitalsCount, sizeof(Country *));
    if (*countries == NULL) {
        for (int i = 0; i < capitalsCount; ++i) {
            disposeHashtable(countriesWithDistances[i]);
        }
        free(countriesWithDistances);
        free(nodesPerCountry);
        return false;
    }

    for (int i = 0; i < capitalsCount; ++i) {
        Country *country = calloc(1, sizeof(Country));
        if (country == NULL) {
            failed = true;
            break;
        }

        country->count = nodesPerCountry[i];
        country->nodes = calloc(country->count, sizeof(GraphNode *));
        if (country->nodes == NULL) {
            failed = true;
            break;
        }
        HashtableIterator iterator = getIterator(countriesWithDistances[i]);
        int index = 0;
        while (moveNext(&iterator)) {
            country->nodes[index] = getCurrent(iterator).node;
            ++index;
        }
        (*countries)[i] = country;
    }

    for (int i = 0; i < capitalsCount; ++i) {
        disposeHashtable(countriesWithDistances[i]);
        free(countriesWithDistances);
    }
    free(nodesPerCountry);

    if (failed) {
        for (int i = 0; i < capitalsCount; ++i) {
            Country *country = (*countries)[i];
            if (country == NULL) {
                continue;
            }
            free(country->nodes);
            free(country);
        }
        free(*countries);
        return false;
    }

    return true;
}

bool getAllCities(Country *country, GraphNode **nodes, int *length) {
    *nodes = calloc(country->count, sizeof(GraphNode *));
    if (*nodes == NULL) {
        return false;
    }

    memcpy(*nodes, country->nodes, country->count * sizeof(GraphNode *));

    *length = country->count;

    return true;
}
