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



