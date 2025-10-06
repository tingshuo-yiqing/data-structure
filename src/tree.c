#include "tree.h"
#include "memmgr.h"

TreeNode* createTreeNode(tree_eletype val) {
    TreeNode* ret = XMALLOC(sizeof(TreeNode));
    ret->left = NULL;
    ret->right = NULL;
    ret->val = val;
    return ret;
}


void freeBTree(TreeNode* root) {
    if (!root) return;
    freeBTree(root->left);
    freeBTree(root->right);
    XFREE(root);
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

    inOrderBTree(root->left);
    printf("%d ", root->val);
    inOrderBTree(root->right);
}


void postOrderBTree(TreeNode* root) {
    if (root == NULL) return ;

    postOrderBTree(root->left);
    postOrderBTree(root->right);
    printf("%d ", root->val);
}


int getBTreeNodes(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return getBTreeNodes(root->left) + getBTreeNodes(root->right) + 1;
}


bool isSameBTree(TreeNode* p, TreeNode* q) {
    // https://leetcode.cn/problems/same-tree/?envType=problem-list-v2&envId=binary-tree
    if (p == NULL || q == NULL) {
        return p == q;
    }
    return p->val == q->val && isSameBTree(p->left, q->left) && isSameBTree(p->right, q->right);
}


tree_eletype* serializeBTree(TreeNode* root, int* serializeSize) {
    // https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/
    
    //! 这里的二叉树节点数包括了空节点，不能使用getBTreeNodeSize函数求得的节点数
    //! 修改getBTreeNodeSize函数，使其可以空节点+1

    tree_eletype* data = XMALLOC(sizeof(tree_eletype) * 1024);
    if (root == NULL) return NULL;

    queue* q = initQueue();
    pushQueue(q, root);
    int index = 0;

    while (!isQueueEmpty(q)) {
        TreeNode* node = popQueue(q);
        if (node) {
            data[index++] = node->val;
            pushQueue(q, node->left);
            pushQueue(q, node->right);
        } else {
            data[index++] = NULL_MARKER;
        }
    }

    //! 去除末尾多余的空节点标记NULL_MARKER
    while (index > 0 && data[index - 1] == NULL_MARKER) index--;
    *serializeSize = index;

    freeQueue(q);
    return data;
}


TreeNode* deserializeBTree(tree_eletype* data, size_t dataSize) {
    // https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/
    if (dataSize == 0 || data[0] == NULL_MARKER) {
        return NULL;
    }

    TreeNode* root = createTreeNode(data[0]);
    queue* q = initQueue();
    pushQueue(q, root);

    size_t index = 1;
    while (!isQueueEmpty(q) && index < dataSize) {
        TreeNode* node = popQueue(q);

        if (index < dataSize && data[index] != NULL_MARKER) {
            TreeNode* left = createTreeNode(data[index]);
            node->left = left;
            pushQueue(q, left);
        }
        index++;

        if (index < dataSize && data[index] != NULL_MARKER) {
            TreeNode* right = createTreeNode(data[index]);
            node->right = right;
            pushQueue(q, right);
        }
        index++;
    }
    freeQueue(q);
    return root;
}
