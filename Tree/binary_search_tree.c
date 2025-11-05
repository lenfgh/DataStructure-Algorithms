#include<stdlib.h>

# define MAX_SIZE 100000


typedef struct TreeNode {
    int val;
    int height;
    TreeNode * left;
    TreeNode * right;
} TreeNode;

TreeNode  * newTreeNode(int num) {
    TreeNode * n = (TreeNode *) malloc(sizeof(TreeNode));
    n->val = num;
    n->left = NULL;
    n->right = NULL;
    return n;
}

typedef struct {
    TreeNode * root;
} BinarySearchTree;


TreeNode * search(BinarySearchTree *bst, int num) {
    TreeNode * cur = bst->root;
    while (cur!=NULL) {
        if (cur->val < num) {
            cur = cur->right;
        } else if (cur->val > num) {
            cur = cur->left;
        } else {
            break;
        }
    }
    return cur;
}

void insert(BinarySearchTree * bst, int num) {
    if (bst->root == NULL) {
        bst->root = newTreeNode(num);
        return;
    }
    TreeNode * cur = bst->root, * pre = NULL;
    while (cur!=NULL) {
        if (cur->val == num) {
            return;
        } 
        pre = cur;
        if (cur->val>num) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    TreeNode * n = newTreeNode(num);
    if (pre->val>num) {
        pre->left = n;
    } else {
        pre->right = n;
    }
}

void removeItem(BinarySearchTree * bst, int num) {
    if (bst->root==NULL) {
        return;
    }
    TreeNode * cur = bst->root, * pre = NULL;

    while (cur!=NULL) {
        if (cur->val == num) {
            return;
        } 
        pre = cur;
        if (cur->val>num) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    if (cur==NULL) {
        return;
    }
    if (cur->left == NULL || cur->right==NULL) {
        TreeNode *child = cur->left != NULL ? cur->left : cur->right;
        if (pre->left == cur) {
            pre->left = child;
        } else {
            pre->right = child;
        }
        free(cur);
    } else {
        TreeNode * tmp = cur->right;
        while (tmp->left!=NULL) {
            tmp = tmp->left;
        }
        int tmpVal = tmp->val;
        removeItem(bst, tmpVal);
        cur->val = tmpVal;
    }
}




