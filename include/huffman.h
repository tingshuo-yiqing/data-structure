#ifndef HUFFMAN_H
#define HUFFMAN_H


#include<stddef.h>

typedef struct HuffmanNode {
    char ch;
    int freq;
    struct HuffmanNode* left;
    struct HuffmanNode* right;
} HuffmanNode;

typedef struct {
    char ch;
    char code[256];  // 存放ch的哈夫曼编码
} HuffmanCode;

typedef struct Minheap {
    HuffmanNode** nodes;
    int size;
    int capacity;
} MinHeap;


HuffmanNode* buildHuffmanTree(char data[], int freq[], int dataSize);

void freeHuffmanTree(HuffmanNode* root);

int buildHuffmanTable(HuffmanNode* root, HuffmanCode table[]);
#endif