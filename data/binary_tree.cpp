template<typename T>
struct _TreeNode {
    T val;
    _TreeNode *left;
    _TreeNode *right;
    
    _TreeNode() : left(nullptr), right(nullptr) {}
    _TreeNode(const T& x) : val(x), left(nullptr), right(nullptr) {}
    _TreeNode(const T& x, _TreeNode *left, _TreeNode *right) : val(x), left(left), right(right) {}
};

template<typename T>
struct BinaryTree {
    using TreeNode = _TreeNode<T>;

    static const bool CHECK_MODE = true; // be careful, check or not
    static const T LEAF;
    int idx = 0; // wired
    TreeNode* root = nullptr;

    BinaryTree() {}

    BinaryTree(const vector<T>& nodes) {
        preorder_build(nodes);
    }

    bool preorder_build(const vector<T>& nodes) {
        if (CHECK_MODE and !check_bt(nodes))
            return false;

        root = preorder_creat(nodes);
        
        assert(idx == (int) nodes.size());
        return true;
    }

    //creat binary tree
    TreeNode* preorder_creat(const vector<T>& nodes) {
        T value = nodes[idx++];

        TreeNode* treenode;
        
        if (LEAF == value) {
            treenode = nullptr;
        } else {
            treenode = new TreeNode(value);
            treenode->left = preorder_creat(nodes);
            treenode->right = preorder_creat(nodes);
        }
        
        return treenode;
    }

    //check if it's binary tree, [preorder mode]
    bool check_bt(const vector<T>& nodes) {
        int deg = 1;

        for (const T& node : nodes) {
            if (deg == 0)
                return false;

            if (node == LEAF) {
                deg -= 1;
            } else {
                deg += 1;
            }
        }

        return deg == 0;
    }

    void preorder_traverse(TreeNode* treenode) {
        if (treenode == nullptr)
            return;

        const T& value = treenode->val;

        preorder_traverse(treenode->left);

        //dosomething(value);

        preorder_traverse(treenode->right);        
    }
};

// template<>
// const int BinaryTree<int>::LEAF = -1;
