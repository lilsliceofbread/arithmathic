#include "binary_tree.h"
#include <memory.h>

void binary_tree_node_create(TreeNode** node, TreeNode* parent, void* data, u32 bytes)
{
    if(*node != NULL)
    {
        ARITH_LOG(LOG_ERROR, "cannot create node because pointer is not NULL");
        return;
    }

    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));

    new_node->parent = parent; // NULL means no parent, yet
    new_node->left = NULL; // no children yet
    new_node->right = NULL;
    new_node->data = malloc(bytes);
    if(data != NULL)
    {
        memcpy(new_node->data, data, bytes);
    }

    *node = new_node;
}

void binary_tree_free(TreeNode* head)
{
    free(head->data);

    if(head->left != NULL)
    {
        binary_tree_free(head->left);
        free(head->left);
    }
    if(head->right != NULL)
    {
        binary_tree_free(head->right);
        free(head->right);
    }
}

void binary_tree_insert(TreeNode* parent, void* data, u32 bytes)
{
    TreeNode* child = NULL;

    if(parent->left == NULL)
    {
        binary_tree_node_create(&child, parent, data, bytes);
        parent->left = child;
        return;
    }

    if(parent->right == NULL)
    {
        binary_tree_node_create(&child, parent, data, bytes);
        parent->right = child;
        return;
    }

    ARITH_LOG(LOG_ERROR, "tree node already has 2 children");
}

void binary_tree_insert_parent(TreeNode* child, void* data, u32 bytes)
{
    TreeNode* parent = NULL;

    if(child->parent != NULL)
    {
        ARITH_LOG(LOG_ERROR, "tree node already has parent");
        return;
    }

    binary_tree_node_create(&parent, NULL, data, bytes);

    child->parent = parent;
    parent->left = child;
}