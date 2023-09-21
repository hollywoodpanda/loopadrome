#include <stdio.h>
#include <stdlib.h>

#include "./avl_tree.h"

int get_height (Node *node)
{
    
    if (node == NULL) {
        return 0;
    }

    return node->height;


}

Node *create_node (int key)
{
    
    Node *node = (Node*) malloc(sizeof(Node));

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;

}

int max (int some_depth, int other_depth)
{
    
    return  (some_depth > other_depth) ? some_depth : other_depth;

}

int get_balance (Node *node)
{
    
    if (node == NULL) {
        return 0;
    }

    return get_height(node->left) - get_height(node->right);

}

Node *right_rotate (Node *node)
{
    
    Node *left_child = node->left;
    Node *T2 = left_child->right;

    left_child->right = node;
    node->left = T2;

    left_child->height = max(get_height(left_child->right), get_height(left_child->left)) + 1;
    node->height = max(get_height(node->right), get_height(node->left)) + 1;

    return left_child;

}

Node *left_rotate (Node *node)
{
    
    Node *right_child = node->right;
    Node *T2 = right_child->left;

    right_child->left = node;
    node->right = T2;

    node->height = max(get_height(node->right), get_height(node->left)) + 1;
    right_child->height = max(get_height(right_child->right), get_height(right_child->left)) + 1;

    return right_child;
    
}

Node *insert (int key, Node *node)
{
    
    if (node == NULL) {
        return create_node(key);
    }

    if (key < node->key) {
        node->left = insert(key, node->left);
    } else if (key > node->key) {
       node->right = insert(key, node->right);
    }

    node->height = max(get_height(node->left), get_height(node->right)) + 1;

    int balance_factor = get_balance(node);

    // Left - Left
    if (balance_factor > 1 && key < node->left->key) {
        return right_rotate(node);
    }

    // Right - Right
    if (balance_factor < -1 && key > node->right->key) {
        return left_rotate(node);
    }

    // Left - Right
    if (balance_factor > 1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Right - Left
    if (balance_factor < -1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;

}

void pre_order (Node *root_node)
{
    
    if (root_node != NULL) {
        pre_order(root_node->left);
        pre_order(root_node->right);
    }    

}

void destroy_tree (Node *root_node)
{

    if (root_node != NULL) {
        destroy_tree(root_node->left);
        destroy_tree(root_node->right);
        free(root_node);
    }

}