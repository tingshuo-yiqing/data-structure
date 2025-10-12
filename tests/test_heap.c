#include<stdio.h>
#include "heap.h"
#include "memmgr.h"

// deepseek生成的测试代码
// 测试函数声明
void testMinHeap(void);
void testMaxHeap(void);
void testEdgeCases(void);
void testResize(void);
void printTestResult(const char* testName, bool passed);

int main(void) {
    printf("=== Heap Implementation Tests ===\n\n");
    
    testMinHeap();
    testMaxHeap();
    testEdgeCases();
    testResize();
    
    printf("\n=== All Tests Completed ===\n");
    return 0;
}

void testMinHeap(void) {
    printf("Testing Min Heap:\n");
    
    Heap* h = initMinHeap();
    bool allPassed = true;
    
    // Test 1: Basic insertion and popping
    insertHeap(h, 5);
    insertHeap(h, 3);
    insertHeap(h, 8);
    insertHeap(h, 1);
    insertHeap(h, 4);
    
    bool test1 = (popHeap(h) == 1);
    printTestResult("Min Heap - Pop min value 1", test1);
    allPassed &= test1;
    
    bool test2 = (popHeap(h) == 3);
    printTestResult("Min Heap - Pop min value 3", test2);
    allPassed &= test2;
    
    bool test3 = (popHeap(h) == 4);
    printTestResult("Min Heap - Pop min value 4", test3);
    allPassed &= test3;
    
    bool test4 = (popHeap(h) == 5);
    printTestResult("Min Heap - Pop min value 5", test4);
    allPassed &= test4;
    
    bool test5 = (popHeap(h) == 8);
    printTestResult("Min Heap - Pop min value 8", test5);
    allPassed &= test5;
    
    printTestResult("Min Heap Basic Test", allPassed);
    freeHeap(h);
    printf("\n");
}

void testMaxHeap(void) {
    printf("Testing Max Heap:\n");
    
    Heap* h = initMaxHeap();
    bool allPassed = true;
    
    // Test basic insertion and popping
    insertHeap(h, 5);
    insertHeap(h, 3);
    insertHeap(h, 8);
    insertHeap(h, 1);
    insertHeap(h, 4);
    
    bool test1 = (popHeap(h) == 8);
    printTestResult("Max Heap - Pop max value 8", test1);
    allPassed &= test1;
    
    bool test2 = (popHeap(h) == 5);
    printTestResult("Max Heap - Pop max value 5", test2);
    allPassed &= test2;
    
    bool test3 = (popHeap(h) == 4);
    printTestResult("Max Heap - Pop max value 4", test3);
    allPassed &= test3;
    
    bool test4 = (popHeap(h) == 3);
    printTestResult("Max Heap - Pop max value 3", test4);
    allPassed &= test4;
    
    bool test5 = (popHeap(h) == 1);
    printTestResult("Max Heap - Pop max value 1", test5);
    allPassed &= test5;
    
    printTestResult("Max Heap Basic Test", allPassed);
    freeHeap(h);
    printf("\n");
}

void testEdgeCases(void) {
    printf("Testing Edge Cases:\n");
    
    Heap* h = initMinHeap();
    bool allPassed = true;
    
    // Test empty heap
    bool test1 = isHeapEmpty(h);
    printTestResult("Empty Heap Detection", test1);
    allPassed &= test1;
    
    bool test2 = (getHeapSize(h) == 0);
    printTestResult("Empty Heap Size", test2);
    allPassed &= test2;
    
    // Test single element
    insertHeap(h, 42);
    bool test3 = (!isHeapEmpty(h));
    printTestResult("Non-empty Heap Detection", test3);
    allPassed &= test3;
    
    bool test4 = (getHeapSize(h) == 1);
    printTestResult("Single Element Heap Size", test4);
    allPassed &= test4;
    
    bool test5 = (topHeap(h) == 42);
    printTestResult("Top Element", test5);
    allPassed &= test5;
    
    bool test6 = (popHeap(h) == 42);
    printTestResult("Pop Single Element", test6);
    allPassed &= test6;
    
    bool test7 = isHeapEmpty(h);
    printTestResult("Empty After Pop", test7);
    allPassed &= test7;
    
    printTestResult("Edge Cases Test", allPassed);
    freeHeap(h);
    printf("\n");
}

void testResize(void) {
    printf("Testing Resize Function:\n");
    
    Heap* h = initMinHeap();
    bool allPassed = true;
    
    // Insert many elements to trigger resize
    size_t initialCapacity = h->capacity;
    
    for (int i = 100; i >= 0; i--) {
        insertHeap(h, i);
    }
    
    bool test1 = (h->capacity > initialCapacity);
    printTestResult("Capacity Resized", test1);
    allPassed &= test1;
    
    bool test2 = (getHeapSize(h) == 101);
    printTestResult("Correct Size After Resize", test2);
    allPassed &= test2;
    
    // Verify all elements can be popped in order
    bool orderCorrect = true;
    for (int i = 0; i <= 100; i++) {
        if (popHeap(h) != i) {
            orderCorrect = false;
            break;
        }
    }
    
    bool test3 = orderCorrect;
    printTestResult("Correct Order After Resize", test3);
    allPassed &= test3;
    
    bool test4 = isHeapEmpty(h);
    printTestResult("Heap Empty After Resize Test", test4);
    allPassed &= test4;
    
    printTestResult("Resize Function Test", allPassed);
    freeHeap(h);
    printf("\n");
}

void printTestResult(const char* testName, bool passed) {
    printf("  %s: %s\n", testName, passed ? "✓ PASS" : "✗ FAIL");
}

// Additional visualization test (optional)
void demoHeap(void) {
    printf("=== Heap Demo ===\n");
    
    // Demo min heap
    printf("\nMin Heap Demo:\n");
    Heap* minHeap = initMinHeap();
    int testData[] = {7, 2, 9, 1, 5, 3, 8};
    int dataSize = sizeof(testData) / sizeof(testData[0]);
    
    printf("Insertion order: ");
    for (int i = 0; i < dataSize; i++) {
        printf("%d ", testData[i]);
        insertHeap(minHeap, testData[i]);
    }
    printf("\n");
    
    printf("Popping order: ");
    while (!isHeapEmpty(minHeap)) {
        printf("%d ", popHeap(minHeap));
    }
    printf("\n");
    freeHeap(minHeap);
    
    // Demo max heap
    printf("\nMax Heap Demo:\n");
    Heap* maxHeap = initMaxHeap();
    
    printf("Insertion order: ");
    for (int i = 0; i < dataSize; i++) {
        printf("%d ", testData[i]);
        insertHeap(maxHeap, testData[i]);
    }
    printf("\n");
    
    printf("Popping order: ");
    while (!isHeapEmpty(maxHeap)) {
        printf("%d ", popHeap(maxHeap));
    }
    printf("\n");
    freeHeap(maxHeap);
}
