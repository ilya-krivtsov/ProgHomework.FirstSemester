#include "intStringDictionary.h"

#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    char *value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct IntStringDictionary {
    Node *root;
} IntStringDictionary;

bool createDictionary(IntStringDictionary **dictionary) {
    *dictionary = malloc(sizeof(IntStringDictionary));
    if (*dictionary == NULL) {
        return false;
    }

    (*dictionary)->root = NULL;

    return true;
}

static bool createNode(Node **node, int key, char *value) {
    *node = malloc(sizeof(Node));
    if (*node == NULL) {
        return false;
    }

    (*node)->key = key;

    char *valueCopy = strdup(value);
    if (valueCopy == NULL) {
        return false;
    }
    (*node)->value = valueCopy;

    (*node)->left = NULL;
    (*node)->right = NULL;

    return true;
}

static bool addAfterNode(Node *node, int key, char *value) {
    Node *parent = NULL;
    Node *child = node;
    while (child != NULL) {
        parent = child;
        if (key > parent->key) {
            child = parent->right;
        } else if (key < parent->key) {
            child = parent->left;
        } else {
            free(parent->value);
            char *valueCopy = strdup(value);
            if (valueCopy == NULL) {
                return false;
            }
            parent->value = valueCopy;
            return true;
        }
    }

    if (parent == NULL) {
        return false;
    }

    Node **childPointer = key > parent->key ? &parent->right: &parent->left;

    return createNode(childPointer, key, value);
}

bool addToDictionary(IntStringDictionary *dictionary, int key, char *value) {
    if (dictionary->root == NULL) {
        return createNode(&dictionary->root, key, value);
    }

    return addAfterNode(dictionary->root, key, value);
}

Node *getNode(Node *node, int key) {
    while (true) {
        if (node == NULL) {
            return NULL;
        }

        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            break;
        }
    }

    return node;
}

char *getValue(IntStringDictionary *dictionary, int key) {
    Node *node = getNode(dictionary->root, key);

    return node == NULL ? NULL : node->value;
}

bool containsKey(IntStringDictionary *dictionary, int key) {
    Node *node = getNode(dictionary->root, key);

    return node != NULL;
}

// returns rightmost child of given node, or node itself if right is NULL
Node *getRightmost(Node *node) {
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

bool removeFromDictionary(IntStringDictionary *dictionary, int key) {
    Node *node = dictionary->root;
    Node *previous = NULL;
    while (true) {
        if (node == NULL) {
            return false;
        }

        if (key < node->key) {
            previous = node;
            node = node->left;
        } else if (key > node->key) {
            previous = node;
            node = node->right;
        } else {
            break;
        }
    }

    if (node == dictionary->root) {
        if (node->left == NULL) {
            dictionary->root = node->right;
            free(node);
            return true;
        }

        if (node->right == NULL) {
            dictionary->root = node->left;
            free(node);
            return true;
        }

        Node *rightmostInLeft = getRightmost(node->left);
        rightmostInLeft->right = node->right;
        dictionary->root = node->left;

        free(node);

        return true;
    }

    Node **setNewNodeTo = key < previous->key ? &previous->left : &previous->right;

    if (node->left == NULL) {
        *setNewNodeTo = node->right;
        free(node);
        return true;
    }

    if (node->right == NULL) {
        *setNewNodeTo = node->left;
        free(node);
        return true;
    }

    Node *rightmostInLeft = getRightmost(node->left);
    rightmostInLeft->right = node->right;
    *setNewNodeTo = node->left;
    free(node);
    return true;
}

void disposeNode(Node *node) {
    if (node == NULL) {
        return;
    }

    disposeNode(node->left);
    disposeNode(node->right);

    free(node->value);
    free(node);
}

void disposeDictionary(IntStringDictionary *dictionary) {
    disposeNode(dictionary->root);
    free(dictionary);
}
