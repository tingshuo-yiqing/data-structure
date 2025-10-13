
## typedef

### 概念

typedef 是 C 语言中用于为现有类型创建别名的关键字，可以提高代码的可读性和可移护性。

**基本语法：**
```c
typedef 原类型 新类型名;
```
#### 结构体的应用

#### 函数指针的应用


## static

### 概念

在普通函数前面加上`static`关键字，可以使其**具有内部链接(internal linkage)**性质，这个性质使其只能在**当前源文件**中使用，不会暴露给别的 .c 文件。即起到修改作用域和生命周期(局部变量)的作用。

#### 生命周期
```c
#include <stdio.h>

void func() {
    static int a = 5;
    int b = 5;
    a++; b++;
    printf("%d %d\n", a, b);
}

int main() {
    func();  // 6 6
    func();  // 7 6
    func();  // 8 6
    return 0;
}

```
`a` 为静态局部变量，只初始化一次，每次调用累加；`b` 为普通局部变量，每次重新创建。


## inline

### 概念

在普通函数前面加上`inline`关键字，作用是将一个函数的代码直接嵌套到它调用的地方，而不是进行常规的函数式调用。

主要好处是**性能提升**，省去了调用函数时的开销。常替代一些简单的宏用于辅助函数。

不过`inline`只是一个建议，不是命令。编译器会根据函数的大小、复杂度、可读性等等来决定是否执行。

### 示例

```c
// 构建堆的辅助函数
#define PARENT(i) (((i) - 1) / 2)
#define LEFT(i)   ((i) * 2 + 1)
#define RIGHT(i)  ((i) * 2 + 2)

// 推荐替代宏，写成inline函数
static inline size_t parent(size_t i) { return (i - 1) / 2; }
static inline size_t left(size_t i)   { return i * 2 + 1; }
static inline size_t right(size_t i)  { return i * 2 + 2; }
```