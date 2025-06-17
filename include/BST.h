#ifndef BST_H
#define BST_H

typedef struct BSTNode
{
    int key;
    struct BSTNode *left, *right;
} BSTNode;

BSTNode *insert(BSTNode *root, int key);
BSTNode *search(BSTNode *root, int key);
BSTNode *delete(BSTNode *root, int key);
BSTNode *min(BSTNode *root);
BSTNode *max(BSTNode *root);
void inOrder(BSTNode *root);
void preOrder(BSTNode *root);
void postOrder(BSTNode *root);
void freeTree(BSTNode *root);

#endif
