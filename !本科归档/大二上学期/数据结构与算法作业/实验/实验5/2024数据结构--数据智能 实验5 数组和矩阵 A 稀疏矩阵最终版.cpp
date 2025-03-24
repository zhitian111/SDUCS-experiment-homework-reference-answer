/*2024数据结构--数据智能 实验5 数组和矩阵 A 稀疏矩阵最终版.cpp*/
#include <iostream>

using namespace std;

#define debug cout<<__LINE__<<": "<<__FUNCTION__<<'\n';


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
    void self_quick_sort() { if (count == 0 || count == 1||is_sorted) { return; }quick_sort(my_iterator<T>(datas, 0), my_iterator<T>(datas + count - 1, count - 1)); is_sorted = true; };
    bool getSorted() const { return is_sorted; };
    void erase_the_same();
    arraylist();
    ~arraylist() { delete[] datas; };
    arraylist(const arraylist<T>& other);
    void operator=(const arraylist<T>& other);
    arraylist(arraylist<T>&& other);
    void reset_sorted(bool is_sorted) { this->is_sorted = is_sorted; };
    void print() const;
    void operator+=(const arraylist<T>& other);
    void operator*=(const arraylist<T>& other);
};

template<class T>
void arraylist<T>::print() const
{
    for (size_t i = 0; i < count; i++)
    {
        cout << datas[i] << " ";
        cout << '\n';
    }
}

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
arraylist<T>::arraylist(arraylist<T>&& other)
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
    if (datas == nullptr)
    {
        capacity = 512;
        datas = new T[capacity];
    }
    if (count + 1 > capacity)
    {
        double_capacity();
    }
    datas[count] = element;
    // is_sorted = false;
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
    capacity = 512;
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
    capacity = 512;
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
    void operator=(const point& other)
    {
        this->row = other.row;
        this->col = other.col;
        this->value = other.value;
    }
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

ostream& operator<<(ostream& os, const point& p)
{
    os << "(" << p.row << "," << p.col << "," << p.value << ")";
    return os;
}

arraylist<point> operator+(arraylist<point>& a, const arraylist<point>& b)
{
    arraylist<point> c;
    c.clear();
    if (a.size() == 0)
    {
        return b;
    }
    if (b.size() == 0)
    {
        return a;
    }
    a.self_quick_sort();
    
    for (size_t i = 0; i < b.size(); i++)
    {
        int index = a.find_first(b[i]);
        if (index != -1)
        {
            a[index].value += b[i].value;
        }
        else       
        {
            c.push_back(b[i]);
        }
    }
    for(size_t i = 0; i < a.size(); i++)
    {
        c.push_back(a[i]);
    }
    return c;
}

arraylist<point> operator*(arraylist<point>& a, const arraylist<point>& b)
{
    arraylist<point> c;
    c.clear();
    for (size_t i = 0; i < a.size(); i++)
    {
        arraylist<point> temp;
        for (size_t j = 0; j < b.size(); j++)
        {
            if (a[i].col == b[j].row)
            {
                temp.push_back(point{ a[i].row, b[j].col, a[i].value * b[j].value });
            }
        }
        c = c + temp;
    }
    c.print();
    return c;
}

template<>
void arraylist<point>::operator+=(const arraylist<point>& other)
{
    if (other.size() == 0)
    {
        return;
    }
    
    if (this->size() == 0)
    {
        for (size_t i = 0; i < other.size(); i++)
        {
            this->push_back(other[i]);
        }
        reset_sorted(true);
        return;
    }
    size_t point1 = 0, point2 = 0;
    arraylist<point> temp;
    while (point1 < this->count && point2 < other.count)
    {
        if (this->datas[point1].row < other.datas[point2].row)
        {
            temp.push_back(this->datas[point1]);
            point1++;
        }
        else if (this->datas[point1].row > other.datas[point2].row)
        {
            temp.push_back(other.datas[point2]);
            point2++;
        }
        else if (this->datas[point1].col < other.datas[point2].col)
        {
            temp.push_back(this->datas[point1]);
            point1++;
        }
        else if (this->datas[point1].col > other.datas[point2].col)
        {
            temp.push_back(other.datas[point2]);
            point2++;
        }
        else if (this->datas[point1].col == other.datas[point2].col && this->datas[point1].row == other.datas[point2].row)
        {
            if (this->datas[point1].value + other.datas[point2].value != 0)
            {
                temp.push_back(point{ this->datas[point1].row, this->datas[point1].col, this->datas[point1].value + other.datas[point2].value });
            }
            point1++;
            point2++;
        
        }

    }
    while (point1 < this->count)
    {
        temp.push_back(this->datas[point1]);
        point1++;
    }
    while (point2 < other.count)
    {
        temp.push_back(other.datas[point2]);
        point2++;
    }
    this->clear();
    for(size_t i = 0; i < temp.size(); i++)
    {
        this->push_back(temp[i]);
    }
    this->is_sorted = true;
}

template<>
void arraylist<point>::operator*=(const arraylist<point>& other)
{
    arraylist<point> c;
    for (size_t i = 0;i < this->size();i++)
    {
        arraylist<point> temp;
        for (size_t j = 0;j < other.size();j++)
        {
            if (this->datas[i].col == other[j].row)
            {
                temp.push_back(point{ this->datas[i].row, other[j].col, this->datas[i].value * other[j].value });
            }
            else if (this->datas[i].col < other[j].row)
            {
                break;
            }
            else if (this->datas[i].col > other[j].row)
            {
                continue;
            }
        }
        c+=temp;
    }
    // for (size_t i = 0; i < this->size(); i++)
    // {
    //     arraylist<point> temp;
    //     for (size_t j = 0; j < other.size(); j++)
    //     {
    //         if (datas[i].col == other[j].row)
    //         {
    //             temp.push_back(point{ datas[i].row, other[j].col, datas[i].value * other[j].value });
    //         }
    //     }
    //     c+=temp;
    // }
    this->clear();
    for(size_t i = 0; i < c.size(); i++)
    {
        this->push_back(c[i]);
    }
    this->is_sorted = true;
}

class SparseMatrix
{
private:
    arraylist<point> points;
    int row, col;
    int count;
public:
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
    arraylist<point>& getPoints() { return points; }
    void transpose();
    SparseMatrix(int row, int col);
    SparseMatrix(int row, int col, int count);
    void operator*=(SparseMatrix& b);
    void operator+=(SparseMatrix& a);
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

}

SparseMatrix::SparseMatrix(const SparseMatrix& other) :
    row(other.row), col(other.col), count(other.count), points(other.points)
{
    int tem;
    for (int i = 0;i < row;i++)
    {
        for (int j = 0;j < col;j++)
        {
            cin >> tem;
            if (tem != 0)
            {
                this->points.push_back({ i,j,tem });
                this->count++;
            }
        }
    }

}

void SparseMatrix::operator=(const SparseMatrix& other)
{
    this->row = other.row;
    this->col = other.col;
    this->count = other.count;
    this->points = other.points;
}
SparseMatrix::SparseMatrix(SparseMatrix&& other) :
    row(other.row), col(other.col), count(other.count), points(other.points)
{

}

SparseMatrix::SparseMatrix(SparseMatrix& other) :
    row(other.row), col(other.col), count(other.count), points(other.points)
{

}

SparseMatrix::SparseMatrix(int row, int col, int count) :
    row(row), col(col), count(count), points()
{

    for (int i = 0;i < count;i++)
    {
        int row, col, value;

        cin >> row >> col >> value;
        this->points.push_back({ row - 1,col - 1,value });
        this->count++;
    }
}

void SparseMatrix::operator+=(SparseMatrix& a)
{
    if (this->row!= a.getRow() || this->col!= a.getCol())
    {
        cout << -1 << '\n';
        this->points.clear();
        for (size_t i = 0; i < a.getPoints().size(); i++)
        {
            this->points.push_back(a.getPoints()[i]);
        }
        this->row = a.getRow();
        this->col = a.getCol();
        this->count = a.getCount();
    }
    else
    {
        this->points+=a.getPoints();
        this->count = this->points.size();
    }
}

void SparseMatrix::operator*=(SparseMatrix& b)
{
    if (this->col != b.getRow()||b.col == 0)
    {
        cout << -1 << '\n';
        this->points.clear();
        for (size_t i = 0; i < b.getPoints().size(); i++)
        {
            this->points.push_back(b.getPoints()[i]);
        }
        this->row = b.getRow();
        this->col = b.getCol();
        this->count = b.getCount();
    }
    else
    {
        this->points *= b.getPoints();
        this->count = this->points.size();
        this->col = b.getCol();
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
            if (value != 0)
            {
                this->count++;
                this->points.push_back({ i,j,value });
            }
        }
    }
    this->points.reset_sorted(true);
}

void SparseMatrix::print()
{
    cout << row << " " << col << '\n';
    this->points.self_quick_sort();
    for (int i = 0;i < row;i++)
    {
        for (int j = 0;j < col;j++)
        {
            int index = this->points.find_first(point{ i,j,0 });
            if (index != -1)
            {
                cout<<points[index].value<<" ";
            }
            else
            {
                cout << 0 << " ";
            }
        }
        cout << '\n';
    }
}

void SparseMatrix::transpose()
{
    for (size_t i = 0; i < count; i++)
    {
        my_swap(points[i].row, points[i].col);
    }
    my_swap(row, col);
    points.reset_sorted(false);
    points.self_quick_sort();
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
            if (value != 0)
            {
                this->count++;
                this->points.push_back({ i,j,value });
            }
        }
    }
    this->points.reset_sorted(true);
}


class Solution
{
public:
    void solute();
    void test()
    {
        arraylist<point> a;
        arraylist<point> b;
        a.push_back(point{ 1,1,0 });
        a.push_back(point{ 1,2,1 });
        a.push_back(point{ 2,1,0 });
        a.push_back(point{ 2,2,1 });
        b = a;
        a = a * b;
        for(size_t i = 0; i < a.size(); i++)
        {
            cout << a[i].row << " " << a[i].col << " " << a[i].value << '\n';
        }
    }

};

void Solution::solute()
{
    ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    int n;
    cin >> n;
    int operation;
    cin >> operation;
    int row, col;
    cin >> row >> col;
    SparseMatrix matrix(row, col);
    matrix.getPoints().reset_sorted(true);
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
            matrix1.getPoints().reset_sorted(true);
            matrix *= matrix1;
        }
        else if (operation == 3)
        {
            int row, col, count;
            cin >> row >> col >> count;
            SparseMatrix matrix1(row, col, count);
            matrix1.getPoints().reset_sorted(true);
            matrix += matrix1;
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
    solution.solute();
    return 0;
}