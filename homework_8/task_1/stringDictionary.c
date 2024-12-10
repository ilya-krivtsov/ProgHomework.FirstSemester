#include "stringDictionary.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    char *value;
    int balance;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct StringDictionary {
    Node *root;
} StringDictionary;

bool createDictionary(StringDictionary **dictionary) {
    *dictionary = malloc(sizeof(StringDictionary));
    if (*dictionary == NULL) {
        return false;
    }

    (*dictionary)->root = NULL;

    return true;
}

static bool createNode(Node **node, const char *key, const char *value) {
    *node = malloc(sizeof(Node));
    if (*node == NULL) {
        return false;
    }

    char *keyCopy = strdup(key);
    if (keyCopy == NULL) {
        return false;
    }
    (*node)->key = keyCopy;

    char *valueCopy = strdup(value);
    if (valueCopy == NULL) {
        return false;
    }
    (*node)->value = valueCopy;

    (*node)->balance = 0;
    (*node)->left = NULL;
    (*node)->right = NULL;

    return true;
}

static void disposeSingleNode(Node *node) {
    free(node->key);
    free(node->value);
    free(node);
}

static Node *rotateLeft(Node *node) {
    Node *right = node->right;
    node->right = right->left;
    right->left = node;

    return right;
}

static Node *rotateRight(Node *node) {
    Node *left = node->left;
    node->left = left->right;
    left->right = node;

    return left;
}

static Node *rotateLeftMajor(Node *node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

static Node *rotateRightMajor(Node *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

static Node *balanceNode(Node *node) {
    if (node->balance == -2) {
        if (node->right->balance <= 0) {
            Node *newNode = rotateLeft(node);
            if (newNode->balance == -1) {
                node->balance = 0;
                newNode->balance = 0;
            } else {
                node->balance = -1;
                newNode->balance = 1;
            }

            return newNode;
        }

        Node *newNode = rotateLeftMajor(node);

        newNode->left->balance = newNode->balance == -1 ? 1 : 0;
        newNode->right->balance = newNode->balance == 1 ? -1 : 0;
        newNode->balance = 0;

        return newNode;
    }

    if (node->balance == 2) {
        if (node->left->balance >= 0) {
            Node *newNode = rotateRight(node);
            if (newNode->balance == 1) {
                node->balance = 0;
                newNode->balance = 0;
            } else {
                node->balance = 1;
                newNode->balance = -1;
            }

            return newNode;
        }

        Node *newNode = rotateRightMajor(node);

        newNode->right->balance = newNode->balance == 1 ? -1 : 0;
        newNode->left->balance = newNode->balance == -1 ? 1 : 0;
        newNode->balance = 0;

        return newNode;
    }

    return node;
}

static Node *insertNode(Node *node, const char *key, const char *value, bool *continueAscending, bool *created) {
    if (node == NULL) {
        Node *newNode = NULL;
        *created = createNode(&newNode, key, value);

        if (!(*created)) {
            *continueAscending = false;
        }

        return newNode;
    }

    int cmp = strcmp(key, node->key);

    if (cmp < 0) {
        node->left = insertNode(node->left, key, value, continueAscending, created);
        if (!(*continueAscending)) {
            return node;
        }

        ++node->balance;
    } else if (cmp > 0) {
        node->right = insertNode(node->right, key, value, continueAscending, created);
        if (!(*continueAscending)) {
            return node;
        }

        --node->balance;
    } else {
        *continueAscending = false;

        free(node->value);

        char *valueCopy = strdup(value);
        if (valueCopy == NULL) {
            *created = false;
        } else {
            node->value = valueCopy;
        }

        return node;
    }

    if (node->balance == 0) {
        *continueAscending = false;
        return node;
    }

    if (abs(node->balance) == 1) {
        return node;
    }

    Node *balanced = balanceNode(node);

    if (balanced->balance == 0) {
        *continueAscending = false;
    }

    return balanced;
}

bool addToDictionary(StringDictionary *dictionary, const char *key, const char *value) {
    bool continueAscending = true;
    bool created = true;

    Node *newRoot = insertNode(dictionary->root, key, value, &continueAscending, &created);
    dictionary->root = newRoot;

    return created;
}

static Node *findNode(Node *node, const char *key) {
    if (node == NULL) {
        return NULL;
    }

    int cmp = strcmp(key, node->key);

    if (cmp < 0) {
        return findNode(node->left, key);
    }

    if (cmp > 0) {
        return findNode(node->right, key);
    }

    return node;
}

const char *getValue(StringDictionary *dictionary, const char *key) {
    Node *node = findNode(dictionary->root, key);

    return node == NULL ? NULL : node->value;
}

bool containsKey(StringDictionary *dictionary, const char *key) {
    return findNode(dictionary->root, key) != NULL;
}

static void swap(char **left, char **right) {
    char *temp = *left;
    *left = *right;
    *right = temp;
}

static Node *deleteNode(Node *node, const char *key, bool *continueAscending, bool *found) {
    if (node == NULL) {
        *continueAscending = false;
        *found = false;
        return NULL;
    }

    int cmp = strcmp(key, node->key);

    if (cmp < 0) {
        node->left = deleteNode(node->left, key, continueAscending, found);

        if (!(*continueAscending)) {
            return node;
        }

        --node->balance;
    } else if (cmp > 0) {
        node->right = deleteNode(node->right, key, continueAscending, found);

        if (!(*continueAscending)) {
            return node;
        }

        ++node->balance;
    } else {
        if (node->left == NULL && node->right == NULL) {
            disposeSingleNode(node);
            return NULL;
        }

        if (node->left == NULL) {
            Node *right = node->right;
            disposeSingleNode(node);
            return right;
        }

        if (node->right == NULL) {
            Node *left = node->left;
            disposeSingleNode(node);
            return left;
        }

        Node *newNode = node->left;
        while (newNode->right != NULL) {
            newNode = newNode->right;
        }

        swap(&node->key, &newNode->key);
        swap(&node->value, &newNode->value);

        node->left = deleteNode(node->left, key, continueAscending, found);

        if (!(*continueAscending)) {
            return node;
        }

        --node->balance;
    }

    if (abs(node->balance) == 1) {
        *continueAscending = false;
        return node;
    }

    if (node->balance == 0) {
        return node;
    }

    Node *balanced = balanceNode(node);

    if (abs(balanced->balance) == 1) {
        *continueAscending = false;
    }

    return balanced;
}

bool removeFromDictionary(StringDictionary *dictionary, const char *key) {
    bool continueAscending = true;
    bool found = true;

    dictionary->root = deleteNode(dictionary->root, key, &continueAscending, &found);

    return found;
}

static void disposeNodeRecursive(Node *node) {
    if (node == NULL) {
        return;
    }

    disposeNodeRecursive(node->left);
    disposeNodeRecursive(node->right);

    disposeSingleNode(node);
}

void disposeDictionary(StringDictionary *dictionary) {
    disposeNodeRecursive(dictionary->root);
    free(dictionary);
}
