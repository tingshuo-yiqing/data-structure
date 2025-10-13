#include<stdio.h>
#include "tree.h"
#include "huffman.h"


int main() {
    char data[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int freq[]  = {5, 9, 12, 13, 16, 45};
    int n = sizeof(data) / sizeof(data[0]);

    HuffmanNode* root = buildHuffmanTree(data, freq, n);

    HuffmanCode table[256];
    int count = buildHuffmanTable(root, table);

    printf("Huffman Codes:\n");
    for (int i = 0; i < count; i++)
        printf("%c : %s\n", table[i].ch, table[i].code);

    freeHuffmanTree(root);
    return 0;
}