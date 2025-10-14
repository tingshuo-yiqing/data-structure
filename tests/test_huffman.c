#include<stdio.h>
#include "memmgr.h"
#include "tree.h"
#include "huffman.h"


int main() {

    // 输入文本
    char *text = "assdsadfasdaa";
    // 创建哈夫曼树
    HuffmanNode* root = buildHuffmanTree(text);

    // 建哈夫曼编码表
    HuffmanCode table[256];
    int count = buildHuffmanTable(root, table);

    printf("Huffman Codes:\n");
    for (int i = 0; i < count; i++)
        printf("%c : %s\n", table[i].ch, table[i].code);

    printf("字符频率:\n");
    printCodeFreq(text);

    // 对文本进行编码
    char* s = huffmanEncode(text, table, count);
    printf("%s\n", s);

    // 对文本进行解码
    char* c = huffmanDecode(s, root);
    printf("%s\n", c);

    // 求压缩率
    printf("%lf\n", calcCompressionRate(text, s));
    freeHuffmanTree(root);
    XFREE(s);
    XFREE(c);
    return 0;
}