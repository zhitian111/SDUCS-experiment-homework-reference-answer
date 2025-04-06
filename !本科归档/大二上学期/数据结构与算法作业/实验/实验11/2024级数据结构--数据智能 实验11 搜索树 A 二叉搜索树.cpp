/*2024级数据结构--数据智能 实验11 搜索树 A 二叉搜索树.cpp*/
#include <iostream>

using namespace std;


template<class T>
struct Node
{
    T data;
    Node<T>* left, * right, * parent;
    size_t depth;
    size_t sons;
    bool touched;
    size_t left_size;
    size_t right_size;
    Node(Node<T>* parent, const T& data) : data(data), left(nullptr), right(nullptr), parent(parent), depth(0), sons(0),left_size(0), right_size(0), touched(false) {}
    Node(): left(nullptr), right(nullptr), parent(nullptr), depth(0), sons(0), touched(false), left_size(0), right_size(0) {}
};



template<class T>
class BinarySearchTree
{
private:
    Node<T>* root;
    size_t count;
    size_t depth;
public:
    int xor1;
    BinarySearchTree() : root(nullptr), count(0), depth(0), xor1(0) {}
    BinarySearchTree(size_t size);
    ~BinarySearchTree() {}
    Node<T>* getRoot() { return root; }
    bool insert(const T& data);
    bool find(const T& data);
    bool erase(const T& data);
    void print() const;
    void preOrderPrint(const Node<T>* p) const;
    void inOrderPrint();
    void iniNode(Node<T>* p);
    void iniSize(Node<T>* p);
    bool eraseRank(size_t rank);
    Node<T>* findRank(size_t rank);
};

template<class T>
BinarySearchTree<T>::BinarySearchTree(size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        T data;
        cin >> data;
        insert(data);
    }
}

template<class T>
bool BinarySearchTree<T>::insert(const T& data)
{
    if (root == nullptr)
    {
        root = new Node<T>(nullptr, data);
        count++;
        depth = 1;
        return true;
    }
    Node<T>* p = root;
    while (p != nullptr)
    {
        xor1 ^= p->data;
        if (data < p->data && p->left != nullptr)
        {
            p = p->left;
        }
        else if (data > p->data && p->right != nullptr)
        {
            p = p->right;
        }
        else if (data < p->data && p->left == nullptr)
        {
            Node<T>* node = new Node<T>(p, data);
            p->left = node;
            count++;
            p = p->left;
            while (p != nullptr)
            {
                if (p->parent == nullptr)
                {
                    break;
                }
                if (p->parent->left == p)
                {
                    p->parent->left_size++;
                    p = p->parent;
                }
                else if (p->parent->right == p)
                {
                    p->parent->right_size++;
                    p = p->parent;
                }
            }
            return true;
        }
        else if (data > p->data && p->right == nullptr)
        {
            Node<T>* node = new Node<T>(p, data);
            p->right = node;
            count++;
            p = p->right;
            while (p != nullptr)
            {
                if (p->parent == nullptr)
                {
                    break;
                }
                if (p->parent->left == p)
                {
                    p->parent->left_size++;
                    p = p->parent;
                }
                else if (p->parent->right == p)
                {
                    p->parent->right_size++;
                    p = p->parent;
                }
            }
            return true;
        }
        else if (data == p->data)
        {
            cout << 0 << endl;
            return false;
        }
    }
    return false;
}

template<class T>
bool BinarySearchTree<T>::find(const T& data)
{
    Node<T>* p = root;
    while (p != nullptr)
    {
        if (data == p->data)
        {
            // cout << 1 << endl;
            xor1 ^= p->data;
            return true;
        }
        else if (data < p->data && p->left != nullptr)
        {
            xor1 ^= p->data;
            p = p->left;
        }
        else if (data > p->data && p->right != nullptr)
        {
            xor1 ^= p->data;
            p = p->right;
        }
        else
        {
            xor1 ^= p->data;
            break;
        }
    }
    cout << 0 << endl;
    return false;
}

template<class T>
bool BinarySearchTree<T>::erase(const T& data)
{
    Node<T>* p = root;
    while (p != nullptr)
    {
        if (data == p->data)
        {
            this->xor1 ^= p->data;

            /*  删除节点
                1. 如果节点为叶节点则直接结束
                2. 如果节点只有左/右子树，则将左/右子树的根节点转移过来
                3. 如果节点同时用左右子树，则将左子树中的最大值转移过来，然后删除最大值节点
                    这个被删除的最大值节点只有两种情况：为叶节点或者只有左子树(题目让使用右子树中最小的节点，等价)
            */
            if (p == root)
            {
                if (p->left == nullptr && p->right == nullptr)
                {
                    count--;
                    delete p;
                    root = nullptr;
                    return true;
                }
                else if (p->left == nullptr && p->right != nullptr)
                {
                    root = p->right;
                    root->parent = nullptr;
                    count--;
                    delete p;
                    return true;
                }
                else if (p->left != nullptr && p->right == nullptr)
                {
                    root = p->left;
                    root->parent = nullptr;
                    count--;
                    delete p;
                    return true;
                }
                else if (p->left != nullptr && p->right != nullptr)
                {
                    Node<T>* max_node = p->right;
                    while (max_node->left != nullptr)
                    {
                        max_node = max_node->left;
                    }
                    p->data = max_node->data;
                    auto temp = max_node;
                    while (temp != nullptr)
                    {
                        if (temp->parent == nullptr)
                        {
                            break;
                        }
                        if (temp->parent->left == temp)
                        {
                            temp->parent->left_size--;
                            temp = temp->parent;
                        }
                        else if (temp->parent->right == temp)
                        {
                            temp->parent->right_size--;
                            temp = temp->parent;
                        }
                    }
                    if (max_node->right != nullptr)
                    {
                        max_node->right->parent = max_node->parent;
                        if (max_node->parent->left == max_node)
                        {
                            max_node->parent->left = max_node->right;
                        }
                        if (max_node->parent->right == max_node)
                        {
                            max_node->parent->right = max_node->right;
                        }
                    }
                    if (max_node->right == nullptr)
                    {
                        if (max_node->parent->left == max_node)
                        {
                            max_node->parent->left = nullptr;
                        }
                        else if (max_node->parent->right == max_node)
                        {
                            max_node->parent->right = nullptr;
                        }    
                    }
                    

                    delete max_node;
                    count--;
                    return true;
                }
            }

            else if (p != root)
            {
                if (p->left == nullptr && p->right == nullptr)//叶节点
                {
                    auto temp = p;
                    while (temp != nullptr)
                    {
                        if (temp->parent == nullptr)
                        {
                            break;
                        }
                        if (temp->parent->left == temp)
                        {
                            temp->parent->left_size--;
                            temp = temp->parent;
                        }
                        else if (temp->parent->right == temp)
                        {
                            temp->parent->right_size--;
                            temp = temp->parent;
                        }
                    }
                    if (p->parent->left == p)
                    {
                        p->parent->left = nullptr;
                    }
                    else if (p->parent->right == p)
                    {
                        p->parent->right = nullptr;
                    }
                    count--;

                    delete p;
                    return true;
                }
                else if (p->left == nullptr && p->right != nullptr)//有右子树
                {
                    auto temp = p;
                    while (temp != nullptr)
                    {
                        if (temp->parent == nullptr)
                        {
                            break;
                        }
                        if (temp->parent->left == temp)
                        {
                            temp->parent->left_size--;
                            temp = temp->parent;
                        }
                        else if (temp->parent->right == temp)
                        {
                            temp->parent->right_size--;
                            temp = temp->parent;
                        }
                    }
                    if (p->parent->left == p)
                    {
                        p->parent->left = p->right;
                    }
                    else if (p->parent->right == p)
                    {
                        p->parent->right = p->right;
                    }
                    p->right->parent = p->parent;
                    count--;

                    delete p;
                    return true;
                }
                else if (p->left != nullptr && p->right == nullptr)//有左子树
                {
                    auto temp = p;
                    while (temp != nullptr)
                    {
                        if (temp->parent == nullptr)
                        {
                            break;
                        }
                        if (temp->parent->left == temp)
                        {
                            temp->parent->left_size--;
                            temp = temp->parent;
                        }
                        else if (temp->parent->right == temp)
                        {
                            temp->parent->right_size--;
                            temp = temp->parent;
                        }
                    }
                    if (p->parent->left == p)
                    {
                        p->parent->left = p->left;
                    }
                    else if (p->parent->right == p)
                    {
                        p->parent->right = p->left;
                    }
                    p->left->parent = p->parent;
                    count--;

                    delete p;
                    return true;
                }
                else if (p->left != nullptr && p->right != nullptr)//有左右子树
                {
                    {
                        Node<T>* max_node = p->right;
                        while (max_node->left != nullptr)
                        {
                            max_node = max_node->left;
                        }
                        p->data = max_node->data;
                        count--;
                        auto temp = max_node;
                        while (temp != nullptr)
                        {
                            if (temp->parent == nullptr)
                            {
                                break;
                            }
                            if (temp->parent->left == temp)
                            {
                                temp->parent->left_size--;
                                temp = temp->parent;
                            }
                            else if (temp->parent->right == temp)
                            {
                                temp->parent->right_size--;
                                temp = temp->parent;
                            }
                        }
                        if (max_node->right != nullptr)//有右子树
                        {
                            max_node->right->parent = max_node->parent;
                            if (max_node->parent->left == max_node)
                            {
                                max_node->parent->left = max_node->right;
                            }
                            else if (max_node->parent->right == max_node)
                            {
                                max_node->parent->right = max_node->right;
                            }
                        }
                        if (max_node->right == nullptr)//叶节点
                        {
                            if (max_node->parent->left == max_node)
                            {
                                max_node->parent->left = nullptr;
                            }
                            else if (max_node->parent->right == max_node)
                            {
                                max_node->parent->right = nullptr;
                            }                        
                        }

                        delete max_node;
                        return true;
                    }
                }                
            }

        }
        else if (data < p->data && p->left != nullptr)
        {
            this->xor1 ^= p->data;
            p = p->left;
        }
        else if (data > p->data && p->right != nullptr)
        {
            this->xor1 ^= p->data;
            p = p->right;
        }
        else
        {
            this->xor1 ^= p->data;
            break;
        }
    }
    cout << 0 << endl;
    return false;
}


//前序遍历输出
template<class T>
void BinarySearchTree<T>::print() const
{
    preOrderPrint(this->root);
    cout << endl;
}




template<class T>
void BinarySearchTree<T>::preOrderPrint(const Node<T>* p) const
{
    if (p == nullptr)
    {
        return;
    }
    cout << p->data << " ";
    preOrderPrint(p->left);
    preOrderPrint(p->right);
}


template<class T>
void BinarySearchTree<T>::inOrderPrint()
{
    Node<T>* node = root;
    iniNode(node);
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
                if (node == nullptr)
                {
                    break;
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
void BinarySearchTree<T>::iniNode(Node<T>* p)
{
    if (p == nullptr)
    {
        return;
    }
    iniNode(p->left);
    iniNode(p->right);
    p->touched = false;
}

template<class T>
void BinarySearchTree<T>::iniSize(Node<T>* p)
{
    if (p == nullptr)
    {
        return;
    }
    iniSize(p->left);
    iniSize(p->right);
    if (p->left == nullptr && p->right == nullptr)
    {
        p->left_size = 0;
        p->right_size = 0;
    }
    else if (p->left == nullptr && p->right != nullptr)
    {
        p->left_size = 0;
        p->right_size = p->right->left_size + p->right->right_size + 1;
    }
    else if (p->left != nullptr && p->right == nullptr)
    {
        p->left_size = p->left->left_size + p->left->right_size + 1;
        p->right_size = 0;
    }
    else
    {
        p->left_size = p->left->left_size + p->left->right_size + 1;
        p->right_size = p->right->left_size + p->right->right_size + 1;
    }
}

template<class T>
Node<T>* BinarySearchTree<T>::findRank(size_t rank)
{
    if (rank > count || rank < 1)
    {
        return nullptr;
    }
    size_t temp = rank;
    Node<T>* node = root;
    while (node != nullptr)
    {
        this->xor1 ^= node->data;
        if (node->left_size + 1 == temp)
        {
            return node;
        }
        else if (node->left_size + 1 < temp)
        {
            temp -= (node->left_size + 1);
            node = node->right;
        }
        else
        {
            node = node->left;
        }
    }
    return nullptr;
}

template<class T>
bool BinarySearchTree<T>::eraseRank(size_t rank)
{
    if (rank > count || rank < 1)
    {
        return false;
    }
    size_t temp = rank;
    Node<T>* p = root;
    while (p != nullptr)
    {
        this->xor1 ^= p->data;
        if (p->left_size + 1 == temp)
        {
            if (p == root)
            {
                if (p->left == nullptr && p->right == nullptr)
                {
                    count--;
                    delete p;
                    root = nullptr;
                    return true;
                }
                else if (p->left == nullptr && p->right != nullptr)
                {
                    root = p->right;
                    root->parent = nullptr;
                    count--;
                    delete p;
                    return true;
                }
                else if (p->left != nullptr && p->right == nullptr)
                {
                    root = p->left;
                    root->parent = nullptr;
                    count--;
                    delete p;
                    return true;
                }
                else if (p->left != nullptr && p->right != nullptr)
                {
                    Node<T>* max_node = p->right;
                    while (max_node->left != nullptr)
                    {
                        max_node = max_node->left;
                    }
                    p->data = max_node->data;
                    auto temp = max_node;
                    while (temp != nullptr)
                    {
                        if (temp->parent == nullptr)
                        {
                            break;
                        }
                        if (temp->parent->left == temp)
                        {
                            temp->parent->left_size--;
                            temp = temp->parent;
                        }
                        else if (temp->parent->right == temp)
                        {
                            temp->parent->right_size--;
                            temp = temp->parent;
                        }
                    }   
                    if (max_node->right != nullptr)
                    {
                        max_node->right->parent = max_node->parent;
                        if (max_node->parent->left == max_node)
                        {
                            max_node->parent->left = max_node->right;
                        }
                        if (max_node->parent->right == max_node)
                        {
                            max_node->parent->right = max_node->right;
                        }
                    }
                    if (max_node->right == nullptr)
                    {
                        if (max_node->parent->left == max_node)
                        {
                            max_node->parent->left = nullptr;
                        }
                        else if (max_node->parent->right == max_node)
                        {
                            max_node->parent->right = nullptr;
                        }    
                    }
                
                    
                    delete max_node;
                    count--;
                    return true;
                }
            }
            else if (p != root)
            {
                if (p->left == nullptr && p->right == nullptr)
                {

                    auto temp = p;
                    while (temp != nullptr)
                    {
                        if (temp->parent == nullptr)
                        {
                            break;
                        }
                        if (temp->parent->left == temp)
                        {
                            temp->parent->left_size--;
                            temp = temp->parent;
                        }
                        else if (temp->parent->right == temp)
                        {
                            temp->parent->right_size--;
                            temp = temp->parent;
                        }
                    }
                    if (p->parent->left == p)
                    {
                        p->parent->left = nullptr;
                    }
                    else if (p->parent->right == p)
                    {
                        p->parent->right = nullptr;
                    }
                    count--;

                    delete p;
                    return true;
                }
                else if (p->left == nullptr && p->right != nullptr)
                {
                    auto temp = p;
                    while (temp != nullptr)
                    {
                        if (temp->parent == nullptr)
                        {
                            break;
                        }
                        if (temp->parent->left == temp)
                        {
                            temp->parent->left_size--;
                            temp = temp->parent;
                        }
                        else if (temp->parent->right == temp)
                        {
                            temp->parent->right_size--;
                            temp = temp->parent;
                        }
                    }
                    if (p->parent->left == p)
                    {
                        p->parent->left = p->right;
                    }
                    else if (p->parent->right == p)
                    {
                        p->parent->right = p->right;
                    }
                    p->right->parent = p->parent;
                    count--;

                    delete p;
                    return true;
                }
                else if (p->left != nullptr && p->right == nullptr)
                {
                    auto temp = p;
                    while (temp != nullptr)
                    {
                        if (temp->parent == nullptr)
                        {
                            break;
                        }
                        if (temp->parent->left == temp)
                        {
                            temp->parent->left_size--;
                            temp = temp->parent;
                        }
                        else if (temp->parent->right == temp)
                        {
                            temp->parent->right_size--;
                            temp = temp->parent;
                        }
                    }
                    if (p->parent->left == p)
                    {
                        p->parent->left = p->left;
                    }
                    else if (p->parent->right == p)
                    {
                        p->parent->right = p->left;
                    }
                    p->left->parent = p->parent;
                    count--;

                    delete p;
                    return true;
                }
                else if (p->left != nullptr && p->right != nullptr)
                {
                    {
                        Node<T>* max_node = p->right;
                        while (max_node->left != nullptr)
                        {
                            max_node = max_node->left;
                        }
                        p->data = max_node->data;
                        count--;
                        auto temp = max_node;
                        while (temp != nullptr)
                        {
                            if (temp->parent == nullptr)
                            {
                                break;
                            }
                            if (temp->parent->left == temp)
                            {
                                temp->parent->left_size--;
                                temp = temp->parent;
                            }
                            else if (temp->parent->right == temp)
                            {
                                temp->parent->right_size--;
                                temp = temp->parent;
                            }
                        } 
                        if (max_node->right != nullptr)
                        {
                            max_node->right->parent = max_node->parent;
                            if (max_node->parent->left == max_node)
                            {
                                max_node->parent->left = max_node->right;
                            }
                            else if (max_node->parent->right == max_node)
                            {
                                max_node->parent->right = max_node->right;
                            }
                        }
                        if (max_node->right == nullptr)
                        {
                            if (max_node->parent->left == max_node)
                            {
                                max_node->parent->left = nullptr;
                            }
                            else if (max_node->parent->right == max_node)
                            {
                                max_node->parent->right = nullptr;
                            }                        
                        }
                           
                        delete max_node;
                        return true;
                    }
                }                
            }
            
            return true;
        }
        else if (p->left_size + 1 < temp)
        {
            temp -= p->left_size + 1;
            p = p->right;
        }
        else
        {
            p = p->left;
        }
    }
    return false;
}


class Solution
{
public:
    void solve();
    void test();
};



void Solution::solve()
{
    ios::sync_with_stdio(false);
    BinarySearchTree<long long> bst;
    size_t m;
    cin >> m;
    for (size_t i = 0; i < m; i++)
    {
        long long op, x;
        cin >> op >> x;
        if (op == 0)
        {
            bst.xor1 = 0;
            if (bst.insert(x))
            {
                cout << bst.xor1 << endl;
            }
        }
        else if (op == 1)
        {
            bst.xor1 = 0;
            if (bst.find(x))
            {
                cout << bst.xor1 << endl;                
            }
        }
        else if (op == 2)
        {
            bst.xor1 = 0;
            if (bst.erase(x))
            {                
                cout << bst.xor1 << endl;
            }
        }
        else if (op == 3)
        {
            // bst.iniSize(bst.getRoot());
            bst.xor1 = 0;
            Node<long long>* p = bst.findRank(x);
            if (p != nullptr)
            {
                cout << bst.xor1 << endl;
            }
            else
            {
                cout << 0 << endl;
            }
        }
        else if (op == 4)
        {
            // bst.iniSize(bst.getRoot());
            bst.xor1 = 0;
            if (bst.eraseRank(x))
            {
                cout << bst.xor1 << endl;
            }
            else
            {
                cout << 0 << endl;
            }
        }
        // cout << endl;
        // cout << "preorder: ";
        // bst.print();
        // cout << endl;
        // cout << "inorder: ";
        // bst.inOrderPrint();
        // cout << endl;
    }

}

void Solution::test()
{
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.inOrderPrint();
    bst.iniSize(bst.getRoot());
    bst.eraseRank(2);
    bst.inOrderPrint(); 
    cout << bst.findRank(2)->data << endl;
}

int main()
{
    Solution solution;
    solution.solve();
    // solution.test();
    return 0;
}