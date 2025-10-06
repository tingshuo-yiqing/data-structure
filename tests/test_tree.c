#include "tree.h"

int main() {
    tree_eletype nums[] = {1, 2, 3, -1, -1, 4, 5};
    size_t numsSize = sizeof(nums) / sizeof(nums[0]);

    TreeNode* root = deserializeBTree(nums, numsSize);

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
    printf("\n");
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
    
    return 0;
}