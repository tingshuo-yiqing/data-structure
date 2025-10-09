#include "tree.h"

int main() {
    tree_eletype nums[] = {1, 2, 5, 3, 4, -1, 6};
    size_t numsSize = sizeof(nums) / sizeof(nums[0]);
    
    // tree_eletype foo_arr[] = {1};
    // size_t foo_arr_size = sizeof(foo_arr) / sizeof(foo_arr[0]);

    TreeNode* root = deserializeBTree(nums, numsSize);
    // TreeNode* foo = deserializeBTree(foo_arr, foo_arr_size);

    printf("======四序遍历======\n");
    printf("先序: ");
    preOrderBTree(root);
    printf("\n");
    printf("中序: ");
    inOrderBTree(root);
    printf("\n");
    printf("后序: ");
    postOrderBTree(root);
    printf("\n");
    printf("层序: ");
    levelOrderBTree(root);
    printf("二叉树节点个数为:%d\n", getBTreeNodes(root));
    
    printf("======序列化======\n");
    int serializeSize;
    tree_eletype* data = serializeBTree(root, &serializeSize);
    for (int i = 0; i < serializeSize; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    printf("======判断相同二叉树======\n");
    TreeNode* foo = deserializeBTree(data, serializeSize);
    if (isSameBTree(root, foo)) {
        printf("root和foo是相同结构的二叉树\n");
    } else {
        printf("root和foo是不相同结构的二叉树\n");
    }
    
    printf("======二叉树最大深度======\n");
    printf("%d\n", maxDepthBTree(root));
    printf("======二叉树最小深度======\n");
    printf("%d\n", minDepthBTree(root));
    
    printf("======BST的插入操作======\n");
    tree_eletype test[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    size_t testSize = sizeof(test) / sizeof(test[0]);
    
    TreeNode* testroot = NULL;
    
    for (size_t i = 0; i < testSize; ++i) {
        testroot = insertBSTnode(testroot, test[i]);
    }
    
    inOrderBTree(testroot);
    printf("\n");
    
    TreeNode* max_node = getBSTmaxNode(testroot);
    TreeNode* min_node = getBSTminNode(testroot);
    if (min_node)
    printf("testroot的最小值为%d\n", min_node->val);
    else
    printf("这是一颗空树\n");
    if (max_node)
    printf("testroot的最大值为%d\n", max_node->val);
    else
    printf("这是一颗空树\n");
    
    printf("======二叉树的翻转操作======\n");
    tree_eletype test1[] = {20, 10, 50, 8, 15, 42, 60, -1, -1, -1, -1, 32};
    size_t test1Size = sizeof(test1) / sizeof(test1[0]);

    TreeNode* test1root = deserializeBTree(test1, test1Size);
    levelOrderBTree(test1root);
    invertBTree(test1root);
    levelOrderBTree(test1root);
    return 0;
}