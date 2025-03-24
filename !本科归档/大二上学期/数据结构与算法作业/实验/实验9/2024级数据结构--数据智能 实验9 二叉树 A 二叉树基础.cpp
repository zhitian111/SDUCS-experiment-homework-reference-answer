/*2024级数据结构--数据智能 实验9 二叉树 A 二叉树基础.cpp*/
#include <iostream>

using namespace std;

size_t pow(size_t base, size_t exp)
{
    size_t result = 1;
    while (exp > 0)
    {
        if (exp & 1)
        {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return result;
}

template<class T>
inline T& max(T& a, T& b)
{
    return a > b? a : b;
}
template<class T>
inline T& min(T& a, T& b)
{
    return a < b? a : b;
}


template<class T>
struct Node
{
    T data;
    Node<T>* left, * right, * parent;
    size_t depth;
    size_t sons;
    bool touched;
    Node(Node<T>* parent, const T& data) : data(data), left(nullptr), right(nullptr), parent(parent), depth(0), sons(0), touched(false) {}
};

template<class T>
class binaryTree
{
public:
    enum inputType { preOrder, inOrder, postOrder };
private:
    Node<T>* root;
    size_t count;
    size_t depth;
    Node<T>** index;
public:
    Node<T>* Root() { return root; };
    binaryTree();
    binaryTree(size_t size, inputType type = inputType::preOrder);
    ~binaryTree();
    size_t size() const;
    size_t height() const;
    size_t subTreeSize(const size_t subscript) const;
    size_t subTreeHeight(const size_t subscript) const;
    size_t subTreeSize(Node<T>* node) const;
    size_t subTreeHeight(Node<T>* node) const;
    void preOrderOutput(Node<T>* node);
    void inOrderOutput();
    void postOrderOutput();
    void levelOrderOutput();
    void subTreeSizeOutput();
    void subTreeHeightOutput();
    void iniDepth(Node<T>* node);
    void iniSons(Node<T>* node);
};
template<class T>
binaryTree<T>::binaryTree()
{
    root = nullptr;
    count = 0;
    depth = 0;
    index = nullptr;
}


template<class T>
binaryTree<T>::binaryTree(size_t size, binaryTree<T>::inputType type)
{
    if (size == 0)
    {
        return;
    }
    Node<T>* node = new Node<T>(nullptr, 1);
    root = node;
    count = 1;
    depth = 1;
    index = new Node<T>*[size];
    node->depth = 1;
    index[0] = node;
    if (size == 1)
    {
        return;
    }
    if (type == binaryTree<T>::inputType::preOrder)
    {
        return;
    }
    else if (type == binaryTree<T>::inputType::inOrder)
    {
        size_t nullptr_count = 0;
        for (size_t i = 0; i < size; i++)
        {
            Node<T>* operatedNode = index[i];
            T left, right;
            cin >> left >> right;
            if (left != -1)
            {
                Node<T>* leftNode = new Node<T>(operatedNode, left);
                operatedNode->left = leftNode;
                leftNode->depth = operatedNode->depth + 1;
                index[i * 2 + 1 - nullptr_count] = leftNode;
                count++;
            }
            else
            {
                operatedNode->left = nullptr;
                nullptr_count++;
            }
            if (right != -1)
            {
                Node<T>* rightNode = new Node<T>(operatedNode, right);
                operatedNode->right = rightNode;
                rightNode->depth = operatedNode->depth + 1;
                index[i * 2 + 2 - nullptr_count] = rightNode;
                count++;
            }
            else
            {
                operatedNode->right = nullptr;
                nullptr_count++;
            }
            if (i == size - 1)
            {
                this->depth = operatedNode->depth;
            }
        }
        return;
    }
    else if (type == binaryTree<T>::inputType::postOrder)
    {
        return;
    }
}

template<class T>
binaryTree<T>::~binaryTree()
{
    for (size_t i = 0; i < count; i++)
    {
        delete index[i];
    }
    delete[] index;
}

template<class T>
size_t binaryTree<T>::size() const
{
    return count;
}

template<class T>
size_t binaryTree<T>::height() const
{
    return depth;
}


template<class T>
size_t binaryTree<T>::subTreeSize(size_t subscript) const
{
    return index[subscript]->sons;
}

template<class T>
size_t binaryTree<T>::subTreeSize(Node<T>* node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->sons;
}

template<class T>
size_t binaryTree<T>::subTreeHeight(size_t subscript) const
{
    return index[subscript]->depth;
}

template<class T>
size_t binaryTree<T>::subTreeHeight(Node<T>* node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->depth;
}

template<class T>
void binaryTree<T>::preOrderOutput(Node<T>* node)
{
    if (node == nullptr)
    {
        return;
    }
    cout << node->data << " ";
    preOrderOutput(node->left);
    preOrderOutput(node->right);
    return;
}

template<class T>
void binaryTree<T>::inOrderOutput()
{
    Node<T>* node = root;
    for (size_t i = 0; i < this->size(); i++)
    {
        index[i]->touched = false;
    }
    while (1)
    {
        if (node->left != nullptr && node->left->touched == false)
        {
            node = node->left;
        }
        else
        {
            if (node->touched == false)
            {
                cout << node->data << " ";
                node->touched = true;
                if (node->right != nullptr)
                {
                    node = node->right;
                }
                else
                {
                    node = node->parent;
                }
            }
            else
            {
                if (node->parent != nullptr)
                {
                    node = node->parent;
                }
                else if (node->right != nullptr && node->right->touched == true)
                {
                    break;
                }
            }

        }
        if (node->parent == nullptr && node->right != nullptr && node->right->touched == true)
        {
            break;
        }
    }

    cout << endl;
    return;
}

template<class T>
void binaryTree<T>::postOrderOutput()
{
    Node<T>* node = root;
    for (size_t i = 0; i < this->size(); i++)
    {
        index[i]->touched = false;
    }
    while (1)
    {
        if (node == nullptr)
        {
            break;
        }
        if (node->left != nullptr && node->left->touched == false)
        {
            node = node->left;
        }
        else
        {
            if (node->right != nullptr && node->right->touched == false)
            {
                node = node->right;
            }
            else
            {
                if (node->touched == false)
                {
                    cout << node->data << " ";
                    node->touched = true;
                    node = node->parent;
                }
                else
                {
                    if (node->parent != nullptr)
                    {
                        node = node->parent;
                    }
                    else if (node->right != nullptr && node->right->touched == true && node->touched == true)
                    {
                        break;
                    }
                }
            }
        }
        if (node == nullptr)
        {
            break;
        }
        if (node->parent == nullptr && node->right != nullptr && node->right->touched == true && node->touched == true)
        {
            break;
        }
    }
    cout << endl;
    return;
}

template<class T>
void binaryTree<T>::levelOrderOutput()
{
    for (size_t i = 0; i < this->size(); i++)
    {
        cout << index[i]->data << " ";
    }
    cout << endl;
}

template<class T>
void binaryTree<T>::subTreeSizeOutput()
{
    for (size_t i = 0; i < this->size(); i++)
    {
        cout << subTreeSize(i) << " ";
    }
    cout << endl;
}

template<class T>
void binaryTree<T>::subTreeHeightOutput()
{
    for (size_t i = 0; i < this->size(); i++)
    {
        cout << subTreeHeight(i) << " ";
    }
    cout << endl;
}

template<class T>
void binaryTree<T>::iniDepth(Node<T>* node)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->left == nullptr && node->right == nullptr)
    {
        node->depth = 1;
        return;
    }
    iniDepth(node->left);
    iniDepth(node->right);
    if (node->left != nullptr && node->right != nullptr)
    {
        node->depth = max(node->left->depth, node->right->depth) + 1;        
    }
    else if (node->left != nullptr && node->right == nullptr)
    {
        node->depth = node->left->depth + 1;
    }
    else if (node->left == nullptr && node->right != nullptr)
    {
        node->depth = node->right->depth + 1;
    }
    return;
}

template<class T>
void binaryTree<T>::iniSons(Node<T>* node)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->left == nullptr && node->right == nullptr)
    {
        node->sons = 1;
        return;
    }
    iniSons(node->left);
    iniSons(node->right);
    if (node->left != nullptr && node->right != nullptr)
    {
        node->sons = node->left->sons + node->right->sons + 1;
    }
    else if (node->left != nullptr && node->right == nullptr)
    {
        node->sons = node->left->sons + 1;
    }
    else if (node->left == nullptr && node->right != nullptr)
    {
        node->sons = node->right->sons + 1;
    }
    return;
}
class Solution
{
public:
    void solve();
};


void Solution::solve()
{
    size_t size;
    cin >> size;
    binaryTree<int> tree(size, binaryTree<int>::inputType::inOrder);
    tree.preOrderOutput(tree.Root());
    cout << endl;
    tree.inOrderOutput();
    tree.postOrderOutput();
    tree.levelOrderOutput();
    tree.iniDepth(tree.Root());
    tree.iniSons(tree.Root());
    tree.subTreeSizeOutput();
    tree.subTreeHeightOutput();
}


int main()
{
    Solution solution;
    
    solution.solve();

    return 0;
}