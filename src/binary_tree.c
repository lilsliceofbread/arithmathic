#include "binary_tree.h"
#include <memory.h>

/**
 * internal functions
 */

TreeNode* binary_tree_node_create(void* data, u32 bytes);

void binary_tree_create(TreeNode** head, void* data, u32 bytes)
{
    (*head) = binary_tree_node_create(data, bytes); // double pointer so user can't forget to keep pointer and it gets leaked
}

void binary_tree_insert_left(TreeNode* parent, void* data, u32 bytes)
{
    if(parent->left != NULL)
    {
        ARITH_LOG(LOG_ERROR, "attempted to insert into already filled child slot of parent tree node");
        return;
    }

    TreeNode* node = binary_tree_node_create(data, bytes);

    parent->left = node;

}

void binary_tree_insert_right(TreeNode* parent, void* data, u32 bytes)
{
    if(parent->left != NULL)
    {
        ARITH_LOG(LOG_ERROR, "attempted to insert into already filled child slot of parent tree node");
        return;
    }

    TreeNode* node = binary_tree_node_create(data, bytes);

    parent->right = node;

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

TreeNode* binary_tree_node_create(void* data, u32 bytes)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

    node->left = NULL; // no children yet
    node->right = NULL;
    node->data = malloc(bytes);
    if(data != NULL)
    {
        memcpy(node->data, data, bytes);
    }

    return node;
}