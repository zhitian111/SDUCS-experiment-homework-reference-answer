/*2024数据结构--数据智能 实验5 数组和矩阵 A 稀疏矩阵数组描述快速版.cpp*/
#include <iostream>

using namespace std;

#define debug cout<<__LINE__<<": "<<__FUNCTION__<<endl;


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
    void erase(int index);
    void clear();
    void double_capacity();
    int getCapacity() const{return capacity;};
    bool is_in(const T& target) const;
    int size() const { return count; };
    void self_quick_sort() { if (count == 0) { return; }quick_sort(my_iterator<T>(datas, 0), my_iterator<T>(datas + count - 1, count - 1)); is_sorted = true; };
    bool getSorted() const { return is_sorted; };
    void erase_the_same();
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
void arraylist<T>::erase_the_same()
{
    if (is_sorted == false)
    {
        self_quick_sort();
    }
    
    if (count <= 1)
    {
        return;
    }
    else
    {
        int i = 0;
        while (i<count-1)
        {
            if(datas[i] == datas[i+1])
            {
                this->erase(i);
            }
            i++;
        }
    }
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

    T* new_datas = new T[capacity];

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
void arraylist<T>::erase(int index)
{
    T* new_datas = new T[capacity];

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

class SparseMatrix
{
private:
    arraylist<point> points;
    int row, col;
    int count;
public:
    int value[501][501];

    int getRow() const {
        return row;
    }
    int getCol() const {
        return col;
    }
    int getCount() const {
        return count;
    }
    int& getRow() { return row; }
    int& getCol() { return col; }
    int& getCount() { return count; }
    int* getValues() { return &value[0][0]; }
    arraylist<point>& getPoints() { return points; }
    void transpose();
    SparseMatrix(int row, int col);
    SparseMatrix(int row, int col, int count);
    SparseMatrix operator*(SparseMatrix& b);
    SparseMatrix operator+(SparseMatrix& a);
    void operator=(const SparseMatrix& other);
    SparseMatrix(const SparseMatrix& other);
    SparseMatrix(SparseMatrix&& other);
    SparseMatrix(SparseMatrix& other);
    
    SparseMatrix();
    void reset();
    void print();
};

SparseMatrix::SparseMatrix()
{
    row = 0;
    col = 0;
    count = 0;
    
    points.clear();
    for (int i = 0;i < 501;i++)
    {
        for (int j = 0;j < 501;j++)
        {
            value[i][j] = 0;
        }
    }
}

SparseMatrix::SparseMatrix(const SparseMatrix& other) :
    row(other.row), col(other.col), count(other.count), points(other.points)
{
    for (int i = 0;i < row;i++)
    {
        for (int j = 0;j < col;j++)
        {
            value[i][j] = other.value[i][j];
        }
    }

}

void SparseMatrix::operator=(const SparseMatrix& other)
{
    this->row = other.row;
    this->col = other.col;
    this->count = other.count;
    this->points = other.points;
    for (int i = 0;i < row;i++)
    {
        for (int j = 0;j < col;j++)
        {
            value[i][j] = other.value[i][j];
        }
    }
}

SparseMatrix::SparseMatrix(SparseMatrix&& other) :
    row(other.row), col(other.col), count(other.count), points(other.points)
{
    for (int i = 0;i < row;i++)
    {
        for (int j = 0;j < col;j++)
        {
            value[i][j] = other.value[i][j];
        }
    }

}

SparseMatrix::SparseMatrix(SparseMatrix& other) :
    row(other.row), col(other.col), count(other.count), points(other.points)
{
    for (int i = 0;i < row;i++)
    {
        for (int j = 0;j < col;j++)
        {
            value[i][j] = other.value[i][j];
        }
    }
}

SparseMatrix::SparseMatrix(int row, int col, int count) :
    row(row), col(col), count(count), points()
{
    for (int i = 0;i < row;i++)
    {
        for (int j = 0;j < col;j++)
        {
            value[i][j] = 0;
        }
    }
    for (int i = 0;i < count;i++)
    {
        int row, col, value;
        cin >> row >> col >> value;
        this->value[row][col] = value;
        this->points.push_back({ row,col });
        this->count++;
    }
}

SparseMatrix SparseMatrix::operator+(SparseMatrix& a)
{
    if (this->row!= a.getRow() || this->col!= a.getCol())
    {
        cout << -1 << endl;
        SparseMatrix c(a);
        return c;
    }
    else
    {
        SparseMatrix c;
        for (int i = 0;i < a.getCount();i++)
        {
            c.value[a.getPoints()[i].row][a.getPoints()[i].col] += a.value[a.getPoints()[i].row][a.getPoints()[i].col];
            c.getPoints().push_back(a.getPoints()[i]);
        }
        for (int i = 0; i < this->count; i++)
        {
            c.value[this->points[i].row][this->points[i].col] += this->value[this->points[i].row][this->points[i].col];
            this->points.push_back(this->points[i]);
        }
        c.getRow() = a.getRow();
        c.getCol() = a.getCol();
        c.getPoints().erase_the_same();
        c.getCount() = c.getPoints().size();
        return c;
    }
}

SparseMatrix SparseMatrix::operator*(SparseMatrix& b)
{
    if (this->col != b.getRow())
    {
        SparseMatrix c(b);
        return c;
    }
    else
    {
        
        SparseMatrix c;
        c.getRow() = this->getRow();
        c.getCol() = b.getCol();
        for (int i = 0;i < this->count;i++)
        {
            for (int j = 0;j < b.getCol();j++)
            {
                c.value[this->points[i].row][j] += this->value[this->points[i].row][this->points[i].col] * b.value[this->points[i].col][j];
                if (b.value[this->points[i].col][j] != 0)
                {
                    c.getPoints().push_back({ this->points[i].row,j });
                }
            }
        }
        c.getPoints().erase_the_same();
        c.getCount() = c.getPoints().size();
        return c;
    }
}

SparseMatrix::SparseMatrix(int row, int col)
{
    this->row = row;
    this->col = col;
    this->count = 0;
    int value;
    for (int i = 0;i < row;i++)
    {
        for (int j = 0;j < col;j++)
        {
            cin >> value;
            this->value[i][j] = value;
            if (value != 0)
            {
                this->count++;
                this->points.push_back({ i,j });
            }
        }
    }
}

void SparseMatrix::print()
{
    cout << row << " " << col << endl;
    
    for (int i = 0;i < row;i++)
    {
        for (int j = 0;j < col;j++)
        {
            cout << value[i][j] << " ";
        }
        
        cout << endl;
    }
}

void SparseMatrix::transpose()
{
    for (size_t i = 0; i < count; i++)
    {
        my_swap(value[points[i].row][points[i].col], value[points[i].col][points[i].row]);
        my_swap(points[i].row, points[i].col);
    }
    my_swap(row, col);
}


void SparseMatrix::reset()
{
    this->count = 0;
    this->points.clear();
    int row, col;
    cin >> row >> col;
    this->row = row;
    this->col = col;
    int value;
    for (int i = 0;i < row;i++)
    {
        for (int j = 0;j < col;j++)
        {
            cin >> value;
            this->value[i][j] = value;
            if (value != 0)
            {
                this->count++;
                this->points.push_back({ i,j });
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

    int n;
    cin >> n;
    int operation;
    cin >> operation;
    int row, col;
    cin >> row >> col;
    SparseMatrix matrix(row, col);
    matrix.print();
    SparseMatrix matrix1(matrix);
    matrix1.transpose();
    matrix1.print();
    (matrix * matrix).print();

}

int main()
{
    try {
        Solution solution;
        solution.solute();
        // solution.test();
    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}