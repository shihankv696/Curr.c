#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"
#include "memory_allocation.h"


BSTNode *insert(BSTNode *root, int key)
{
    if (!root)
    {
        BSTNode *newNode = (BSTNode *)dmalloc(sizeof(BSTNode));
        if (!newNode) {
            // Handle memory allocation failure
            return NULL;
        }

        newNode->key = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

BSTNode* search(BSTNode* root, int key) {
    if (!root || root->key == key) {
        return root;
    }
    return (key < root->key) ? search(root->left, key) : search(root->right, key);
}

BSTNode* min(BSTNode* root) {
    if (!root) return NULL; // Return NULL if the tree is empty

    while (root->left) {
        root = root->left;
    }
    return root;
}

BSTNode* max(BSTNode* root) {
    if (!root) return NULL; // Return NULL if the tree is empty

    while (root->right) {
        root = root->right;
    }
    return root;
}

BSTNode* delete(BSTNode* root, int key) {
    if (!root) {
        return NULL;
    }
    if (key < root->key) {
        root->left = delete(root->left, key);
    } else if (key > root->key) {
        root->right = delete(root->right, key);
    } else {
        if (!root->left) {
            BSTNode *temp = root->right;
            dfree(root);
            return temp;
        } else if (!root->right) {
            BSTNode *temp = root->left;
            dfree(root);
            return temp;
        }

        BSTNode *temp = min(root->right);
        root->key = temp->key;
        root->right = delete(root->right, temp->key);
    }
    return root;
}

void inOrder(BSTNode* root) {
    if (!root)
        return;
    inOrder(root->left);
    printf("%d ", root->key);
    inOrder(root->right);
}

void preOrder(BSTNode* root) {
    if(!root)
        return; 

    printf("%d ", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(BSTNode* root) {
    if (!root)
        return; 

    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->key);
}

void freeTree(BSTNode* root) {
    if (!root)
        return;

    freeTree(root->left);
    freeTree(root->right);
    dfree(root);
}
