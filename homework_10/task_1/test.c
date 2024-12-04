#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include "graph.h"
#include "fileGraphReader.h"

#define TEST_FILES "testFiles/"
#define GRAPH "_graph.txt"
#define COUNTRIES "_countries.txt"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

GraphNode *getNodeById(GraphNode **nodes, int nodeCount, int id) {
    for (int i = 0; i < nodeCount; ++i) {
        if (i == id) {
            return nodes[i];
        }
    }
    ASSERT_FAIL();
    return NULL;
}

void assertCountry(GraphNode **nodes, int nodeCount, Country *country, FILE *file) {
    GraphNode **cities = NULL;
    int cityCount = 0;
    ASSERT_TRUE(getAllCities(country, &cities, &cityCount));

    int expectedCityCount = 0;
    ASSERT_EQUAL(fscanf(file, "%d", &expectedCityCount), 1);
    ASSERT_EQUAL(expectedCityCount, cityCount);

    for (int i = 0; i < cityCount; ++i) {
        int expectedCityId = -1;
        ASSERT_EQUAL(fscanf(file, "%d", &expectedCityId), 1);

        GraphNode *expectedNode = getNodeById(nodes, nodeCount, expectedCityId);

        int foundCityIndex = -1;
        for (int j = 0; j < cityCount; ++j) {
            if (expectedNode == cities[j]) {
                foundCityIndex = j;
                break;
            }
        }

        ASSERT_NOT_EQUAL(foundCityIndex, -1);
        cities[foundCityIndex] = NULL;
    }

    for (int i = 0; i < cityCount; ++i) {
        ASSERT_NULL(cities[i]);
    }
}

void testGraph(const char *inputFilename, const char *expectedOutputFilename) {
    FILE *inputFile = fopen(inputFilename, "r");
    ASSERT_NOT_NULL(inputFile);

    FILE *expectedOutputFile = fopen(expectedOutputFilename, "r");
    ASSERT_NOT_NULL(expectedOutputFile);

    GraphNode **nodes = NULL;
    int nodeCount = 0;
    Country **countries = NULL;
    int countryCount = 0;
    ASSERT_EQUAL(READ_OK, readGraphFromFileAndCreateCountries(inputFile, &nodes, &nodeCount, &countries, &countryCount, NULL));
    ASSERT_EQUAL(fclose(inputFile), 0);

    int expectedCountryCount = 0;
    ASSERT_EQUAL(fscanf(expectedOutputFile, "%d", &expectedCountryCount), 1);
    ASSERT_EQUAL(expectedCountryCount, countryCount);

    for (int i = 0; i < countryCount; ++i) {
        assertCountry(nodes, nodeCount, countries[i], expectedOutputFile);
    }

    ASSERT_EQUAL(fclose(expectedOutputFile), 0);

    for (int i = 0; i < nodeCount; ++i) {
        disposeNode(nodes[i]);
    }
    free(nodes);

    for (int i = 0; i < countryCount; ++i) {
        disposeCountry(countries[i]);
    }
    free(countries);
}

CTEST(graphTests, graphTestSingleCity) {
    testGraph(TEST_FILES "singleCity" GRAPH, TEST_FILES "singleCity" COUNTRIES);
}

CTEST(graphTests, graphTestTwoCities) {
    testGraph(TEST_FILES "singleCity" GRAPH, TEST_FILES "singleCity" COUNTRIES);
}

CTEST(graphTests, graphTestFiveCitiesTwoCountries) {
    testGraph(TEST_FILES "fiveCitiesTwoCountries" GRAPH, TEST_FILES "fiveCitiesTwoCountries" COUNTRIES);
}

CTEST(graphTests, graphTestFiveCitiesFiveCountries) {
    testGraph(TEST_FILES "fiveCitiesFiveCountries" GRAPH, TEST_FILES "fiveCitiesFiveCountries" COUNTRIES);
}

CTEST(graphTests, graphTestComplexA) {
    testGraph(TEST_FILES "complexA" GRAPH, TEST_FILES "complexA" COUNTRIES);
}

CTEST(graphTests, graphTestComplexB) {
    testGraph(TEST_FILES "complexB" GRAPH, TEST_FILES "complexB" COUNTRIES);
}
