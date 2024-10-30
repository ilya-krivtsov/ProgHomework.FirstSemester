#define CTEST_MAIN
#define CTEST_SEGFAULT
#include "../../ctest/ctest.h"

#include "cyclicList.h"

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}

ListElement *add(ListElement *after, int value) {
    ListElement *element;
    ASSERT_TRUE(addElementAfter(after, &element, value));
    ASSERT_NOT_NULL(element);

    return element;
}

CTEST(cyclicListTests, createTest) {
    ListElement *element = add(NULL, 0);

    ASSERT_TRUE(getNext(element) == element);
    ASSERT_TRUE(getNext(getNext(element)) == element);

    removeAllElements(element);
}

CTEST(cyclicListTests, addElementTest) {
    ListElement *elementA = add(NULL, 0);
    ListElement *elementB = add(elementA, 1);
    ListElement *elementC = add(elementB, 2);
    ListElement *elementD = add(elementC, 3);

    ASSERT_TRUE(getNext(elementA) == elementB);
    ASSERT_TRUE(getNext(elementB) == elementC);
    ASSERT_TRUE(getNext(elementC) == elementD);
    ASSERT_TRUE(getNext(elementD) == elementA);

    ASSERT_EQUAL(getValue(elementA), 0);
    ASSERT_EQUAL(getValue(elementB), 1);
    ASSERT_EQUAL(getValue(elementC), 2);
    ASSERT_EQUAL(getValue(elementD), 3);

    removeAllElements(elementA);
}

CTEST(cyclicListTests, removeElementTest) {
    ListElement *elementA = add(NULL, 0);
    ListElement *elementB = add(elementA, 0);
    ListElement *elementC = add(elementB, 0);
    ListElement *elementD = add(elementC, 0);

    removeElement(elementB);
    ASSERT_TRUE(getNext(elementA) == elementC);

    removeElement(elementC);
    ASSERT_TRUE(getNext(elementA) == elementD);

    removeElement(elementD);
    ASSERT_TRUE(getNext(elementA) == elementA);

    removeAllElements(elementA);
}
