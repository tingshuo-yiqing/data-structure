# 常见应用

## 后缀表达式求值

### 步骤
1. 遍历到数字就进栈
2. 遍历到符号时弹出2个数字，先出栈的放在符号后面
3. 最后栈中的那个数字就是结果

### 注意事项
1. 栈存的是`int`型、符号数组是二维的`char* token[]`因为数字可能是两位数的
2. 重要函数可以简化一些操作时间
   * `atoi`将字符数字转化为整型数字（可以转负数）、
   * `strcmp`C语言比较字符串是否相同的函数
3. 只有碰到了符号才能弹出2个数字，不要每次操作都弹！

```c
int evalPostfix(char** token, int len) {
    stack* st = initStack();
    for (int i = 0; i < len; ++i) {
        char* ch = token[i];

        if (strcmp(ch, "+") == 0 ···) {
            int b = popStack(st);
            int a = popStack(st);

            if (strcmp(ch, "+") == 0) {
                pushStack(st, a + b);
            }
            ···
        } else {
            pushStack(st, atoi(ch));
        }
    }
    int ret = topStack(st);
    freeStack(st);
    return ret;
}
```

## 中缀转后缀



