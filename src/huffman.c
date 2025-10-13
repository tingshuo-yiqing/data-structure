#include<string.h>
#include "huffman.h"
#include "memmgr.h"
#include "myfunction.h"

/* 最小堆结构 */

static MinHeap* initMinHeap(int capacity) {
    MinHeap* ret = XMALLOC(sizeof(MinHeap));
    ret->nodes = XMALLOC(sizeof(HuffmanNode*) * capacity);
    ret->capacity = capacity;
    ret->size = 0;
    return ret;
}

static void freeMinHeap(MinHeap* h) {
    XFREE(h->nodes);
    XFREE(h);
}

static inline int parent(int i) { return (i - 1) / 2; }
static inline int leftChild(int i) { return i * 2 + 1; }
static inline int rightChild(int i) { return i * 2 + 2; }

static void heapifyUp(MinHeap* h, int i) {
    while (i > 0 && h->nodes[i]->freq < h->nodes[parent(i)]->freq) {
        SWAP(h->nodes[i], h->nodes[parent(i)]);
        i = parent(i);
    }
}

static void heapifyDown(MinHeap* h, int i) {
    int len = h->size;
    while (leftChild(i) < len) {
        int l = leftChild(i);
        int r = rightChild(i);
        int best = i;

        if (l < len && h->nodes[l]->freq < h->nodes[best]->freq)
            best = l;
        if (r < len && h->nodes[r]->freq < h->nodes[best]->freq)
            best = r;
        
        if (best == i) break;
        SWAP(h->nodes[i], h->nodes[best]);
        i = best;
    }
}

static void insertMinHeap(MinHeap* h, HuffmanNode* node) {
    h->nodes[h->size++] = node;
    heapifyUp(h, h->size - 1);
}

static HuffmanNode* popMinHeap(MinHeap* h) {
    HuffmanNode* ret = h->nodes[0];
    h->nodes[0] = h->nodes[--h->size];
    heapifyDown(h, 0);
    return ret;
}


/* Huffman 结构 */

static HuffmanNode* createHuffmanNode(char ch, int freq, HuffmanNode* left, HuffmanNode* right) {
    HuffmanNode* ret = XMALLOC(sizeof(HuffmanNode));
    ret->ch = ch;
    ret->freq = freq;
    ret->right = right;
    ret->left = left;
    return ret;
}

HuffmanNode* buildHuffmanTree(char data[], int freq[], int dataSize) {
    MinHeap* heap = initMinHeap(dataSize);

    for (int i = 0; i < dataSize; ++i) {
        insertMinHeap(heap, createHuffmanNode(data[i], freq[i], NULL, NULL));
    }

    while (heap->size > 1) {
        HuffmanNode* left = popMinHeap(heap);
        HuffmanNode* right = popMinHeap(heap);

        insertMinHeap(heap, createHuffmanNode('\0', left->freq + right->freq, left, right));
    }

    HuffmanNode* ret = popMinHeap(heap);
    freeMinHeap(heap);
    return ret;
}


void freeHuffmanTree(HuffmanNode* root) {
    if (!root) return ;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    XFREE(root);
}

/**
 * @param root 根节点
 * @param code 临时变量，记录到当前节点时的编码
 * @param depth 记录当前节点的深度
 * @param table 存放叶子节点编码的表格
 * @param idx  表格的大小，执行idx++
 */
static void generateCodes(
    HuffmanNode* root, 
    char* code, 
    int depth, 
    HuffmanCode table[], 
    int* idx
) {
    if (!root) return ;

    if (!root->left && !root->right) {
        code[depth] = '\0';   // 让叶子节点编码以'\0'结尾
        table[*idx].ch = root->ch; 
        strcpy(table[(*idx)++].code, code); 
        return ;
    }
    // 左 '0' 右 '1'
    code[depth] = '0';
    generateCodes(root->left, code, depth + 1, table,idx);
    code[depth] = '1';
    generateCodes(root->right, code, depth + 1, table,idx);
}


int buildHuffmanTable(HuffmanNode* root, HuffmanCode table[]) {
    char code[256];  // 临时变量
    int idx = 0;
    generateCodes(root, code, 0, table, &idx);
    return idx;
}

