/*2024数据结构--数据智能 实验5 数组和矩阵 A 稀疏矩阵纯数组版.cpp*/
#include <iostream>
#include <vector>

using namespace std;

template<class T>
void my_swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

struct point
{
    int row;
    int col;
};



class SparseMatrix
{
public:
    int row, col, count;
    int data[1000][1000];
    vector<point> points;
    SparseMatrix();
    SparseMatrix(int row, int col);
    SparseMatrix(int row, int col, int count);
    SparseMatrix* operator+(SparseMatrix& other);
    SparseMatrix* operator*(SparseMatrix& other);
    void operator=(SparseMatrix* other);
    void transpose();
    void reset();
    void print();
};


void SparseMatrix::operator=(SparseMatrix* other)
{
    this->row = other->row;
    this->col = other->col;
    this->count = other->count;
    this->points = other->points;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            this->data[i][j] = 0;
        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            this->data[i][j] = other->data[i][j];
        }
    }
    delete other;
}

SparseMatrix::SparseMatrix(int row, int col)
{
    
    this->row = row;
    this->col = col;
    this->count = 0;
    points.clear();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> data[i][j];
            if (data[i][j] != 0)
            {
                count++;
                points.push_back({i, j});
            }
        }
    }
}

SparseMatrix::SparseMatrix()
{
    this->row = 0;
    this->col = 0;
    this->count = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            data[i][j] = 0;
        }
    }
    points.clear();
}


SparseMatrix::SparseMatrix(int row, int col, int count)
{
    this->row = row;
    this->col = col;
    this->count = count;
    points.clear();
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            data[i][j] = 0;
        }
    }
    for (int i = 0; i < count; i++)
    {
        int x, y;
        cin >> x >> y;
        cin >> data[x - 1][y - 1];
        points.push_back({x - 1, y - 1});
    }
}

void SparseMatrix::reset()
{
    for (int i = 0;i < 1000;i++)
    {
        for (int j = 0;j < 1000;j++)
        {
            data[i][j] = 0;
        }
    }
    int row, col;
    this->count = 0;
    this->points.clear();
    cin >> row >> col;
    this->row = row;
    this->col = col;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> data[i][j];
            if (data[i][j] != 0)
            {
                count++;
                points.push_back({i, j});
            }
        }
    }
}

void SparseMatrix::transpose()
{
    vector<int> tempvalue;
    for (int i = 0;i < points.size();i++)
    {
        tempvalue.push_back(data[points[i].row][points[i].col]);
        my_swap(points[i].row, points[i].col);
    }
    for (int i = 0;i < 1000;i++)
    {
        for (int j = 0;j < 1000;j++)
        {
            data[i][j] = 0;
        }
    }
    for (int i = 0;i < points.size();i++)
    {
        data[points[i].row][points[i].col] = tempvalue[i];
    }
    my_swap(row, col);
}


void SparseMatrix::print()
{
    cout << row << " " << col << " " << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}


SparseMatrix* SparseMatrix::operator+(SparseMatrix& other)
{
    if (this->row != other.row || this->col != other.col)
    {
        cout << -1 << endl;
        
        return new SparseMatrix(other);
    }
    else
    {
        SparseMatrix* result = new SparseMatrix;
        result->row = this->row;
        result->col = this->col;
        result->count = 0;
        for (int i = 0;i < this->points.size();i++)
        {
            result->data[this->points[i].row][this->points[i].col] += this->data[this->points[i].row][this->points[i].col];
        }
        
        for (int i = 0;i < other.points.size();i++)
        {
            result->data[other.points[i].row][other.points[i].col] += other.data[other.points[i].row][other.points[i].col];
        }
        
        for (int i = 0;i < result->row;i++)
        {
            for (int j = 0;j < result->col;j++)
            {
                if (result->data[i][j] != 0)
                {
                    result->count++;
                    result->points.push_back({i, j});
                }
            }   
        }
        return result;
    }
}


SparseMatrix* SparseMatrix::operator*(SparseMatrix& other)
{
    if (this->col != other.row)
    {
        cout << -1 << endl;
        return new SparseMatrix(other);
    }
    else
    {
        SparseMatrix* result = new SparseMatrix;
        result->row = this->row;
        result->col = other.col;
        result->count = 0;
        for (int i = 0;i < this->count;i++)
        {
            for (int j = 0;j < other.col;j++)
            {
                result->data[this->points[i].row][j] += this->data[this->points[i].row][this->points[i].col] * other.data[this->points[i].col][j];
            }
        }
        for (int i = 0;i < result->row;i++)
        {
            for (int j = 0;j < result->col;j++)
            {
                if (result->data[i][j] != 0)
                {
                    result->count++;
                    result->points.push_back({i, j});
                }
            }   
        }
        return result;
    }
}

class Solution
{
public:
    void solute();
    void test();
};

void Solution::solute()
{
    int n;
    cin >> n;
    int operation;
    cin >> operation;
    int row, col;
    cin >> row >> col;
    SparseMatrix matrix(row, col);
    for (int i = 1;i < n;i++)
    {
        cin >> operation;
        if (operation == 1)
        {
            matrix.reset();
        }
        else if (operation == 2)
        {
            int row, col, count;
            cin >> row >> col >> count;
            SparseMatrix matrix1(row, col, count);
            matrix = matrix * matrix1;
        }
        else if (operation == 3)
        {
            int row, col, count;
            cin >> row >> col >> count;
            SparseMatrix matrix1(row, col, count);
            matrix = matrix + matrix1;
        }
        else if (operation == 4)
        {
            matrix.print();
        }
        else if (operation == 5)   
        {
            matrix.transpose();
        }
    }    
}

void Solution::test()
{
    int row, col, count;
    cin >> row >> col;
    SparseMatrix matrix(row, col);
    
    matrix.print();
    matrix.transpose();
    matrix.print();

}
int main()
{
    Solution solution;
    solution.solute();
    // solution.test();
    return 0;
}
