#ifndef BST_H
#define BST_H

#include "utils.h"
#include "memory.h"

typedef int (*bst_cmp_fn)(const void *a, const void *b);

typedef struct BSTNode {
    void *data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef struct {
    BSTNode *root;
    size_t size;
    bst_cmp_fn cmp;
} BST;

BST *bst_creat(bst_cmp_fn cmp);
void bst_destroy(BST *tree, void (*free_data)(void *));

dbool bst_insert(BST *tree, void *data);
void *bst_find(BST *tree, const void *key);
dbool bst_remove(BST *tree, const void *key, void (*free_data)(void *));

void bst_traverse_inorder(BST *tree, void (*visit)(void *));
size_t bst_size(const BST *tree);

#endif