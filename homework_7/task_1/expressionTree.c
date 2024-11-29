#include "expressionTree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ExpressionNode {
    int value;
    struct ExpressionNode *left;
    struct ExpressionNode *right;
} ExpressionNode;

typedef struct ExpressionTree {
    ExpressionNode *root;
} ExpressionTree;

// return `true` if read, `false` if stream ended
static bool readChar(FILE *stream, char *value) {
    int readResult = fgetc(stream);
    if (readResult == EOF) {
        return false;
    }
    *value = (char)readResult;
    return true;
}

static void trimWhiteSpace(FILE *stream) {
    while (true) {
        int value = fgetc(stream);
        if (value == EOF) {
            return;
        }
        if (value != ' ') {
            ungetc(value, stream);
            return;
        }
    }
}

static bool readNode(FILE *stream, ExpressionNode **node);

static bool readArgument(FILE *stream, ExpressionNode **argument) {
    trimWhiteSpace(stream);

    char currentChar = '\0';
    if (!readChar(stream, &currentChar)) {
        return false;
    }

    ungetc(currentChar, stream);

    if (currentChar == '(') {
        return readNode(stream, argument);
    }

    int value = 0;
    if (fscanf(stream, "%d", &value) != 1) {
        return false;
    }

    ExpressionNode *node = malloc(sizeof(ExpressionNode));
    if (node == NULL) {
        return false;
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;

    *argument = node;

    return true;
}

static bool readNode(FILE *stream, ExpressionNode **node) {
    ExpressionNode *newNode = malloc(sizeof(ExpressionNode));
    if (newNode == NULL) {
        return false;
    }

    trimWhiteSpace(stream);

    char currentChar = '\0';
    if (!readChar(stream, &currentChar)) {
        return false;
    }

    if (currentChar != '(') {
        return false;
    }

    trimWhiteSpace(stream);

    if (!readChar(stream, &currentChar)) {
        return false;
    }

    if (!(currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/')) {
        return false;
    }

    newNode->value = currentChar;

    if (!readArgument(stream, &newNode->left) || !readArgument(stream, &newNode->right)) {
        return false;
    }

    if (!readChar(stream, &currentChar)) {
        return false;
    }

    if (currentChar != ')') {
        return false;
    }

    *node = newNode;

    return true;
}

bool readExpressionTree(ExpressionTree **tree, FILE *stream) {
    ExpressionTree *newTree = malloc(sizeof(ExpressionTree));
    if (newTree == NULL) {
        return false;
    }

    if (!readNode(stream, &newTree->root)) {
        free(newTree);
        return false;
    }

    *tree = newTree;

    return true;
}

static void printNodeAsTree(ExpressionNode *node, FILE *stream, int depth) {
    if (depth != 0) {
        fprintf(stream, " |");
    }

    for (int i = 1; i < depth; ++i) {
        fprintf(stream, "  |");
    }

    if (depth != 0) {
        fprintf(stream, "-");
    }

    bool isValue = node->left == NULL || node->left == NULL;

    if (isValue) {
        fprintf(stream, "[%d]\n", node->value);
    } else {
        fprintf(stream, "(%c)\n", node->value);
        printNodeAsTree(node->left, stream, depth + 1);
        printNodeAsTree(node->right, stream, depth + 1);
    }
}

static void printNodeAsExpression(ExpressionNode *node, FILE *stream, bool firstNode) {
    bool isValue = node->left == NULL || node->left == NULL;

    if (isValue) {
        fprintf(stream, "%d", node->value);
    } else {
        fprintf(stream, "(");
        printNodeAsExpression(node->left, stream, false);
        fprintf(stream, " %c ", node->value);
        printNodeAsExpression(node->right, stream, false);
        fprintf(stream, ")");
    }
    if (firstNode) {
        fprintf(stream, "\n");
    }
}

void printAsTree(ExpressionTree *tree, FILE *stream) {
    printNodeAsTree(tree->root, stream, 0);
}

void printAsExpression(ExpressionTree *tree, FILE *stream) {
    printNodeAsExpression(tree->root, stream, true);
}

int evaluateNode(ExpressionNode *node) {
    if (node->left == NULL || node->right == NULL) {
        return node->value;
    }

    int left = evaluateNode(node->left);
    int right = evaluateNode(node->right);
    switch (node->value) {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    }

    return 0;
}

int evaluateExpressionTree(ExpressionTree *tree) {
    return evaluateNode(tree->root);
}

void disposeNode(ExpressionNode *node) {
    if (node == NULL) {
        return;
    }
    disposeNode(node->left);
    disposeNode(node->right);

    free(node);
}

void disposeTree(ExpressionTree *tree) {
    disposeNode(tree->root);
    free(tree);
}
