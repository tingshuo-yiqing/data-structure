#include "tree.h"
#include "memmgr.h"

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

    printf("======AVL树的插入操作======\n");
    tree_eletype avl_test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    size_t avl_size = sizeof(avl_test) / sizeof(avl_test[0]);
    
    TreeNode* avl_root = NULL;
    for (size_t i = 0; i < avl_size; ++i) {
        avl_root = insertAVLnode(avl_root, avl_test[i]);
    }
    levelOrderBTree(avl_root);
    preOrderBTree(avl_root);
    printf("\n");
    inOrderBTree(avl_root);
    printf("\n");
    postOrderBTree(avl_root);
    printf("\n");
    
    if (isValidAVL(avl_root)) 
        printf("这是一棵AVL树\n");
    else   
        printf("这不是一棵AVL树\n");
    
    printf("======AVL树的删除操作======\n");
    
    // 测试AVL树删除操作
    tree_eletype avl_delete_test[] = {10, 20, 30, 40, 50, 25};
    size_t avl_delete_size = sizeof(avl_delete_test) / sizeof(avl_delete_test[0]);
    
    TreeNode* avl_delete_root = NULL;
    printf("构建AVL树: ");
    for (size_t i = 0; i < avl_delete_size; ++i) {
        avl_delete_root = insertAVLnode(avl_delete_root, avl_delete_test[i]);
        printf("%d ", avl_delete_test[i]);
    }
    printf("\n");
    
    printf("删除前中序遍历: ");
    inOrderBTree(avl_delete_root);
    printf("\n");
    printf("删除前层序遍历: ");
    levelOrderBTree(avl_delete_root);
    
    // 测试删除叶子节点
    printf("删除叶子节点40: ");
    avl_delete_root = deleteAVLnode(avl_delete_root, 40);
    inOrderBTree(avl_delete_root);
    printf("\n");
    printf("删除后层序遍历: ");
    levelOrderBTree(avl_delete_root);
    
    // 测试删除有一个子节点的节点
    printf("删除有一个子节点的节点20: ");
    avl_delete_root = deleteAVLnode(avl_delete_root, 20);
    inOrderBTree(avl_delete_root);
    printf("\n");
    printf("删除后层序遍历: ");
    levelOrderBTree(avl_delete_root);
    
    // 测试删除有两个子节点的节点
    printf("删除有两个子节点的节点30: ");
    avl_delete_root = deleteAVLnode(avl_delete_root, 30);
    inOrderBTree(avl_delete_root);
    printf("\n");
    printf("删除后层序遍历: ");
    levelOrderBTree(avl_delete_root);
    
    // 验证删除后仍然是AVL树
    if (isValidAVL(avl_delete_root)) 
    printf("删除操作后仍然是一棵AVL树\n");
    else   
    printf("删除操作后不是一棵AVL树\n");
    
    // 测试删除不存在的节点
    printf("删除不存在的节点100: ");
    avl_delete_root = deleteAVLnode(avl_delete_root, 100);
    inOrderBTree(avl_delete_root);
    printf("\n");
    
    // 测试删除根节点
    printf("删除根节点: ");
    avl_delete_root = deleteAVLnode(avl_delete_root, avl_delete_root->val);
    if (avl_delete_root) {
        inOrderBTree(avl_delete_root);
        printf("\n");
        printf("删除根节点后层序遍历: ");
        levelOrderBTree(avl_delete_root);
    } else {
        printf("树为空\n");
    }
    
    // 验证最终状态
    if (avl_delete_root && isValidAVL(avl_delete_root)) 
    printf("最终状态仍然是一棵AVL树\n");
    else if (avl_delete_root)   
    printf("最终状态不是一棵AVL树\n");
    else
    printf("树为空\n");

    
    // 释放所有分配的内存
    freeBTree(root);
    freeBTree(foo);
    freeBTree(testroot);
    freeBTree(test1root);
    freeBTree(avl_root);
    freeBTree(avl_delete_root);
    XFREE(data);

    return 0;
}
