#ifndef HUFFMAN_H
#define HUFFMAN_H


typedef struct HuffmanNode {
    char ch;
    int freq;
    struct HuffmanNode* left;
    struct HuffmanNode* right;
} HuffmanNode;

// 类似字典。存 {ch, 01串}
typedef struct {
    char ch;
    char code[256];  // 存放ch的哈夫曼编码
} HuffmanCode;

typedef struct Minheap {
    HuffmanNode** nodes;
    int size;
    int capacity;
} MinHeap;

/**
 * @brief 递归回收哈夫曼节点
 * @param root 哈夫曼根节点
 */
void freeHuffmanTree(HuffmanNode* root);


/**
 * @brief 构建一颗哈夫曼树
 * @param text 待处理的文本
 * @return 哈夫曼树根节点
 */
HuffmanNode* buildHuffmanTree(const char* text);


/**
 * @brief 创建哈夫曼表
 * @param root 哈夫曼树根节点
 * @param table 空表，用于储存{字符: 编码}
 * @return table的大小
 */
int buildHuffmanTable(HuffmanNode* root, HuffmanCode table[]);


/**
 * @brief 输出字符频率
 * @param text 待处理文本
 */
void printCodeFreq(const char* text);


/**
 * @brief 对text进行哈夫曼编码
 * @param text 待编码的字符串 
 * @param table 哈夫曼编码表
 * @param tableSize 哈夫曼编码表大小
 * @return text的哈夫曼编码即01串，需要调用者free
 */
char* huffmanEncode(const char* text, HuffmanCode table[], int tableSize);

/**
 * @brief 对哈夫曼编码(01串)进行解码
 * @param bits 待解码的哈夫曼编码
 * @param root 哈夫曼树根节点
 * @return 得到的解码字符串，需要调用者free
 */
char* huffmanDecode(const char* bits, HuffmanNode* root);


/**
 * @brief 计算压缩率
 * @param original 原串
 * @param encoded 哈夫曼编码串
 * @return 压缩率
 */
double calcCompressionRate(const char* original, const char* encoded);
#endif