#include "entryList.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry {
    char *name;
    char *phoneNumber;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *begin;
    Entry *end;
} ListSpan;

typedef struct EntryList {
    ListSpan span;
} EntryList;

static void addToSpan(ListSpan *span, Entry *entry) {
    if (span->begin == NULL) {
        span->begin = entry;
    } else {
        span->end->next = entry;
    }

    span->end = entry;
}

static bool addEntry(EntryList *list, const char *name, const char *phoneNumber) {
    Entry *entry = malloc(sizeof(Entry));
    if (entry == NULL) {
        return false;
    }

    entry->name = strdup(name);
    entry->phoneNumber = strdup(phoneNumber);
    entry->next = NULL;

    addToSpan(&list->span, entry);
    return true;
}

bool readToList(EntryList **list, FILE *stream) {
    EntryList *newList = malloc(sizeof(EntryList));
    if (newList == NULL) {
        return false;
    }

    newList->span.begin = NULL;
    newList->span.end = NULL;

    while (!feof(stream)) {
        char nameBuffer[256] = { 0 };
        char phoneBuffer[256] = { 0 };

        if (fscanf(stream, "%255s - %255s", nameBuffer, phoneBuffer) != 2) {
            break;
        }

        if (!addEntry(newList, nameBuffer, phoneBuffer)) {
            return false;
        }
    }

    *list = newList;

    return true;
}

static int compare(const Entry *left, const Entry *right, SortChoice choice) {
    switch (choice)
    {
    case SORT_BY_NAME:
        return strcmp(left->name, right->name);

    case SORT_BY_PHONE:
        return strcmp(left->phoneNumber, right->phoneNumber);

    default:
        return 0;
    }
}

static ListSpan merge(EntryList *into, ListSpan left, ListSpan right, Entry *entryBefore, SortChoice choice) {
    Entry *entryAfter = right.end->next;

    Entry *leftEntry = left.begin;
    Entry *rightEntry = right.begin;

    left.end->next = NULL;
    right.end->next = NULL;

    ListSpan newSpan = { .begin = NULL, .end = NULL };

    while (!(leftEntry == NULL && rightEntry == NULL)) {
        Entry *leftNext = leftEntry == NULL ? NULL : leftEntry->next;
        Entry *rightNext = rightEntry == NULL ? NULL : rightEntry->next;

        Entry *lesser = leftEntry == NULL
            ? rightEntry
            : (rightEntry == NULL
                ? leftEntry
                : compare(leftEntry, rightEntry, choice) <= 0 ? leftEntry : rightEntry);

        addToSpan(&newSpan, lesser);

        if (lesser == leftEntry) {
            leftEntry = leftNext;
        } else {
            rightEntry = rightNext;
        }
    }

    if (entryBefore != NULL) {
        entryBefore->next = newSpan.begin;
    } else {
        into->span.begin = newSpan.begin;
    }
    newSpan.end->next = entryAfter;
    if (entryAfter == NULL) {
        into->span.end = newSpan.end;
    }

    return newSpan;
}

static ListSpan captureSpan(Entry *firstEntry, int maxLength) {
    ListSpan span = { .begin = firstEntry, .end = firstEntry };
    if (firstEntry->next == NULL) {
        // span is single element, return
        return span;
    }

    for (int i = 1; i < maxLength; ++i) {
        span.end = span.end->next;
        if (span.end->next == NULL) {
            break;
        }
    }
    return span;
}

static void sortStep(EntryList *resultList, int length, SortChoice choice) {
    Entry *lastEntry = resultList->span.begin;
    Entry *entryBeforeLast = NULL;

    int localstep = 0;
    while (true) {
        ListSpan leftSpan = captureSpan(lastEntry, length);
        if (leftSpan.end->next == NULL) {
            // not enough elements to capture rightSpan, and all elements in leftSpan are already sorted in previous step, break
            break;
        }
        ListSpan rightSpan = captureSpan(leftSpan.end->next, length);

        ListSpan mergedSpan = merge(resultList, leftSpan, rightSpan, entryBeforeLast, choice);

        entryBeforeLast = mergedSpan.end;
        lastEntry = entryBeforeLast->next;
        if (lastEntry == NULL) {
            // last element in rightSpan is last element in list, so step is complete, break
            break;
        }

        ++localstep;
    }

    if (localstep == 0) {
        // no merge happened, list sorted
        return;
    }

    sortStep(resultList, length * 2, choice);
}

void sortList(EntryList *list, SortChoice choice) {
    if (list->span.begin == list->span.end) {
        return;
    }

    sortStep(list, 1, choice);
}

void printList(EntryList *list, FILE *stream) {
    Entry *entry = list->span.begin;
    if (entry == NULL) {
        fprintf(stream, "\n");
        return;
    }

    do {
        fprintf(stream, "%s - %s", entry->name, entry->phoneNumber);

        if (entry == list->span.end || entry->next == NULL) {
            fprintf(stream, ".\n");
            break;
        }
        entry = entry->next;
        fprintf(stream, ";\n");
    } while (true);
}

void disposeList(EntryList *list) {
    Entry *last = list->span.begin;
    while (last != NULL) {
        free(last->name);
        free(last->phoneNumber);

        Entry *next = last->next;
        free(last);
        last = next;
    }

    free(list);
}
