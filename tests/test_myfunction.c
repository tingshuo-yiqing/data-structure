#include "myfunction.h"
#include <stdio.h>
#include <assert.h>

void test_MAX() {
    printf("测试MAX宏:\n");
    
    // 测试整数
    int a = 10, b = 20;
    int max_val = MAX(a, b);
    printf("  MAX(%d, %d) = %d\n", a, b, max_val);
    assert(max_val == 20);
    
    // 测试负数
    int c = -5, d = -10;
    max_val = MAX(c, d);
    printf("  MAX(%d, %d) = %d\n", c, d, max_val);
    assert(max_val == -5);
    
    // 测试浮点数
    double x = 3.14, y = 2.71;
    double max_double = MAX(x, y);
    printf("  MAX(%.2f, %.2f) = %.2f\n", x, y, max_double);
    assert(max_double == 3.14);
    
    // 测试相等的情况
    int e = 15, f = 15;
    max_val = MAX(e, f);
    printf("  MAX(%d, %d) = %d\n", e, f, max_val);
    assert(max_val == 15);
    
    printf("MAX宏测试通过！\n\n");
}

void test_MIN() {
    printf("测试MIN宏:\n");
    
    // 测试整数
    int a = 10, b = 20;
    int min_val = MIN(a, b);
    printf("  MIN(%d, %d) = %d\n", a, b, min_val);
    assert(min_val == 10);
    
    // 测试负数
    int c = -5, d = -10;
    min_val = MIN(c, d);
    printf("  MIN(%d, %d) = %d\n", c, d, min_val);
    assert(min_val == -10);
    
    // 测试浮点数
    double x = 3.14, y = 2.71;
    double min_double = MIN(x, y);
    printf("  MIN(%.2f, %.2f) = %.2f\n", x, y, min_double);
    assert(min_double == 2.71);
    
    // 测试相等的情况
    int e = 15, f = 15;
    min_val = MIN(e, f);
    printf("  MIN(%d, %d) = %d\n", e, f, min_val);
    assert(min_val == 15);
    
    printf("MIN宏测试通过！\n\n");
}

void test_ABS() {
    printf("测试ABS宏:\n");
    
    // 测试正数
    int positive = 42;
    int abs_val = ABS(positive);
    printf("  ABS(%d) = %d\n", positive, abs_val);
    assert(abs_val == 42);
    
    // 测试负数
    int negative = -42;
    abs_val = ABS(negative);
    printf("  ABS(%d) = %d\n", negative, abs_val);
    assert(abs_val == 42);
    
    // 测试零
    int zero = 0;
    abs_val = ABS(zero);
    printf("  ABS(%d) = %d\n", zero, abs_val);
    assert(abs_val == 0);
    
    // 测试浮点数
    double neg_double = -3.14;
    double abs_double = ABS(neg_double);
    printf("  ABS(%.2f) = %.2f\n", neg_double, abs_double);
    assert(abs_double == 3.14);
    
    printf("ABS宏测试通过！\n\n");
}

void test_SWAP() {
    printf("测试SWAP宏:\n");
    
    // 测试整数交换
    int x = 10, y = 20;
    printf("  交换前: x = %d, y = %d\n", x, y);
    SWAP(x, y);
    printf("  交换后: x = %d, y = %d\n", x, y);
    assert(x == 20 && y == 10);
    
    // 测试浮点数交换
    double a = 1.23, b = 4.56;
    printf("  交换前: a = %.2f, b = %.2f\n", a, b);
    SWAP(a, b);
    printf("  交换后: a = %.2f, b = %.2f\n", a, b);
    assert(a == 4.56 && b == 1.23);
    
    // 测试字符交换
    char c1 = 'A', c2 = 'Z';
    printf("  交换前: c1 = %c, c2 = %c\n", c1, c2);
    SWAP(c1, c2);
    printf("  交换后: c1 = %c, c2 = %c\n", c1, c2);
    assert(c1 == 'Z' && c2 == 'A');
    
    // 测试指针交换
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int *ptr1 = arr1, *ptr2 = arr2;
    printf("  交换前: *ptr1 = %d, *ptr2 = %d\n", *ptr1, *ptr2);
    SWAP(ptr1, ptr2);
    printf("  交换后: *ptr1 = %d, *ptr2 = %d\n", *ptr1, *ptr2);
    assert(*ptr1 == 4 && *ptr2 == 1);
    
    printf("SWAP宏测试通过！\n\n");
}

void test_GCD() {
    printf("测试GCD宏:\n");
    
    // 测试正常情况
    int a = 48, b = 18;
    int gcd_val = GCD(a, b);
    printf("  GCD(%d, %d) = %d\n", a, b, gcd_val);
    assert(gcd_val == 6);
    
    // 测试质数
    int c = 17, d = 13;
    gcd_val = GCD(c, d);
    printf("  GCD(%d, %d) = %d\n", c, d, gcd_val);
    assert(gcd_val == 1);
    
    // 测试包含0的情况
    int e = 0, f = 15;
    gcd_val = GCD(e, f);
    printf("  GCD(%d, %d) = %d\n", e, f, gcd_val);
    assert(gcd_val == 15);
    
    // 测试两个0的情况
    int g = 0, h = 0;
    gcd_val = GCD(g, h);
    printf("  GCD(%d, %d) = %d\n", g, h, gcd_val);
    assert(gcd_val == 0);
    
    // 测试负数（GCD通常定义为正数）
    int i = -24, j = 36;
    gcd_val = GCD(i, j);
    printf("  GCD(%d, %d) = %d\n", i, j, gcd_val);
    assert(gcd_val == 12);
    
    printf("GCD宏测试通过！\n\n");
}


void test_macro_edge_cases() {
    printf("测试宏边界情况:\n");
    
    // 测试表达式作为参数
    int result = MAX(5 + 3, 2 * 4);
    printf("  MAX(5 + 3, 2 * 4) = %d\n", result);
    assert(result == 8);
    
    result = MIN(10 - 2, 3 + 4);
    printf("  MIN(10 - 2, 3 + 4) = %d\n", result);
    assert(result == 7);
    
    // 测试函数调用作为参数
    int abs_result = ABS(-(5 * 2));
    printf("  ABS(-(5 * 2)) = %d\n", abs_result);
    assert(abs_result == 10);
    
    printf("边界情况测试通过！\n\n");
}

int main() {
    printf("开始测试myfunction.h中的所有宏...\n\n");
    
    test_MAX();
    test_MIN();
    test_ABS();
    test_SWAP();
    test_GCD();
    test_macro_edge_cases();
    
    printf("所有测试通过！myfunction.h中的宏实现正确。\n");
    return 0;
}
