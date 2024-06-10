#ifndef ARITH_BINARY_TREE_H
#define ARITH_BINARY_TREE_H

#include "defines.h"

typedef struct TreeNode
{
    void* data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

/**
 * @param  head: should be NULL (not pointing to allocated memory as it will be changed)
 * @param  data: pointer to data to be copied (not moved)
 * @param  bytes: size of data in bytes
 */
void binary_tree_create(TreeNode** head, void* data, u32 bytes);

void binary_tree_free(TreeNode* head);

/**
 * @param  head: pointer to parent node
 * @param  data: pointer to data to be copied (not moved)
 * @param  bytes: size of data in bytes
 */
void binary_tree_insert_left(TreeNode* parent, void* data, u32 bytes);

/**
 * @param  head: pointer to parent node
 * @param  data: pointer to data to be copied (not moved)
 * @param  bytes: size of data in bytes
 */
void binary_tree_insert_right(TreeNode* parent, void* data, u32 bytes);

#endif