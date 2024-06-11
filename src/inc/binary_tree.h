#ifndef ARITH_BINARY_TREE_H
#define ARITH_BINARY_TREE_H

#include "defines.h"

typedef struct TreeNode
{
    struct TreeNode* parent;

    void* data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

/**
 * @param  node: address of pointer to node. should be NULL (not pointing to allocated memory as it will be changed)
 * @param  parent: parent of node, if head then pass NULL
 * @param  data: pointer to data to be copied (not moved)
 * @param  bytes: size of data in bytes
 */
void binary_tree_node_create(TreeNode** node, TreeNode* parent, void* data, u32 bytes);

void binary_tree_free(TreeNode* head);

/**
 * @brief  inserts into left slot first, then right
 * @param  data: pointer to data to be copied (not moved)
 * @param  bytes: size of data in bytes
 */
void binary_tree_insert(TreeNode* parent, void* data, u32 bytes);

/**
 * @brief creates parent with this node as left child
 * @param  data: pointer to data to be copied (not moved)
 * @param  bytes: size of data in bytes
 */
void binary_tree_insert_parent(TreeNode* child, void* data, u32 bytes);

#endif