前向声明（Forward Declaration）是C/C++中的一个重要概念

## 前向声明的原理

**1. 什么是前向声明？**
前向声明就是告诉编译器："有一个名为XXX的类型存在，但它的具体定义在别处"。编译器只需要知道这个类型的存在，而不需要知道它的完整结构。

**2. 语法示例：**
```c
// 前向声明 - 只声明类型存在
typedef struct TreeNode TreeNode;

// 完整定义 - 在tree.h中
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
```

**3. 为什么需要前向声明？**
- **解决循环依赖**：当A文件需要B文件，B文件也需要A文件时
- **减少编译依赖**：只包含必要的头文件，加快编译速度
- **隐藏实现细节**：只暴露接口，不暴露内部结构


**4. 前向声明的限制：**
- 只能声明指针类型（`TreeNode*`）
- 不能直接使用结构体成员（`node->val`）
- 不能定义结构体变量（`TreeNode node;`）
- 不能使用`sizeof(TreeNode)`

简单来说：前向声明就是"先打个招呼，具体细节后面再说"，这样编译器就知道这个类型存在，可以处理指针操作，但不知道内部结构。