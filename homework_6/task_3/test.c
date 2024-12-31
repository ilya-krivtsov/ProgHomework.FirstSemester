#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include <stdlib.h>

#include "sortedList.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

SortedList *createNewList(void) {
    SortedList *list = NULL;
    ASSERT_TRUE(createList(&list));
    return list;
}

void addToList(SortedList *list, int value) {
    ASSERT_TRUE(addElement(list, value));
}

void assertEqual(SortedList *list, const int *array, int size) {
    int i = 0;
    Element *element = getFirst(list);
    while (element != NULL) {
        ASSERT_LE(i, size);
        ASSERT_EQUAL(getValue(element), array[i]);
        ++i;
        element = getNext(element);
    }
    ASSERT_EQUAL(i, size);
}

CTEST(sortedListTests, emptyListTest) {
    SortedList *list = createNewList();
    assertEqual(list, NULL, 0);
}

CTEST(sortedListTests, singleElementTest) {
#define size 1
    SortedList *list = createNewList();
    addToList(list, 5);

    int array[size] = { 5 };
    assertEqual(list, array, size);
#undef size
}

CTEST(sortedListTests, constantSizeListTestA) {
#define size 4
    SortedList *list = createNewList();
    addToList(list, 1);
    addToList(list, 4);
    addToList(list, 9);
    addToList(list, 13);

    int array[size] = { 1, 4, 9, 13 };
    assertEqual(list, array, size);
#undef size
}

CTEST(sortedListTests, constantSizeListTestB) {
#define size 8
    SortedList *list = createNewList();
    addToList(list, 45);
    addToList(list, 22);
    addToList(list, 52);
    addToList(list, 282);
    addToList(list, -23);
    addToList(list, 0);
    addToList(list, 3432);
    addToList(list, 734);

    int array[size] = { -23, 0, 22, 45, 52, 282, 734, 3432 };
    assertEqual(list, array, size);
#undef size
}

CTEST(sortedListTests, addAndRemoveElementsTest) {
#define size 8
    SortedList *list = createNewList();
    addToList(list, 543);
    addToList(list, 62);
    addToList(list, 224);
    addToList(list, -234);
    addToList(list, 4352);
    addToList(list, 6);
    addToList(list, -675);
    addToList(list, 879);

    int arrayA[size] = { -675, -234, 6, 62, 224, 543, 879, 4352 };
    assertEqual(list, arrayA, size);

    ASSERT_TRUE(removeElement(list, -675));
    int arrayB[size - 1] = { -234, 6, 62, 224, 543, 879, 4352 };
    assertEqual(list, arrayB, size - 1);

    ASSERT_TRUE(removeElement(list, 4352));
    int arrayC[size - 2] = { -234, 6, 62, 224, 543, 879 };
    assertEqual(list, arrayC, size - 2);

    ASSERT_TRUE(removeElement(list, 224));
    int arrayD[size - 3] = { -234, 6, 62, 543, 879 };
    assertEqual(list, arrayD, size - 3);

    ASSERT_TRUE(removeElement(list, 543));
    int arrayE[size - 4] = { -234, 6, 62, 879 };
    assertEqual(list, arrayE, size - 4);

    ASSERT_TRUE(removeElement(list, 6));
    int arrayF[size - 5] = { -234, 62, 879 };
    assertEqual(list, arrayF, size - 5);

    ASSERT_TRUE(removeElement(list, -234));
    int arrayG[size - 6] = { 62, 879 };
    assertEqual(list, arrayG, size - 6);

    ASSERT_TRUE(removeElement(list, 879));
    int arrayH[size - 7] = { 62 };
    assertEqual(list, arrayH, size - 7);

    ASSERT_EQUAL(getValue(getFirst(list)), 62);

    ASSERT_FALSE(removeElement(list, -1));
    ASSERT_FALSE(removeElement(list, 100));

    ASSERT_TRUE(removeElement(list, 62));

    ASSERT_FALSE(removeElement(list, 0));
    ASSERT_FALSE(removeElement(list, 12));
    ASSERT_FALSE(removeElement(list, 100));

    ASSERT_NULL(getFirst(list));

#undef size
}
