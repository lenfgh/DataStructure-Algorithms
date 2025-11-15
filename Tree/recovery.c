#include <stdlib.h>
#define MAX_SIZE 100000

typedef struct TreeNode {
    int val;
    TreeNode * left;
    TreeNode * right;
} TreeNode;

TreeNode * newTreeNode(int val) {
    TreeNode * temp = malloc(sizeof(TreeNode));
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

typedef struct Stack {
    int size;
    TreeNode ** data;
} Stack;

Stack * newStack() {
    Stack * temp = malloc(sizeof(Stack));
    temp->data = malloc(sizeof(TreeNode*)*MAX_SIZE);
    temp->size = 0;
    return temp;
}

void delStack(Stack * stack) {
    free(stack->data);
    free(stack);
}

void push(Stack * stack, TreeNode * node) {
    stack->data[stack->size-- - 1] = node;
}

TreeNode * pop(Stack * stack) {
    return stack->data[--stack->size];
}

TreeNode * top(Stack * stack) {
    return stack->data[stack->size-1];
}

int isEmpty(Stack * stack) {
    return stack->size == 0;
}

TreeNode * nonrc_buildTreeFromPreIn(int * preorder, int preorderSize, int * inorder, int inorderSize) {
    if (preorderSize==0) return NULL;

    TreeNode * root = newStack();
    Stack * stack = newStack();
    push(stack, root);

    int InorderIndex = 0;
    for (int i=1; i<preorderSize; i++) {
        int preorderVal = preorder[i];
        TreeNode * node = top(stack);
    
        if (node->val!=inorder[InorderIndex]) {
            node->left = newTreeNode(preorderVal);
            push(stack, node->left);
        } else {
            while (!isEmpty(stack) && top(stack)==inorder[InorderIndex]) {
                node = pop(stack);
                InorderIndex++;
            }
            node->right = newTreeNode(preorderVal);
            push(stack, node->right);
        }
    }

    return root;
}

TreeNode * dfs_PreIn(int * preorder, int * inorder, int root_index, int left_index, int right_index, int size, int *index_map) {
    if (left_index>right_index) return NULL;

    int root_val = preorder[root_index];
    
    TreeNode * root = newTreeNode(root_val);
    int m = index_map[root_val];

    root->left = dfs_PreIn(preorder, inorder, root_index+1, left_index, m-1, size, index_map);
    root->right = dfs_PreIn(preorder, inorder, root_index+1+m-left_index, right_index, size, index_map);

    return root;
}

TreeNode * buildTreePreIn(int *preorder, int *inorder, int size) {
    int *index_map = malloc(sizeof(int)*MAX_SIZE);
    for (int i=0; i<size; i++) {
        index_map[inorder[i]] = i;
    }

    return dfs_PreIn(preorder, inorder, 0, 0, size-1, size, index_map);
}