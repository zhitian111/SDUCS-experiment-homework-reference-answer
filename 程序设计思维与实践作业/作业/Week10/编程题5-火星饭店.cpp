﻿#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;


template <typename T> 
class DynamicSegmentTree
{
    struct DynamicSegmentTreeNode
    {
        T val;
        DynamicSegmentTreeNode* left;
        DynamicSegmentTreeNode* right;
        DynamicSegmentTreeNode() : val(T()), left(nullptr), right(nullptr) {}
        DynamicSegmentTreeNode(const T& val) : val(val), left(nullptr), right(nullptr) {}
    };
private:
    DynamicSegmentTreeNode* root;
    size_t cnt;
    size_t max_size;
    const T DEFAULT = -numeric_limits<T>::max();
    
    T decide(const T& left, const T& right)
    {
        return max(left, right);
    }

    void update(DynamicSegmentTreeNode*& node, size_t start, size_t end, size_t pos, const T& val)
    {
        // 如果节点不存在
        if (node == nullptr)
        {
            node = new DynamicSegmentTreeNode(DEFAULT);
        }
        // 如果达到叶节点
        if (start == end && start == pos)
        {
            node->val = val;
            return;
        }
        if (start == end && start != pos)
        {
            return;
        }
        
        size_t mid = start + (end - start) / 2;
        if (pos <= mid)
        {
            update(node->left, start, mid, pos, val);
        }
        else
        {
            update(node->right, mid + 1, end, pos, val);
        }
        node->val = decide(node->left ? node->left->val : DEFAULT,
            node->right ? node->right->val : DEFAULT);
    }
    T query(DynamicSegmentTreeNode* node, size_t start, size_t end, size_t query_start, size_t query_end)
    {
        if (node == nullptr)
        {
            return DEFAULT;
        }
        // 当前处理区间是查找区间的子集
        if (start >= query_start && query_end >= end)
        {
            // cout << "find:\t" << node->val << endl;
            return node->val;
        }
        // 当前区间在查找区间之外
        if (start > query_end || end < query_start)
        {
            return DEFAULT;
        }
        // 递归处理左右子树
        size_t mid = start + (end - start) / 2;
                // 左子树left -> mid
        return decide(query(node->left, start, mid, query_start, query_end),
                // 右子树mid + 1 -> right
            query(node->right, mid + 1, end, query_start, query_end));
    }

public:
    DynamicSegmentTree() :root(nullptr), cnt(0), max_size(0) {}
    DynamicSegmentTree(const size_t max_size): root(nullptr), cnt(0), max_size(max_size) {}
    ~DynamicSegmentTree()
    {
        clear(root);
    }

    size_t size() const
    {
        return cnt;
    }
    
    void insert(const T& val)
    {
        if (cnt == max_size)
        {
            cout << "error: segment tree is full" << endl;
            return;
        }
        
        cnt++;
        update(root, 0, max_size - 1, cnt - 1, val);
    }
    
    void clear(DynamicSegmentTreeNode* node)
    {
        if (node == nullptr)
        {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }
    void display()
    {
        queue<DynamicSegmentTreeNode*> q;
        q.push(root);
        while (!q.empty())
        {
            if (q.front() == nullptr)
            {
                q.pop();
                cout << "null ";
                continue;
            }


            auto& node = *q.front();
            q.pop();
            q.push(node.left);
            q.push(node.right);
            cout << node.val << " ";
        }
    }
    T query(size_t start, size_t end)
    {
        return query(root, 0, max_size - 1, start, end);
    }
};

void test()
{
    DynamicSegmentTree<int> st(100);
    for (int i = 0;i < 100; i++)
    {
        st.insert(i);
    }
    // st.display();
    // cout << st.query(1,97) << endl;
}

void solve()
{
    size_t m, p;
    cin >> m >> p;
    size_t a = 0;
    DynamicSegmentTree<int> st(m);
    vector<int> final_ans;
    for (size_t i = 0; i < m; i++)
    {
        char c;
        cin >> c;
        if (c == 'Q')
        {
            size_t l;
            cin >> l;
            auto ans = st.query(st.size() - l, st.size() - 1);

            final_ans.push_back(ans);
            a = ans;
        }
        if (c == 'A')
        {
            size_t t;
            cin >> t;
            st.insert((t + a) % p);
        }
    }
    for (auto& ans : final_ans)
    {
        cout << ans << endl;
    }
}

int main()
{
    // test();
    solve();
    return 0;
}