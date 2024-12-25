#include <stdio.h>

#include "entryList.h"

int main(void) {
    FILE *file = fopen("list.txt", "r");

    if (file == NULL) {
        printf("couldn't open file\n");
        return 1;
    }

    EntryList *list = NULL;
    if (!readToList(&list, file)) {
        printf("allocation error\n");
        return 1;
    }

    fclose(file);

    printf("type 'n' to sort entries by name (default);\n");
    printf("type 'p' to sort entries by phone number;\n");
    printf("> ");

    SortChoice choice = SORT_BY_NAME;
    char choiceChar = '\0';
    if (scanf("%c", &choiceChar) == 1) {
        choice = choiceChar == 'p' ? SORT_BY_PHONE : SORT_BY_NAME;
    }

    printf("sorted entries by %s:\n", choice == SORT_BY_NAME ? "name" : "phone number");

    sortList(list, choice);
    printList(list, stdout);
    disposeList(list);
}
