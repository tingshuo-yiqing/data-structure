#include "tree.h"


TreeNode* creatTreeNode(tree_eletype val) {
    TreeNode* ret = (TreeNode*)malloc(sizeof(TreeNode));
    ret->left = NULL;
    ret->right = NULL;
    ret->val = val;
    return ret;
}


void levelOrderBTree(TreeNode* root) {
    if (root == NULL) return ;

    queue* q = initQueue();
    pushQueue(q, root);

    while (!isQueueEmpty(q)) {
        TreeNode* node = popQueue(q);
        printf("%d ", node->val);
        if (node->left) {
            pushQueue(q, node->left);
        }
        if (node->right) {
            pushQueue(q, node->right);
        }
    }
}


void preOrderBTree(TreeNode* root) {
    if (root == NULL) return ;

    printf("%d ", root->val);
    preOrderBTree(root->left);
    preOrderBTree(root->right);
}


void inOrderBTree(TreeNode* root) {
    if (root == NULL) return ;

    preOrderBTree(root->left);
    printf("%d ", root->val);
    preOrderBTree(root->right);
}


void postOrderBTree(TreeNode* root) {
    if (root == NULL) return ;

    preOrderBTree(root->left);
    preOrderBTree(root->right);
    printf("%d ", root->val);
}


TreeNode* deserializeBTree(tree_eletype* data, size_t dataSize) {
    if (dataSize == 0 || data[0] == NULL_MARKER) {
        return NULL;
    }

    // 
    TreeNode* root = creatTreeNode(data[0]);
    queue* q = initQueue();
    pushQueue(q, root);

    size_t index = 1;
    while (!isQueueEmpty(q) && index < dataSize) {
        TreeNode* node = popQueue(q);

        if (index < dataSize && data[index] != NULL_MARKER) {
            TreeNode* left = creatTreeNode(data[index]);
            node->left = left;
            pushQueue(q, left);
        }
        index++;

        if (index < dataSize && data[index] != NULL_MARKER) {
            TreeNode* right = creatTreeNode(data[index]);
            node->right = right;
            pushQueue(q, right);
        }
        index++;
    }
    freeQueue(q);
    return root;
}