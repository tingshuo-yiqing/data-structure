#ifndef DATASTRUCT_TREE
#define DATASTRUCT_TREE

#include "queue.h"

#define NULL_MARKER -1  // 空节点标记
#define tree_eletype int

typedef struct TreeNode {
    tree_eletype val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

/**
 * @brief 
 */
TreeNode* creatTreeNode(tree_eletype val);


/**
 * @brief Level-order printing of binary tree nodes
 * @param root Root node
 */
void levelOrderBTree(TreeNode* root);


/**
 * @brief
 * @param
 */
void preOrderBTree(TreeNode* root);


void inOrderBTree(TreeNode* root);


void postOrderBTree(TreeNode* root);


tree_eletype* serializeBTree(TreeNode* root);

TreeNode* deserializeBTree(tree_eletype* data, size_t dataSize);


#endif