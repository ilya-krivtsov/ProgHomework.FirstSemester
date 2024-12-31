#include <stdbool.h>
#include <stdio.h>

#include "expressionTree.h"

bool readAndEvaluate(FILE *stream) {
    ExpressionTree *tree = NULL;

    if (!readExpressionTree(&tree, stream)) {
        return false;
    }

    printf("tree form:\n");
    printAsTree(tree, stdout);

    printf("expression form:\n");
    printAsExpression(tree, stdout);

    printf("evaluates to %d\n", evaluateExpressionTree(tree));
    printf("\n");
    return true;
}

int main(void) {
    FILE *file = fopen("inputTree.txt", "r");
    if (file == NULL) {
        printf("failed to open file\n");
        return 1;
    }

    while (!feof(file)) {
        if (!readAndEvaluate(file)) {
            printf("failed to evaluate read and evaluate tree\n");
        }

        char value = fgetc(file);
        while (value == '\n') {
            value = fgetc(file);
        }
        ungetc(value, file);
    }
    fclose(file);
}
