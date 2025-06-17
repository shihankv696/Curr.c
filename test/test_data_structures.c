#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/linked_list.h"
#include "../include/hashMap.h"

#include "../include/BST.h"

// Print function for Stack
void print(Stack *stk, void (*print_func)(void *)) {
    StackNode *current = stk->top;
    while (current != NULL) {
        print_func(current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Helper print functions for different data types
void print_int(void *data) {
    printf("%d -> ", *(int *)data);
}

void print_string(void *data) {
    printf("%s -> ", (char *)data);
}

void print_queue(Queue *queue, void (*print_func)(void *)) {
    QueueNode *current = queue->front;
    while (current != NULL) {
        print_func(current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Stack test
void test_stack() {
    printf("Testing Stack...\n");
    Stack *stk = stack();

    int a = 10, b = 20, c = 30;
    push(stk, &a, sizeof(int));
    push(stk, &b, sizeof(int));
    push(stk, &c, sizeof(int));

    printf("Stack contents: ");
    print(stk, print_int);

    int *popped = (int *)pop(stk);
    printf("Popped: %d\n", *popped);

    printf("Stack after pop: ");
    print(stk, print_int);
    printf("\n");
}

// Queue test
void test_queue() {
    printf("Testing Queue...\n");
    Queue *que = queue();

    int a = 1, b = 2, c = 3;
    enqueue(que, &a);
    enqueue(que, &b);
    enqueue(que, &c);

    printf("Queue contents: ");
    print_queue(que, print_int);

    int *deq = (int *)dequeue(que);
    printf("Dequeued: %d\n", *deq);

    printf("Queue after dequeue: ");
    print_queue(que, print_int);
    printf("\n");
}

// Linked list test
int cmp_int(void *a, void *b) {
    return (*(int *)a - *(int *)b);
}

void test_linked_list() {
    printf("Testing Linked List...\n");
    Node *head = NULL;

    int a = 5, b = 10, c = 15;
    Insert(&head, &a, sizeof(int));
    Insert(&head, &b, sizeof(int));
    Insert(&head, &c, sizeof(int));

    printf("Linked list contents: ");
    Traverse(head, print_int);
    printf("\n");

    Node *found = Search(head, &b, cmp_int);
    if (found) {
        printf("Found element: %d\n", *(int *)found->data);
    }

    Delete(&head, &b, cmp_int);
    printf("Linked list after deletion: ");
    Traverse(head, print_int);
    printf("\n");

    Reverse(&head);
    printf("Linked list after reverse: ");
    Traverse(head, print_int);
    printf("\n");

    Destroy(&head);
}

// HashMap test
void test_hashmap() {
    printf("Testing HashMap...\n");
    HashMap *map = Hashmap();

    put(map, "one", 1);
    put(map, "two", 2);
    put(map, "three", 3);

    int found;
    int val = get(map, "two", &found);
    if (found) {
        printf("Value for 'two': %d\n", val);
    }

    removeKey(map, "two");
    val = get(map, "two", &found);
    if (!found) {
        printf("'two' key removed successfully\n");
    }

    hashmap_free(map);
}

// BST test
void test_bst() {
    printf("Testing BST...\n");
    BSTNode *root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("InOrder traversal: ");
    inOrder(root);
    printf("\n");

    BSTNode *found = search(root, 40);
    if (found) {
        printf("Found key: %d\n", found->key);
    }

    root = delete(root, 20);
    printf("InOrder after deleting 20: ");
    inOrder(root);
    printf("\n");

    freeTree(root);
}

void test_stack_edge_cases();
void test_queue_edge_cases();
void test_linked_list_edge_cases();
void test_hashmap_edge_cases();
void test_bst_edge_cases();

int main() {
    test_stack();
    test_queue();
    test_linked_list();
    test_hashmap();
    test_bst();

    // Edge case tests
    test_stack_edge_cases();
    test_queue_edge_cases();
    test_linked_list_edge_cases();
    test_hashmap_edge_cases();
    test_bst_edge_cases();

    return 0;
}

// Edge case tests for Stack
void test_stack_edge_cases() {
    printf("Testing Stack Edge Cases...\n");
    Stack *stk = stack();

    // Pop from empty stack
    void *popped = pop(stk);
    if (popped == NULL) {
        printf("Pop from empty stack returned NULL as expected\n");
    }

    // Push NULL data
    push(stk, NULL, 0);
    popped = pop(stk);
    if (popped == NULL) {
        printf("Push and pop NULL data handled correctly\n");
    }

    // Clean up
    free(stk);
}

// Edge case tests for Queue
void test_queue_edge_cases() {
    printf("Testing Queue Edge Cases...\n");
    Queue *que = queue();

    // Dequeue from empty queue
    void *deq = dequeue(que);
    if (deq == NULL) {
        printf("Dequeue from empty queue returned NULL as expected\n");
    }

    // Enqueue NULL data
    enqueue(que, NULL);
    deq = dequeue(que);
    if (deq == NULL) {
        printf("Enqueue and dequeue NULL data handled correctly\n");
    }

    // Clean up
    free(que);
}

// Edge case tests for Linked List
void test_linked_list_edge_cases() {
    printf("Testing Linked List Edge Cases...\n");
    Node *head = NULL;

    // Delete from empty list
    Delete(&head, NULL, NULL);
    printf("Delete from empty list handled correctly\n");

    // Search in empty list
    Node *found = Search(head, NULL, NULL);
    if (found == NULL) {
        printf("Search in empty list returned NULL as expected\n");
    }

    // Insert NULL data
    Insert(&head, NULL, 0);
    if (head == NULL) {
        printf("Insert NULL data handled correctly\n");
    }

    // Clean up
    Destroy(&head);
}

// Edge case tests for HashMap
void test_hashmap_edge_cases() {
    printf("Testing HashMap Edge Cases...\n");
    HashMap *map = Hashmap();

    // Get from empty map
    int found;
    int val = get(map, "nonexistent", &found);
    if (!found) {
        printf("Get from empty map returned not found as expected\n");
    }

    // Remove from empty map
    removeKey(map, "nonexistent");
    printf("Remove from empty map handled correctly\n");

    // Put NULL key
    put(map, NULL, 123);
    val = get(map, NULL, &found);
    if (!found) {
        printf("Put and get NULL key handled correctly\n");
    }

    // Clean up
    hashmap_free(map);
}

// Edge case tests for BST
void test_bst_edge_cases() {
    printf("Testing BST Edge Cases...\n");
    BSTNode *root = NULL;

    // Search in empty tree
    BSTNode *found = search(root, 999);
    if (found == NULL) {
        printf("Search in empty BST returned NULL as expected\n");
    }

    // Delete from empty tree
    root = delete(root, 999);
    printf("Delete from empty BST handled correctly\n");

    // Insert duplicate keys
    root = insert(root, 50);
    root = insert(root, 50);
    printf("Insert duplicate keys handled\n");

    // Clean up
    freeTree(root);
}
