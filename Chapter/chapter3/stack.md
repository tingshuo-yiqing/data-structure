# 栈的C语言实现

## 基础接口
```c
typedef int eletype;   // 栈中元素类型

// 栈结构体
typedef struct stack {
    eletype* data;
    eletype* mindata;
    int top;
    int mintop;
} stack;

stack* initStack();   // 初始化一个栈

void freeStack(stack* st);  // 回收栈

eletype getStackMinVal(stack* st);  // O(1)获取栈中最小值

bool isStackEmpty(stack* st);  // 判空

void pushStack(stack* st, eletype val);  // 弹入一个元素

eletype topStack(stack* st);   // 获取栈顶元素

eletype popStack(stack* st);  // 弹出栈顶元素

void clearStack(stack* st);   // 清空栈
```

