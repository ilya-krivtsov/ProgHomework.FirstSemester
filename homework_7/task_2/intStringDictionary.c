#include "intStringDictionary.h"

#include <stdlib.h>

typedef struct Node {
    int key;
    const char *value;
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

static bool createNode(Node **node, int key, const char *value) {
    *node = malloc(sizeof(Node));
    if (*node == NULL) {
        return false;
    }

    (*node)->key = key;
    (*node)->value = value;
    (*node)->left = NULL;
    (*node)->right = NULL;

    return true;
}

static bool addAfterNode(Node *node, int key, const char *value) {
    Node *parent = NULL;
    Node *child = node;
    while (child != NULL) {
        parent = child;
        if (key > parent->key) {
            child = parent->right;
        } else if (key < parent->key) {
            child = parent->left;
        } else {
            parent->value = value;
            return true;
        }
    }

    if (parent == NULL) {
        return false;
    }

    Node **childPointer = key > parent->key ? &parent->right: &parent->left;

    return createNode(childPointer, key, value);
}

bool addToDictionary(IntStringDictionary *dictionary, int key, const char *value) {
    if (dictionary->root == NULL) {
        return createNode(&dictionary->root, key, value);
    }

    return addAfterNode(dictionary->root, key, value);
}

Node *getNode(Node *node, int key) {
    Node *previous = NULL;
    while (true) {
        if (node == NULL) {
            return NULL;
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

    return node;
}

const char *getValue(IntStringDictionary *dictionary, int key) {
    Node *node = getNode(dictionary->root, key);

    return node == NULL ? NULL : node->value;
}

bool containsKey(IntStringDictionary *dictionary, int key) {
    Node *node = getNode(dictionary->root, key);

    return node != NULL;
}

bool removeFromDictionary(IntStringDictionary *dictionary, int key) {
    Node *node = getNode(dictionary->root, key);
    if (node == NULL) {
        return false;
    }

    if (node == dictionary->root) {
        if (node->left == NULL) {
            dictionary->root = node->right;
            return true;
        }

        if (node->right == NULL) {
            dictionary->root = node->left;
            return true;
        }

        Node *rightmostInLeft = NULL; // TODO: add rightmost search
        rightmostInLeft->right = node->right;
        dictionary->root = node->left;

        return true;
    }

    if (node->left == NULL) {
        // TODO: set parents left/right as node->right
        return true;
    }

    if (node->right == NULL) {
        // TODO: set parents left/right as node->left
        return true;
    }

    Node *rightmostInLeft = NULL; // TODO: add rightmost search
    rightmostInLeft->right = node->right;
    // TODO: set parents left/right as node->right
}

void disposeNode(Node *node) {
    if (node == NULL) {
        return;
    }

    disposeNode(node->left);
    disposeNode(node->right);
    free(node);
}

void disposeDictionary(IntStringDictionary *dictionary) {
    disposeNode(dictionary->root);
    free(dictionary);
}
