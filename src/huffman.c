#include<string.h>
#include<stdio.h>
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


static int countFreq(const char* text, char data[], int freq[]) {
    int count[256] = {0};
    int retSize = 0;

    //? for循环条件
    for (const char* p = text; *p; p++) {
        count[(unsigned char)*p]++;   // 避免负数下标（例如中文或扩展 ASCII）
    }

    for (int i = 0; i < 256; ++i) {
        if (count[i] > 0) {
            data[retSize] = (char)i;
            freq[retSize] = count[i];
            retSize++;
        }
    }
    return retSize;
}


void printCodeFreq(const char* text) {
    if (!text || !*text) return ;
    char data[256];
    int freq[256];
    int size = countFreq(text, data, freq);
    if (size == 0) return ;

    for (int i = 0; i < size; ++i) {
        printf("%c : %d\n", data[i], freq[i]);
    }
}


HuffmanNode* buildHuffmanTree(const char* text) {

    // 第一个检查是否为NULL，即buildHuffmanTree()， 第二个检查是否为'\0'即buildHuffmanTree("")
    if (!text || !*text) return NULL;
    char data[256];
    int freq[256];
    int size = countFreq(text, data, freq);
    if (size == 0) return NULL;
    
    MinHeap* heap = initMinHeap(size);
    for (int i = 0; i < size; ++i) {
        insertMinHeap(heap, createHuffmanNode(data[i], freq[i], NULL, NULL));
    }

    while (heap->size > 1) {
        HuffmanNode* left = popMinHeap(heap);
        HuffmanNode* right = popMinHeap(heap);

        insertMinHeap(heap, createHuffmanNode('\0',
                        left->freq + right->freq, left, right));
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


char* huffmanEncode(const char* text, HuffmanCode table[], int tableSize) {
    if (!text || !*text || !table || tableSize <= 0) return NULL;

    // 因为ASCII吗作用256位，所以可以使用一个查找表实现O(1)查询
    char* encodeMap[256] = {NULL};  // 存每个字符对应的哈夫曼编码字符串
    for (int i = 0; i < tableSize; ++i) {
        encodeMap[(unsigned char)table[i].ch] = table[i].code;
    }

    char *encoded = XMALLOC(strlen(text) * 32 + 1);
    encoded[0] = '\0';  // 出海话字符串

    for (const unsigned char* p = (const unsigned char*)text; *p; ++p) {
        char* code = encodeMap[*p];
        if (code)
            strcat(encoded, code);
        else
            fprintf(stderr, "[Warning] Unrecognized char: %c\n", *p);
    }
    return encoded;
}


char* huffmanDecode(const char* bits, HuffmanNode* root) {
    if (!bits || !*bits || !root) return NULL;

    char* decoded = XMALLOC(strlen(bits) + 1);
    int idx = 0;

    HuffmanNode* cur = root;
    for (const char* p = bits; *p; ++p) {
        cur = (*p == '0') ? cur->left : cur->right;

        if (!cur->left && !cur->right) {
            decoded[idx++] = cur->ch;  // 到达叶子节点
            cur = root; // 会到根节点继续解码
        }
    }

    decoded[idx] = '\0';
    return decoded;
}


double calcCompressionRate(const char* original, const char* encoded) {
    if (!original || !*original || !encoded || !*encoded) return 0.0;

    // 原始一个和字符通常是 8 bits
    double originalBits = strlen(original) * 8.0;
    double encodedlBits = strlen(encoded) * 1.0;

    return encodedlBits / originalBits;
}