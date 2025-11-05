#include<stdlib.h>
#include<stddef.h>

# define MAX_SIZE 100000

typedef struct {
    int *tree;
    int size;
} ArrayBinaryTree;

ArrayBinaryTree *newArrayBInaryTree(int *arr, int arrSize) {
    ArrayBinaryTree *abt = (ArrayBinaryTree *)malloc(sizeof(ArrayBinaryTree));
    abt->tree = malloc(sizeof(int) * arrSize);
    memcpy(abt->tree, arr, sizeof(int) * arrSize);
    abt->size = arrSize;
    return abt;
}

void delArrayBinaryTree(ArrayBinaryTree * abt) {
    free(abt->tree);
    free(abt);
}

int size(ArrayBinaryTree *abt) {
    return abt->size;
}

int val(ArrayBinaryTree *abt, int i) {
    if (i<0 || i>=size(abt)) {
        return MAX_SIZE;
    }
    return abt->tree[i];
}


int *levelOrder(ArrayBinaryTree * abt, int * returnSize) {
    int * res = (int *)malloc(sizeof(int) * size(abt));
    int index = 0;
    for (int i=0; i<size(abt); i++) {
        if (val(abt, i) != MAX_SIZE) {
            res[index++] = val(abt, i);
        }
    }
    *returnSize = index;
    return res;
}

void dfs(ArrayBinaryTree * abt, int i, char *order, int *res, int *index) {
    if (val(abt, i) == MAX_SIZE) {
        return;
    }
    // preOrder
    if (strcmp(order, "pre") == 0)
        res[(*index)++] = val(abt, i);
    dfs(abt, left(i), order, res, index);
    // inOrder
    if (strcmp(order, "in") == 0)
        res[(*index)++] = val(abt, i);
    dfs(abt, right(i), order, res, index);
    // postOrder
    if (strcmp(order, "post") == 0)
        res[(*index)++] = val(abt, i);
}

int exists(ArrayBinaryTree * abt, int i) {
    return i>=0 && abt->size && abt->tree[i]!=MAX_SIZE;
}

int preOrder(ArrayBinaryTree *abt, int index) {
    if (abt==NULL||abt->size==0||abt->tree[0]==MAX_SIZE) return;
    if (!exists(abt, index)) return;

    print("%d", abt->tree[index]);

    int left = 2*index + 1;
    int right = 2*index + 2;
    preOrder(abt, left);
    preOrder(abt, right);

}

int inOrder(ArrayBinaryTree * abt, int index) {
    if (abt==NULL||abt->size==0||abt->tree[0]==MAX_SIZE) return;
    if (!exists(abt, index)) return;

    int left = 2*index + 1;
    int right = 2*index + 2;
    
    inOrder(abt, left);
    printf("%d", abt->tree[index]);
    inOrder(abt, right);
}

int postOrder(ArrayBinaryTree * abt, int index) {
    if (abt==NULL||abt->size==0||abt->tree[0]==MAX_SIZE) return;
    if (!exists(abt, index)) return;

    int left = 2*index + 1;
    int right = 2*index + 2;
    
    postOrder(abt, left);
    postOrder(abt, right);
    printf("%d", abt->tree[index]);
}



int heightHelper(ArrayBinaryTree * abt, int index) {
    if (!exists(abt, index)) return 0;
    int left = 2*index+1;
    int right = 2*index + 2;

    int leftHeight = heightHelper(abt, left);
    int rightHeight = heightHelper(abt, right);

    return 1+(leftHeight > rightHeight ? leftHeight : rightHeight);
}

int treeHeight(ArrayBinaryTree * abt) {
    return heightHelper(abt, 0);
}

int nodeHelper(ArrayBinaryTree * abt, int index) {
    if (!exists(abt, index)) return 0;
    int left = 2*index +1;
    int right = 2*index+2;
    return 1 + nodeHelper(abt, left) + nodeHelper(abt, right);
}

int countNodes(ArrayBinaryTree * abt) {
    return nodeHelper(abt, 0);
}