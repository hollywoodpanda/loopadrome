#ifndef GAME_AVL_TREE_H
#define GAME_AVL_TREE_H

typedef struct avl_node {
    void *key;
    struct avl_node *left;
    struct avl_node *right;
    int height;
} avl_node;

int get_height (avl_node *node);

avl_node *create_node (void *key);

int max (int some_depth, int other_depth);

int get_balance (avl_node *node);

avl_node *right_rotate (avl_node *node); 

avl_node *left_rotate (avl_node *node);

avl_node *insert (void *key, avl_node *root, int (*compare_fn)(void *value_a, void *value_b));

avl_node *delete (void *key, avl_node *root, int (*compare_fn)(void *value_a, void *value_b));

avl_node *find (void *key, avl_node *root, int (*compare_fn)(void *value_a, void *value_b));

void pre_order (avl_node *root_node, unsigned int node_type);

void destroy_tree (avl_node *root);

#endif