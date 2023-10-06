#include <stdio.h>
#include <stdlib.h>

#include "./avl_tree.h"
#include "../constants.h"

int get_height (avl_node *node)
{
    
    int left_height, right_height;

    if (node == NULL) {
        return 0;
    }

    if (node->left == NULL) {
        left_height = 0;
    } else {
        left_height = node->left->height + 1;
    }

    if (node->right == NULL) {
        right_height = 0;
    } else {
        right_height = node->right->height + 1;
    }

    return max(left_height, right_height);

}

avl_node *create_node (void *key) {
    
    avl_node *node = (avl_node*) malloc(sizeof(avl_node));

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

int get_balance (avl_node *node)
{
    
    if (node == NULL) {
        return 0;
    }

    return get_height(node->left) - get_height(node->right);

}

avl_node *right_rotate (avl_node *node)
{
    
    avl_node *left_child = node->left;
    avl_node *T2 = left_child->right;

    left_child->right = node;
    node->left = T2;

    left_child->height = max(get_height(left_child->right), get_height(left_child->left)) + 1;
    node->height = max(get_height(node->right), get_height(node->left)) + 1;

    return left_child;

}

avl_node *left_rotate (avl_node *node)
{
    
    avl_node *right_child = node->right;
    avl_node *T2 = right_child->left;

    right_child->left = node;
    node->right = T2;

    node->height = max(get_height(node->right), get_height(node->left)) + 1;
    right_child->height = max(get_height(right_child->right), get_height(right_child->left)) + 1;

    return right_child;
    
}

avl_node *insert (void *key, avl_node *root, int (*compare_fn)(void *value_a, void *value_b)) {

    if (root == NULL) {
        return create_node(key);
    }
    
    if (compare_fn(key, root->key) == -1) {
        root->left = insert(key, root->left, compare_fn);
    } else if (compare_fn(key, root->key) == 1) {
        root->right = insert(key, root->right, compare_fn);
    } else {
        return root;
    }

    root->height = 1 + max(get_height(root->left), get_height(root->right));
    
    int balance = get_balance(root);

    if (balance > 1 && compare_fn(key, root->left->key) == -1) {
        return right_rotate(root);
    }

    if (balance < -1 && compare_fn(key, root->right->key) == 1) {
        return left_rotate(root);
    }

    if (balance > 1 && compare_fn(key, root->left->key) == 1) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && compare_fn(key, root->right->key) == -1) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;

}

avl_node *delete (void *key, avl_node *root, int (*compare_fn)(void *value_a, void *value_b)) {

    avl_node *temp = NULL;

    if (root == NULL) {
        return NULL;
    }

    if (compare_fn(key, root->key) == 1) {

        root->right = delete(key, root->right, compare_fn);

        if (get_balance(root) == 2) {

            if (get_balance(root->left) >= 0) {
                root = right_rotate(root);
            } else {
                root->left = left_rotate(root->left);
                root = right_rotate(root);
            }

        }

    } else if (compare_fn(key, root->key) == -1) {

        if (get_balance(root) == -2) {

            if (get_balance(root->right) <= 0) {
                root = left_rotate(root);
            } else {
                root->right = right_rotate(root->right);
                root = left_rotate(root);
            }

        }

    } else {

        if (root->right != NULL) {

            temp = root->right;

            while (temp->left != NULL) {
                temp = temp->left;
            }

            root->key = temp->key;
            root->right = delete(temp->key, root->right, compare_fn);

            if (get_balance(root) == 2) {

                if (get_balance(root->left) >= 0) {
                    root = right_rotate(root);
                } else {
                    root->left = left_rotate(root->left);
                    root = right_rotate(root);
                }

            }

        } else {
            return root->left;
        }

    }

    root->height = get_height(root);

    return root;


}

void pre_order (avl_node *node, unsigned int node_type) {

    if (node != NULL) {

        switch (node_type) {
            case NODE_TYPE_LEFT:
                printf("/ ");
                break;
            case NODE_TYPE_RIGHT:
                printf("\\ ");
                break;
            default:
                break;
        }
        
        printf("%p (height %d)\r\n", node->key, node->height);

        pre_order(node->left, NODE_TYPE_LEFT);
        pre_order(node->right, NODE_TYPE_RIGHT);

    }

}

void destroy_tree (avl_node *root)
{

    if (root != NULL) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root);
    }

}

int compare_nodes (
    avl_node *node_a, 
    avl_node *node_b, 
    int (*compare_fn)(avl_node *node_a, avl_node *node_b)
) {

    return compare_fn(node_a, node_b);

}