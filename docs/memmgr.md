# 内存管理模块文档

## 概述

内存管理模块提供了一套安全的动态内存分配和释放函数，包含调试信息输出功能，帮助检测内存分配失败和空指针释放等问题。

## 主要特性

- 内存分配失败时输出错误信息并退出程序
- 释放空指针时输出警告信息
- 支持调试模式下的内存分配/释放跟踪
- 自动将释放后的指针设为NULL，防止悬空指针

## API 函数

### 核心函数

#### `void* xmalloc_debug(size_t size, const char* file, int line)`
- **功能**: 带调试信息的内存分配函数
- **参数**: 
  - `size`: 要分配的内存大小（字节）
  - `file`: 调用该函数的源文件名（通常使用 `__FILE__`）
  - `line`: 调用该函数的行号（通常使用 `__LINE__`）
- **返回值**: 指向分配内存的指针
- **行为**:
  - 分配成功：返回内存指针
  - 分配失败：输出错误信息到stderr并调用 `exit(EXIT_FAILURE)` 终止程序

#### `void xfree_debug(void* ptr, const char* file, int line)`
- **功能**: 带调试信息的内存释放函数
- **参数**: 
  - `ptr`: 要释放的内存指针
  - `file`: 调用该函数的源文件名（通常使用 `__FILE__`）
  - `line`: 调用该函数的行号（通常使用 `__LINE__`）
- **行为**:
  - 如果 `ptr` 为NULL：输出警告信息到stderr
  - 如果 `ptr` 不为NULL：释放内存

### 便捷宏

#### `XMALLOC(size)`
- **功能**: 内存分配宏，自动填充文件名和行号
- **参数**: 
  - `size`: 要分配的内存大小
- **展开**: `xmalloc_debug(size, __FILE__, __LINE__)`
- **使用示例**:
  ```c
  int* arr = XMALLOC(10 * sizeof(int));
  ```

#### `XFREE(ptr)`
- **功能**: 内存释放宏，自动填充文件名和行号，并将指针设为NULL
- **参数**: 
  - `ptr`: 要释放的内存指针
- **展开**: 
  ```c
  do { \
      xfree_debug(ptr, __FILE__, __LINE__); \
      (ptr) = NULL; \
  } while(0)
  ```
- **使用示例**:
  ```c
  XFREE(arr);  // 释放内存并将arr设为NULL
  ```

## 使用示例

### 基础使用

```c
#include "memmgr.h"

int main() {
    // 分配内存
    int* numbers = XMALLOC(5 * sizeof(int));
    
    // 使用内存
    for (int i = 0; i < 5; i++) {
        numbers[i] = i * 10;
    }
    
    // 释放内存（自动设为NULL）
    XFREE(numbers);
    
    // 此时 numbers 为 NULL，避免悬空指针
    if (numbers == NULL) {
        printf("指针已安全释放\n");
    }
    
    return 0;
}
```

### 错误处理示例

```c
#include "memmgr.h"

void risky_allocation() {
    // 尝试分配极大内存（可能失败）
    void* huge_buffer = XMALLOC(SIZE_MAX);
    // 如果分配失败，程序会终止并输出错误信息
    
    XFREE(huge_buffer);
}

void safe_free_example() {
    int* ptr = NULL;
    
    // 释放空指针（会输出警告但不会崩溃）
    XFREE(ptr);  // 输出: [filename:line] Warning: attempt to free NULL pointer
    
    ptr = XMALLOC(sizeof(int));
    *ptr = 42;
    
    // 正常释放
    XFREE(ptr);
    
    // 再次释放（仍然是安全的）
    XFREE(ptr);  // 输出: [filename:line] Warning: attempt to free NULL pointer
}
```

## 调试功能

### 启用调试输出

默认情况下，调试输出被注释掉了。要启用详细的内存跟踪，可以取消注释相关代码：

```c
// 在 xmalloc_debug 函数中取消注释：
fprintf(stderr, "[%s:%d] Allocated %zu bytes at %p\n", file, line, size, ptr);

// 在 xfree_debug 函数中取消注释：
fprintf(stderr, "[%s:%d] Freed memory at %p\n", file, line, ptr);
```

启用后，每次内存分配和释放都会输出详细信息：

```
[main.c:15] Allocated 20 bytes at 0x7f8a5c4026a0
[main.c:20] Freed memory at 0x7f8a5c4026a0
```

## 错误信息格式

### 内存分配失败
```
[filename:line] malloc(size) failed
```

### 释放空指针警告
```
[filename:line] Warning: attempt to free NULL pointer
```

## 设计优势

1. **安全性**: 自动处理分配失败和空指针释放
2. **调试友好**: 提供详细的错误位置信息
3. **防止悬空指针**: 释放后自动设为NULL
4. **一致性**: 使用宏确保统一的错误处理方式

## 注意事项

1. 该模块主要用于开发和调试阶段
2. 在生产环境中，可以考虑禁用调试输出以提高性能
3. 所有内存分配失败都会导致程序终止
4. 使用 `do {...} while(0)` 宏结构确保宏的安全性

## 依赖关系

- 标准库 `stdlib.h` (malloc, free, exit)
- 标准库 `stdio.h` (fprintf, stderr)
