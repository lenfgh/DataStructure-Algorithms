#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct HuffmanNode {
    int weight;
    char ch;
    struct HuffmanNode *left, *right;
} HuffmanNode;

typedef struct HuffmanTree {
    HuffmanNode * root;
} HuffmanTree;

HuffmanNode * newHuffmanNode(int weight, char ch) {
    HuffmanNode * node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    node->weight = weight;
    node->ch = ch;
    node->left = NULL;
    node->right = NULL;
}

int compare(const void * a, const void* b) {
    return ((HuffmanNode*)a)->weight-((HuffmanNode*)b)->weight;
}

HuffmanTree * buildHuffmanTree(int weights[], char chars[], int n) {
    HuffmanNode * nodes[n+1];
    for (int i=1; i<=n; i++) {
        nodes[i] = newHuffmanNode(weights[i], chars[i]);
    }

    while (n>1) {
        qsort(nodes+1, n, sizeof(HuffmanNode*), compare);
        HuffmanNode * left = nodes[1];
        HuffmanNode * right = nodes[2];
        HuffmanNode * parent = newHuffmanNode(left->weight+right->weight, '\0');
        parent->left = left;
        parent->right = right;

        nodes[1] = parent;
        for (int i=2;i<n;i++) {
            nodes[i] = nodes[i+1];
        }
        n--;
    }

    HuffmanTree* huffmantree = (HuffmanTree*)(malloc(sizeof(HuffmanTree)));
    huffmantree->root = nodes[1];
    return huffmantree;
}





