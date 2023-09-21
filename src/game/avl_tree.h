#ifndef GAME_AVL_TREE_H
#define GAME_AVL_TREE_H

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int get_height (Node *node);

Node *create_node (int key);

int max (int some_depth, int other_depth);

int get_balance (Node *node);

Node *right_rotate (Node *node);

Node *left_rotate (Node *node);

Node *insert (int key, Node *node);

void pre_order (Node *root_node);

void destroy_tree (Node *root_node);

#endif