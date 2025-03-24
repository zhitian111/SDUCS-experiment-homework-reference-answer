/*2024数据结构--数据智能 实验5 数组和矩阵 A 稀疏矩阵.cpp*/
#include <iostream>
#include <stdio.h>
#define debug cout<<__LINE__<<": "<<__FUNCTION__<<endl;
using namespace std;

template<class T>
void my_swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}


template<class T>
class my_iterator
{
    private:
        T* current;
        unsigned int index;
    public:
        my_iterator(T* current, unsigned int index = 0) : current(current), index(index) {}
        T* getCurrent(){ return current; }
        T& getData()  const { return *current; }
        unsigned int getIndex()  const{ return index; }
        void operator++() { current++; index++; }
        void operator--() { current--; index--; }
        void operator++(int) { current++; index++; }
        void operator--(int) { current--; index--; }
        bool operator==(const my_iterator& my_iterator) const { return index == my_iterator.getIndex(); }
        bool operator!=(const my_iterator& my_iterator) const { return index != my_iterator.getIndex(); }
        bool operator<(const my_iterator& my_iterator) const { return index < my_iterator.getIndex(); }
        bool operator>(const my_iterator& my_iterator) const { return index > my_iterator.getIndex(); }
        unsigned int getIndex() { return index; }
        void reset(T* current) { this->current = current; }
};




template<class T>
void quick_sort(my_iterator<T> head, my_iterator<T> tail)
{
    if (head == tail || tail < head) { return; }
    T pivot = *(head.getCurrent());
    my_iterator<T> i = head;
    my_iterator<T> j = tail;
    while (i < j)
    {
        while (*(j.getCurrent()) >= pivot && i < j)
        {
            j--;
        }
        if (i<j)
        {
            *(i.getCurrent()) = *(j.getCurrent());
        }
        while (*(i.getCurrent()) <= pivot && i < j)
        {
            i++;
        }
        if (i<j)
        {
            *(j.getCurrent()) = *(i.getCurrent());
        }        
        if (i==j)
        {
            *(i.getCurrent()) = pivot;
        }
    }
    my_iterator<T> j2 = j;
    j2++;
    quick_sort(head, j);
    quick_sort(j2, tail);
}

template<class T>
class arraylist
{
private:
    T* datas;
    int count;
    int capacity;
    bool is_sorted;
    void copy(T* copyed, T* to, int acount = -1);

public:
    T& operator[](const unsigned int subscript) { return datas[subscript]; };
    const T& operator[](const unsigned int subscript) const { return datas[subscript]; };
    int find_first(const T& target) const;
    void push_back(const T& element);
    void erase(const T& target);
    void clear();
    void double_capacity();
    int getCapacity() const{return capacity;};
    bool is_in(const T& target) const;
    int size() const { return count; };
    void self_quick_sort() { if (count == 0) { return; }quick_sort(my_iterator<T>(datas, 0), my_iterator<T>(datas + count - 1, count - 1)); is_sorted = true; };
    bool getSorted() const { return is_sorted; };
    arraylist();
    ~arraylist() { delete[] datas; };
    arraylist(const arraylist<T>& other);
    void operator=(const arraylist<T>& other);
};

template<class T>
void arraylist<T>::copy(T* copyed, T* to,int acount)
{
    if (acount == -1)
    {
        acount = this->count;
    }
    for (size_t i = 0; i < acount; i++)
    {
        to[i] = copyed[i];
    }
}

template<class T>
void arraylist<T>::double_capacity()
{
    capacity *= 2;
    T* new_datas = new T[capacity];
    copy(datas, new_datas, count);
    delete[] datas;
    datas = new_datas;
    is_sorted = false;
}



template<class T>
void arraylist<T>::operator=(const arraylist<T>& other)
{
    capacity = other.getCapacity();
    count = other.size();
    datas = new T[capacity];
    copy(other.datas, datas, count);
    is_sorted = other.getSorted();
}


template<class T>
void arraylist<T>::push_back(const T& element)
{
    // if (count == 0)
    // {
    //     datas = new T[1];
    //     datas[0] = element;
    //     count = 1;
    //     capacity = 1;
    //     return;
    // }
    if (count + 1 > capacity)
    {
        double_capacity();
    }
    datas[count] = element;
    is_sorted = false;
    count++;
}



template<class T>
int arraylist<T>::find_first(const T& target) const
{
    if (is_sorted == false)
    {        
        for (size_t i = 0; i < count; i++)
        {
            if (target == datas[i])
            {
                return i;
            }
        }
        return -1;
    }
    if (is_sorted == true)
    {
        int head = 0;
        int tail = count - 1;
        while (head <= tail)
        {
            int mid = head + ((tail - head) / 2);

            if (target == datas[mid])
            {
                return mid;
            }
            if (target < datas[mid])
            {
                tail = mid - 1;
            }
            if (target > datas[mid])
            {
                head = mid + 1;
            }
        }
    }
    return -1;

}


template<class T>
void arraylist<T>::clear()
{
    if (datas!= nullptr)
    {
        delete[] datas;
    }
    count = 0;
    capacity = 16;
    is_sorted = false;
    datas = new T[capacity];

}


template<class T>
void arraylist<T>::erase(const T& target)
{
    int index = find_first(target);

    T* new_datas = new T[count - 1];

    for (size_t i = 0; i < count; i++)
    {
        if (i < index)
        {
            new_datas[i] = datas[i];
        }
        if (i == index)
        {
            continue;
        }
        if (i > index)
        {
            new_datas[i - 1] = datas[i];
        }
    }

    delete[] datas;

    count--;
    
    datas = new_datas;
}

template<class T>
bool arraylist<T>::is_in(const T& target) const
{
    int index = this->find_first(target);

    if (index != -1)
    {
        return true;
    }
    if (index == -1)
    {
        return false;
    }
    return false;
}

template<class T>
arraylist<T>::arraylist()
{
    datas = nullptr;
    count = 0;
    capacity = 16;
    is_sorted = false;
    
    datas = new T[capacity];

}

template<class T>
arraylist<T>::arraylist(const arraylist<T>& other)
{
    capacity = other.getCapacity();
    count = other.size();
    datas = new T[capacity];
    copy(other.datas, datas, count);
}



struct point
{
    int row, col;
    int value;
};

bool operator==(const point& a, const point& b)
{
    if (a.row == b.row && a.col == b.col)
    {
        return true;
    }
    return false;
}

bool operator!=(const point& a, const point& b)
{
    return !(a == b);
}

bool operator<(const point& a, const point& b)
{
    if (a.row < b.row)
    {
        return true;
    }
    if (a.row == b.row && a.col < b.col)
    {
        return true;
    }
    return false;
}

bool operator>(const point& a, const point& b)
{
    return !(a < b || a == b);
}

bool operator<=(const point& a, const point& b)
{
    return a < b || a == b;
}

bool operator>=(const point& a, const point& b)
{
    return a > b || a == b;
}

void operator<<(const ostream& os, const point& a)
{
    cout << "(" << a.row << "," << a.col << "," << a.value << ")";
}


class SparseMatrix {
private:
    int row, col;
    int count;
    arraylist<point> values;
public:
    SparseMatrix(int r, int c);
    SparseMatrix(int r, int c, int count);
    SparseMatrix(const SparseMatrix& other);
    SparseMatrix();
    void print();
    void reset(int r, int c);
    int getRow() const { return row; }
    int getCol() const{ return col; }
    int getCount() const { return count; }
    void resetRow(int r) { row = r; }
    void resetCol(int c) { col = c; }
    void resetCount(int c) { count = c; }
    arraylist<point>& getValues() { return values; }
    const arraylist<point>& getValues() const { return values; }
    void transpose();
    SparseMatrix operator+(SparseMatrix& other);
    SparseMatrix operator*(SparseMatrix& other);
};


SparseMatrix::SparseMatrix(int r, int c)
{
    row = r;
    col = c;
    count = 0;
    values = arraylist<point>();

    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            int value;
            scanf("%d", &value);
            if (value != 0)
            {
                point p;
                p.row = i;
                p.col = j;
                p.value = value;
                values.push_back(p);
                count++;
            }
        }
    }
    this->values.self_quick_sort();
}

SparseMatrix::SparseMatrix()
{
    row = 0;
    col = 0;
    count = 0;
    values = arraylist<point>();
}

SparseMatrix::SparseMatrix(const SparseMatrix& other) :
    values(other.getValues())
{
    this->row = other.getRow();
    this->col = other.getCol();
    this->count = other.getCount();
}

SparseMatrix::SparseMatrix(int r, int c, int count)
{
    row = r;
    col = c;
    this->count = count;
    values = arraylist<point>();

    for (size_t i = 0; i < count; i++)
    {
        point p;
        scanf("%d %d %d", &p.row, &p.col, &p.value);
        p.row--;
        p.col--;
        values.push_back(p);
    }

}

SparseMatrix SparseMatrix::operator+(SparseMatrix& other)
{
    if (this->row != other.getRow() || this->col != other.getCol())
    {
        return other;
    }
    else
    {
        SparseMatrix result;
        result.resetRow(this->row);
        result.resetCol(this->col);
        result.resetCount(this->count);
        result.getValues() = this->values;
        const arraylist<point>& other_values = other.getValues();
        arraylist<point>& result_values = result.getValues();
        for (size_t i = 0; i < other.getCount(); i++)
        {
            point p = other_values[i];
            int index = result_values.find_first(p);
            if (index == -1)
            {
                result_values.push_back(p);
                result_values.self_quick_sort();
                result.resetCount(result.getCount() + 1);
            }
            else
            {
                result_values[index].value += other_values[i].value;
            }
        }
        return result;
    }
}

SparseMatrix SparseMatrix::operator*(SparseMatrix& other)
{
    if (this->col != other.getRow())
    {
        return other;
    }
    else
    {
        SparseMatrix result;
        result.resetRow(this->row);
        result.resetCol(other.getCol());
        result.resetCount(0);
        const arraylist<point>& other_values = other.getValues();
        arraylist<point>& result_values = result.getValues();
        //todo 稀疏矩阵简易乘法算法
        for (size_t i = 0; i < count; i++)
        {
            point p = values[i];
            point new_p;
            new_p.row = p.row;
            for (size_t j = 0;j < other.getCount();j++)
            {
                point q = other_values[j];
                if (p.col == q.row)
                {
                    new_p.col = q.col;
                    new_p.value = p.value * q.value;
                    int index = result_values.find_first(new_p);
                    if (index != -1)
                    {
                        result_values[index].value += new_p.value;
                    }
                    else
                    {
                        result_values.push_back(new_p);
                        result_values.self_quick_sort();
                        result.resetCount(result.getCount() + 1);
                    }
                }
            }
        }
    return result;
    }
}

void SparseMatrix::transpose()
{
    my_swap(this->row, this->col);
    for (size_t i = 0; i < count; i++)
    {
        my_swap(values[i].row, values[i].col);
    }
}

void print(const SparseMatrix& matrix)
{
    static int tem_matrix[501][501];
    printf("%d %d\n", matrix.getRow(), matrix.getCol());
    const arraylist<point>& values = matrix.getValues();
    for (size_t i = 0; i < matrix.getCount(); i++)
    {
        tem_matrix[values[i].row][values[i].col] = values[i].value;
    }
    for (size_t i = 0; i < matrix.getRow(); i++)
    {
        for (size_t j = 0; j < matrix.getCol(); j++)
        {
            printf("%d ", tem_matrix[i][j]);
            tem_matrix[i][j] = 0;
        }
        printf("\n");
    }
}


void SparseMatrix::print()
{
    printf("%d %d\n", row, col);
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            point p;
            p.row = i;
            p.col = j;
            int index = values.find_first(p);
            if (index != -1)
            {
                printf("%d ", values[index].value);
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void SparseMatrix::reset(int r, int c)
{
    row = r;
    col = c;
    count = 0;

    values.clear();

    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            int value;
            scanf("%d", &value);
            if (value != 0)
            {
                point p;
                p.row = i;
                p.col = j;
                p.value = value;
                values.push_back(p);
                count++;
            }
        }
    }

}

class Solution
{
public:
    void solute();
    void test();
};

void Solution::test()
{

    int row, col;
    cin >> row >> col;
    SparseMatrix matrix(row, col);
    matrix.print();
    matrix.transpose();
    matrix.print();
}

void Solution::solute()
{

    int n;
    scanf("%d", &n);
    int operation;
    scanf("%d", &operation);
    int row, col;
    scanf("%d %d", &row, &col);
    SparseMatrix matrix(row, col);
    for (int i = 1;i < n;i++)
    {
        scanf("%d", &operation);
        if (operation == 1)
        {
            int row, col;
            scanf("%d %d", &row, &col);
            matrix.reset(row, col);
        }
        else if (operation == 2)
        {
            int row, col, count;
            scanf("%d %d %d", &row, &col, &count);
            SparseMatrix matrix1(row, col, count);
            matrix = matrix*matrix1;
        }
        else if (operation == 3)
        {
            int row, col, count;
            scanf("%d %d %d", &row, &col, &count);
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

int main()
{
    Solution solution;
    // solution.test();
    solution.solute();
    return 0;
}
