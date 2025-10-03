#ifndef TREE_H
#define TREE_H

#include "utils.h"
#include "memory.h"

typedef struct TreeNode {
    void *data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    TreeNode *root;
    size_t size;
} BinaryTree;

BinaryTree *bt_create(void);
void bt_destroy(BinaryTree *t, void (*free_data)(void *));

void bt_preorder(BinaryTree *t, void (*visit)(void *));
void bt_inorder(BinaryTree *t, void (*visit)(void *));
void bt_postorder(BinaryTree *t, void (*visit)(void *));

size_t bt_size(const BinaryTree *t);

#endif