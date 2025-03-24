/*2024级数据结构--数据智能 实验10 堆 B 霍夫曼编码.cpp*/

#include<iostream>

using namespace std;

size_t count[26];
size_t sum = 0;

template<class T>
struct Node
{
    T data;
    Node<T>* left, * right, * parent;
    size_t depth;
    size_t sons;
    bool touched;
    Node(Node<T>* parent, const T& data) : data(data), left(nullptr), right(nullptr), parent(parent), depth(0), sons(0), touched(false) {}
    Node() : left(nullptr), right(nullptr), parent(nullptr), depth(0), sons(0), touched(false),data(0) {}
};

template<class T>
class huffmanTree
{
public:
    huffmanTree() : root(nullptr) {}
    huffmanTree(huffmanTree<T>& tree_1, huffmanTree<T>& tree_2);
    huffmanTree(T data,size_t frequency);
    void ini_code_length(Node<T>* node);
    size_t getFrequency() const { return frequency; }
    Node<T>* getRoot() const { return root; }
private:
    Node<T>* root;
    size_t frequency;
    size_t code_length;
};

template<class T>
huffmanTree<T>::huffmanTree(T data, size_t frequency)
{
    this->root = new Node<T>(nullptr, data);
    this->frequency = frequency;
}

template<class T>
huffmanTree<T>::huffmanTree(huffmanTree<T>& tree_1, huffmanTree<T>& tree_2)
{
    Node<T>* node_1 = tree_1.root;
    Node<T>* node_2 = tree_2.root;
    Node<T>* node_3 = new Node<T>();
    this->root = node_3;
    node_3->left = node_1;
    node_3->right = node_2;
    node_1->parent = node_3;
    node_2->parent = node_3;
    this->frequency = tree_1.frequency + tree_2.frequency;
}

template<class T>
void huffmanTree<T>::ini_code_length(Node<T>* node)
{
    if (node == nullptr)
    {
        return;
    }
    if (node == this->root)
    {
        node->depth = 0;
        ini_code_length(node->left);
        ini_code_length(node->right);
    }
    else
    {
        node->depth = node->parent->depth + 1;
        if (node->left == nullptr && node->right == nullptr)
        {
            // cout << node->data << " " << node->depth << endl;
            sum += node->depth * count[node->data - 'a'];
        }
        ini_code_length(node->left);
        ini_code_length(node->right);
    }
}

class Solution
{
public:
    void solute();
};

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) { len++; }
    return len;
}

void Solution::solute()
{

    char string[1000000];
    size_t cnt = 0;
    huffmanTree<char>* tree[26];
    cin >> string;
    size_t length = strlen(string);
    for (size_t i = 0; i < 26; i++)
    {
        count[i] = 0;
    }
    for (size_t i = 0; i < length; i++)
    {
        count[string[i] - 'a']++;
    }
    for (size_t i = 0; i < 26; i++)
    {
        if (count[i] != 0)
        {
            tree[cnt] = new huffmanTree<char>(char(i + 'a'), count[i]);
            cnt++;
        }
    }
    while (cnt > 1)
    {
        for (size_t i = 0; i < cnt; i++)
        {
            for (size_t j = 0; j < cnt - i - 1; j++)
            {
                if (tree[j]->getFrequency() < tree[j + 1]->getFrequency())
                {
                    swap(tree[j], tree[j + 1]);
                }
            }
        }
        // cout << endl;
        // for (size_t i = 0; i < cnt; i++)
        // {
        //     cout << tree[i]->getFrequency() << endl;
        // }
        // cout << endl;
        huffmanTree<char>* tree_1 = tree[cnt - 1];
        huffmanTree<char>* tree_2 = tree[cnt - 2];
        // delete tree_1;
        // delete tree_2;
        huffmanTree<char>* tree_3 = new huffmanTree<char>(*tree_1, *tree_2);
        tree[cnt - 2] = tree_3;
        cnt--;
    }
    tree[0]->ini_code_length(tree[0]->getRoot());
    cout << sum << endl;
}

int main()
{
    Solution s;
    s.solute();
    return 0;
}