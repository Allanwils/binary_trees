#include "binary_trees.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct avl_node {
    int value;
    int height;
    struct avl_node *left;
    struct avl_node *right;
} avl_node_t;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(avl_node_t *node) {
    if (node == NULL) {
        return -1;
    } else {
        return node->height;
    }
}

int balance_factor(avl_node_t *node) {
    if (node == NULL) {
        return 0;
    } else {
        return height(node->left) - height(node->right);
    }
}

avl_node_t *new_node(int value) {
    avl_node_t *node = (avl_node_t*) malloc(sizeof(avl_node_t));
    node->value = value;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

avl_node_t *right_rotate(avl_node_t *node) {
    avl_node_t *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    new_root->height = max(height(new_root->left), height(new_root->right)) + 1;
    return new_root;
}

avl_node_t *left_rotate(avl_node_t *node) {
    avl_node_t *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    new_root->height = max(height(new_root->left), height(new_root->right)) + 1;
    return new_root;
}

avl_node_t *avl_insert(avl_node_t *node, int value) {
    if (node == NULL) {
        return new_node(value);
    }

    if (value < node->value) {
        node->left = avl_insert(node->left, value);
    } else if (value > node->value) {
        node->right = avl_insert(node->right, value);
    } else {
        return node; // value already exists in the tree
    }

    node->height = max(height(node->left), height(node->right)) + 1;
    int bf = balance_factor(node);

    if (bf > 1 && value < node->left->value) {
        return right_rotate(node);
    }

    if (bf < -1 && value > node->right->value) {
        return left_rotate(node);
    }
