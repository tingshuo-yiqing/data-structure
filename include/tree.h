#ifndef DATASTRUCT_TREE
#define DATASTRUCT_TREE

#ifdef __cplusplus
extern "C" {
#endif

#include "queue.h"

#define NULL_MARKER -1  // 序列化和反序列化时用于空节点标记
#define tree_eletype int

typedef struct TreeNode {
    tree_eletype val;
    struct TreeNode* left;
    struct TreeNode* right;
    int height;  // 树的高度
} TreeNode;

/**
 * @brief Create a binary tree node with the value of val
 * @param val tree_eleetype 
 */
TreeNode* createTreeNode(tree_eletype val);


/**
 * @brief Recursive release of binary tree nodes
 * @param root Root node
 */
void freeBTree(TreeNode* root);


/**
 * @brief Level-order printing of binary tree nodes
 * @param root Root node
 */
void levelOrderBTree(TreeNode* root);


/**
 * @brief PreOrder print binary tree node
 * @param root Root node
 */
void preOrderBTree(TreeNode* root);


/**
 * @brief InOrder print binary tree node
 * @param root Root node
 */
void inOrderBTree(TreeNode* root);


/**
 * @brief PostOrder print binary tree node
 * @param root Root node
 */
void postOrderBTree(TreeNode* root);


/**
 * @brief Recursive calculation of the number of nodes in a binary tree
 * @param root Root node
 * @return The node size of binary tree
 */
int getBTreeNodes(TreeNode* root); 


/**
 * @brief Determine whether two binary trees are the same
 * @param p Root node one
 * @param q Root node two
 * @return true if trees are identical, false otherwise
 */
bool isSameBTree(TreeNode* p, TreeNode* q);


/**
 * @brief Implement binary tree level-order serialization
 * @param root Root node
 * @param serializeSize [out] Output parameter, return the size of the serialized array
 * @return The pointer to the serialized array
 */
tree_eletype* serializeBTree(TreeNode* root, int* serializeSize);


/**
 * @brief Reconstruct binary tree from level-order serialized data
 * @param data Array containing level-order traversal with NULL_MARKER for null nodes
 * @param dataSize Size of the data array
 * @return Root node of the reconstructed binary tree
 */
TreeNode* deserializeBTree(tree_eletype* data, size_t dataSize);


/**
 * @brief 
 */
TreeNode* getBTreeRightChild(TreeNode* root, TreeNode* e);


TreeNode* getBTreeLeftChild(TreeNode* root, TreeNode* e);


/**
 * @brief Find the maximum depth of a binary tree
 * @param root Root node
 */
int maxDepthBTree(TreeNode* root);


/**
 * @brief Find the minimum depth of a binary tree
 * @param root Root node
 */
int minDepthBTree(TreeNode* root);

/**
 * 
 */
TreeNode* invertBTree(TreeNode* root);


/* binary search tree (BST) */

/**
 * @brief
 * @param
 * @param
 * @return 
 */
TreeNode* insertBSTnode(TreeNode* root, tree_eletype val);

/**
 * 
 */
TreeNode* searchBSTval(TreeNode* root, tree_eletype val);


/**
 * @brief Get the node with the minimum value in the BST
 * @param root Root node
 * @return Pointer to the node with the maximum value, or NULL if tree is empty
 * @note Check if it is NULL before use
 */
TreeNode* getBSTminNode(TreeNode* root);


/**
 * @brief Get the node with the maximum value in the BST
 * @param root Root node
 * @return Pointer to the node with the maximum value, or NULL if tree is empty
 * @note Check if it is NULL before use
 */
TreeNode* getBSTmaxNode(TreeNode* root);

/**
 * 
 */
TreeNode* deleteBSTnode(TreeNode* root, tree_eletype val);

/**
 * @brief 
 */
bool isValidBSTdfs(TreeNode* root, long long left_val, long long right_val);
/**
 * 
 */
bool isValidBST(TreeNode* root);



/* AVL Tree */

int getTreeHeight(TreeNode* root);

int getTreeBalance(TreeNode* root);

void updateTreeHeight(TreeNode* root);

TreeNode* leftRotate(TreeNode* root);

TreeNode* rightRotate(TreeNode* root);

TreeNode* insertAVLnode(TreeNode* root, tree_eletype key);


int isValidAVLdfs(TreeNode* root);
bool isValidAVL(TreeNode* root);


/**
 * @brief Delete a node from an AVL tree
 * @param root Root of the tree
 * @param key Value to delete
 * @return New root after deletion
 */
TreeNode* deleteAVLnode(TreeNode* root, tree_eletype key);

#ifdef __cplusplus
}
#endif

#endif
