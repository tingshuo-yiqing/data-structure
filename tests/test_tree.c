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
    return 0;
}