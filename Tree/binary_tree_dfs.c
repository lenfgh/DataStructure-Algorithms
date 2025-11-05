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

void preOrder(TreeNode * root, int * size, int * arr) {
    if (root==NULL) {
        return ;
    }
    arr[(*size)++] = root->val;
    preOrder(root->left, size, arr);
    preOrder(root->right, size, arr);
}

void inOrder(TreeNode * root, int * size, int * arr) {
    if (root==NULL) {
        return;
    }
    inOrder(root->left, size, arr);
    arr[(*size)++] = root->val;
    inOrder(root->right, size, arr);
}

void postOrder(TreeNode * root, int * size, int * arr) {
    if (root==NULL) {
        return;
    }
    postOrder(root->left, size, arr);
    postOrder(root->right, size, arr);
    arr[(*size)++] = root->val;
}

// 

typedef struct Stack {
    TreeNode **data;
    int top;
    int capacity;
} Stack;

Stack * createStack (int capacity) {
    Stack * stack = (Stack *)malloc(sizeof(Stack));
    stack->data = (TreeNode**)malloc(sizeof(TreeNode*)*capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, TreeNode *node) {
    if (stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = node;
    }
}

TreeNode* pop(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top--];
    }
    return NULL;
}

TreeNode* peek(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top];
    }
    return NULL;
}

void preOrderIterative(TreeNode * root, int * arr) {
    if (root==NULL) return;

    Stack * stack = createStack(MAX_SIZE);
    push(stack, root);
    int index = 0;

    while(!isEmpty(stack)) {
        TreeNode * current = pop(stack);
        arr[index++] = current->val;
        if (current->right!=NULL) {
            push(stack, current->right);
        }
        if (current->left!=NULL) {
            push(stack, current->left);
        }
    }
    free(stack->data);
    free(stack);   
}

void inOrderIterative(TreeNode * root, int * arr) {
    if (root==NULL) return;
    Stack * stack = createStack(MAX_SIZE);
    int index = 0;
    // push(stack, root);
    TreeNode * current = root;

    while(!isEmpty(stack) || current!=NULL) {

        while(current!=NULL) {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        arr[index++] = current->val;
        current = current->right;
    }

    free(stack->data);
    free(stack);
}

void postOrderIterative(TreeNode * root, int * arr ) {
    if (root==NULL) return;

    Stack * stack = createStack(MAX_SIZE);
    TreeNode * current = root;
    TreeNode * prev = NULL;
    int index = 0;
    // push(stack, root);

    while(!isEmpty(stack) || current!=NULL) {
        while (current!=NULL) {
            push(stack, current);
            current = current->left;
        }

        current = pop(stack);
        
        if (current->right==NULL || current->right == prev) {
            // push(stack, current);
            arr[index++] = current->val;
            prev = current;
            current = NULL;
        } else {
            push(stack, current);
            current = current->right;
        }
    }
    free(stack->data);
    free(stack);
}