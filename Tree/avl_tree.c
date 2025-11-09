

typedef struct TreeNode {
    int val;
    int height;
    struct TreeNode * left;
    struct TreeNode * right;
} TreeNode;

typedef struct AVLTree {
    TreeNode * root;
} AVLTree;

TreeNode * newTreeNode (int val) {
    TreeNode * node;
    node = (TreeNode *) malloc(sizeof(TreeNode));
    node->val = val;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int height(TreeNode * node) {
    if (node!=NULL) {
        return node->height;
    }
    return -1;
}

void updateHeight(TreeNode * node) {
    int lh = height(node->left);
    int rh = height(node->right);
    node->height = 1 + (lh>rh ? lh : rh);
}

int balanceFactor(TreeNode * node) {
    if (node==NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

TreeNode * rightRotate(TreeNode * node) {
    TreeNode * child, *grandChild;
    child = node->left;
    grandChild = child->right;
    child->right = node;
    node->left = grandChild;
    updateHeight(node);
    updateHeight(child);
    return child;
}

TreeNode * leftRotate(TreeNode * node) {
    TreeNode * child, * grandChild;
    child = node->right;
    grandChild = child->left;
    child->left = node;
    node->right = grandChild;
    updateHeight(node);
    updateHeight(child);
    return child;
}

TreeNode * rotate(TreeNode * node) {
    int bf = balanceFactor(node);;
    if (bf>1) {
        if (balanceFactor(node->left)>=0) {
            return rightRotate(node);
        } else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (bf<-1) {
        if (balanceFactor(node->right)<=0) {
            return leftRoate(node);
        } else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

void insert(AVLTree * tree, int val) {
    tree->root = insertHelper(tree->root, val);
}

TreeNode *insertHelper(TreeNode * node, int val) {
    if (node==NULL) {
        return newTreeNode(val);
    }
    if (val<node->val) {
        node->left = insertHelper(node->left, val);
    } else if ( val > node->val) {
        node->right = insertHelper(node->right, val);
    } else {
        return node;
    }
    updateHeight(node);
    node = rotate(node);
    return node;
}





