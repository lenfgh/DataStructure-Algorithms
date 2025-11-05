#include<stdlib.h>
#include<stdbool.h>

#define MAX_SIZE 1000000

typedef struct TreeNode {
    int val;
    int height;
    TreeNode * left;
    TreeNode * right;
} TreeNode;

TreeNode *newTreeNode(int val) {
    TreeNode *node;

    node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}


int * levelOrder(TreeNode * root, int * size) {
    // assistance
    int front, rear;
    int index, *arr;
    TreeNode *node;
    TreeNode **queue;

    queue = (TreeNode **)malloc(sizeof(TreeNode *) * MAX_SIZE);
    front = 0, rear = 0;
    queue[rear++] = root;
    arr = (int *)malloc(sizeof(int) * MAX_SIZE);
    index = 0;
    while (front<rear) {
        node = queue[front++];
        arr[index++] = node->val;
        if (node->left != NULL) {
            queue[rear++] = node->left;
        }
        if (node->right != NULL) {
            queue[rear++] = node->right;
        }
    }
    *size = index;
    arr = realloc(arr, sizeof(int) * (*size));
    free(queue);
    return arr;
}