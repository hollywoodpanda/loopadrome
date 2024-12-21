#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"
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

avl_node *create_node (void *data) {
    
    avl_node *node = (avl_node*) malloc(sizeof(avl_node));

    node->data = data;
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

avl_node *insert (void *data, avl_node *root, int (*compare_fn)(void *value_a, void *value_b)) {

    if (root == NULL) {
        
        root = create_node(data);

    } else if (compare_fn(data, root->data) == 1) {

        root->right = insert(data, root->right, compare_fn);

        if (get_balance(root) == -2) {

            if (compare_fn(data, root->right->data) == 1) {

                root = left_rotate(root);

            } else {

                root->right = right_rotate(root->right);
                root = left_rotate(root);


            }

        }

    } else {

        root->left = insert(data, root->left, compare_fn);

        if (get_balance(root) == 2) {

            if (compare_fn(data, root->left->data) == -1) {

                root = right_rotate(root);

            } else {

                root->left = left_rotate(root->left);
                root = right_rotate(root);

            }

        }

    }

    root->height = get_height(root);

    return root;

}

avl_node *delete (void *data, avl_node *root, int (*compare_fn)(void *value_a, void *value_b)) {

    avl_node *temp = NULL;

    if (root == NULL) {
        return NULL;
    }

    if (compare_fn(data, root->data) == 1) {

        root->right = delete(data, root->right, compare_fn);

        if (get_balance(root) == 2) {

            if (get_balance(root->left) >= 0) {
                root = right_rotate(root);
            } else {
                root->left = left_rotate(root->left);
                root = right_rotate(root);
            }

        }

    } else if (compare_fn(data, root->data) == -1) {

        root->left = delete(data, root->left, compare_fn);

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

            root->data = temp->data;
            root->right = delete(temp->data, root->right, compare_fn);

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

avl_node *find (
    void *data, 
    avl_node *root, 
    int (*compare_fn)(void *value_a, void *value_b)
) {

    if (root == NULL) {
        return NULL;
    }

    if (compare_fn(data, root->data) == 1) {

        return find(data, root->right, compare_fn);

    } else if (compare_fn(data, root->data) == -1) {

        return find(data, root->left, compare_fn);

    }

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
        
        printf("%p (height %d)\r\n", node->data, node->height);

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
