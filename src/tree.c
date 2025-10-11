#include "tree.h"
#include "memmgr.h"
#include "myfunction.h"

TreeNode* createTreeNode(tree_eletype val) {
    TreeNode* ret = XMALLOC(sizeof(TreeNode));
    ret->left = NULL;
    ret->right = NULL;
    ret->val = val;
    ret->height = 1;
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
    printf("\n");
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



TreeNode* getBTreeRightChild(TreeNode* root, TreeNode* e) {
    if (!root) return NULL;
    if (e->right) 
        return e->right;
    return NULL;
}


TreeNode* getBTreeLeftChild(TreeNode* root, TreeNode* e) {
    if (!root) return NULL;
    if (e->left) 
        return e->left;
    return NULL;
}


int maxDepthBTree(TreeNode* root) {
    // https://leetcode.cn/problems/maximum-depth-of-binary-tree/
    if (!root) return 0;
    return MAX(maxDepthBTree(root->left), maxDepthBTree(root->right)) + 1;
}


int minDepthBTree(TreeNode* root) {
    // https://leetcode.cn/problems/minimum-depth-of-binary-tree/description/?envType=problem-list-v2&envId=binary-tree
    if (!root) return 0;
    if (!root->left) 
        return minDepthBTree(root->right) + 1;
    if (!root->right) 
        return minDepthBTree(root->left) + 1;
    return MIN(minDepthBTree(root->left), minDepthBTree(root->right)) + 1;
}


TreeNode* invertBTree(TreeNode* root) {
    // https://leetcode.cn/problems/invert-binary-tree/
    if (!root) return NULL;

    queue* q = initQueue();
    pushQueue(q, root);

    while (!isQueueEmpty(q)) {
        TreeNode* node = popQueue(q);
        SWAP(node->left, node->right);
        if (node->left) {
            pushQueue(q, node->left);
        }
        if (node->right) {
            pushQueue(q, node->right);
        }
    }
    freeQueue(q);
    return root;
}


/* BST API */


TreeNode* insertBSTnode(TreeNode* root, tree_eletype val) {
    // https://leetcode.cn/problems/insert-into-a-binary-search-tree/description/
    if (!root)
        return createTreeNode(val);
    
    if (val < root->val)
        root->left = insertBSTnode(root->left, val);
    if (val > root->val)
        root->right = insertBSTnode(root->right, val);
    
    return root;
}


TreeNode* searchBSTval(TreeNode* root, tree_eletype val) {
    // https://leetcode.cn/problems/search-in-a-binary-search-tree/
    if (!root) return NULL;

    if (val < root->val)
        return searchBSTval(root->left, val);
    else if (val > root->val)
        return searchBSTval(root->right, val);
    else
        return root;
}


TreeNode* getBSTminNode(TreeNode* root) {
    // value propagation
    while (root->left) {
        root = root->left;
    } 
    return root;
}


TreeNode* getBSTmaxNode(TreeNode* root) {
    while (root->right) {
        root = root->right;
    } 
    return root;
}


TreeNode* deleteBSTnode(TreeNode* root, tree_eletype val) {
    // https://leetcode.cn/problems/delete-node-in-a-bst/description/
    if (!root) return NULL;
    // search val
    if (val < root->val)
        root->left = deleteBSTnode(root->left, val);
    else if (val > root->val)
        root->right = deleteBSTnode(root->right, val);
    else {
        // delete val
        if (!root->left) {
            TreeNode* r = root->right;
            XFREE(root);
            return r;
        }
        if (!root->right) {
            TreeNode* l = root->left;
            XFREE(root);
            return l;
        }   
        TreeNode* minNode = getBSTminNode(root->right);
        root->val = minNode->val;
        root->right = deleteBSTnode(root->right, minNode->val);
    }
    return root;
}


bool isValidBSTdfs(TreeNode* root, long long left_val, long long right_val) {
    if (!root) return true;
    long long x = root->val;
    return (left_val < x && x < right_val) && 
            isValidBSTdfs(root->left, left_val, x) &&
            isValidBSTdfs(root->right, x, right_val);
}
bool isValidBST(TreeNode* root) {
    // https://leetcode.cn/problems/validate-binary-search-tree/
    return isValidBSTdfs(root, LLONG_MIN, LLONG_MIN);
}


/* AVL Tree */

int getTreeHeight(TreeNode* root) {
    return root ? root->height : 0;
}


int getTreeBalance(TreeNode* root) {
    if (!root) return 0;
    return getTreeHeight(root->left) - getTreeHeight(root->right);
}


void updateTreeHeight(TreeNode* root) {
    if (root)
        root->height = MAX(getTreeHeight(root->left), getTreeHeight(root->right)) + 1;
}


TreeNode* leftRotate(TreeNode* root) {
    TreeNode* new_root = root->right;
    TreeNode* T2 = new_root->left;

    new_root->left = root;
    root->right = T2;

    updateTreeHeight(root);
    updateTreeHeight(new_root);
    return new_root;
}


TreeNode* rightRotate(TreeNode* root) {
    TreeNode* new_root = root->left;
    TreeNode* T2 = new_root->right;

    new_root->right = root;
    root->left = T2;

    updateTreeHeight(root);
    updateTreeHeight(new_root);
    return new_root;
}


TreeNode* insertAVLnode(TreeNode* root, tree_eletype key) {
    // 1.Perform standard BST insertion.
    if (!root)
        return createTreeNode(key);
    if (key < root->val)
        root->left = insertAVLnode(root->left, key);
    else if (key > root->val) 
        root->right = insertAVLnode(root->right, key);
    else
        return root;  // no duplicates
    
    // 2.Update the current node height
    updateTreeHeight(root);
    // 3.Check for balance
    int balance = getTreeBalance(root);

    // Based on the condition of the position of the inserted key
    // LL
    if (balance > 1 && key < root->left->val) 
        return rightRotate(root);
    // LR
    if (balance > 1 && key > root->left->val) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RR
    if (balance < -1 && key > root->right->val)
        return leftRotate(root);
    // RL
    if (balance < -1 && key < root->right->val) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}


int isValidAVLdfs(TreeNode* root) {
    if (!root) return 0;
    int left = isValidAVLdfs(root->left);
    int right = isValidAVLdfs(root->right);
    if (left == -1 || right == -1 || ABS(left - right) > 1) 
        return -1;
    return MAX(left, right) + 1;
}
bool isValidAVL(TreeNode* root) {
    // https://leetcode.cn/problems/balanced-binary-tree/description/
    return isValidAVLdfs(root) != -1;
}


TreeNode* deleteAVLnode(TreeNode* root, tree_eletype key) {
    // Perform standard BST deletion
    if (!root) return NULL;
    if (key < root->val) 
        root->left = deleteAVLnode(root->left, key);
    else if (key > root->val) 
        root->right = deleteAVLnode(root->right, key);
    else {
        if (!root->left) {
            TreeNode* r = root->right;
            XFREE(root);
            return r;
        }
        if (!root->right) {
            TreeNode* l = root->left;
            XFREE(root);
            return l;
        }
        TreeNode* minNode = getBSTminNode(root->right);
        root->val = minNode->val;
        root->right = deleteAVLnode(root->right, minNode->val);
    }

    updateTreeHeight(root);
    int balance = getTreeBalance(root);

    int leftBalance = getTreeBalance(root->left);
    int rightBalance = getTreeBalance(root->right);
    // LL
    if (balance > 1 && leftBalance >= 0) 
        return rightRotate(root);
    // LR
    if (balance > 1 && leftBalance < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RR
    if (balance < -1 && rightBalance <= 0)
        return leftRotate(root);
    // RL
    if (balance < -1 && rightBalance > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}