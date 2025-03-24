/*2024数据结构--数据智能 实验3 数组描述线性表 A  通讯录.cpp*/
#include<iostream>
using namespace std;



class PersonalData
{
private:
    bool strequal(const char* a, const char* b) const
    {
        int count = 0;
        while (true)
        {
            if (a[count]=='\0' && b[count] == '\0')
            {
                return true;
            }
            if (a[count]!= b[count])
            {
                return false;
            }
            count++;
        }
    };
    void strcpy(char* a, const char* b)
    {
        int count = 0;
        while (true)
        {
            a[count] = b[count];
            if (b[count] =='\0')
            {
                return;
            }
        count++;
        }
    }



public:
    
    char name[20];
    char telenum[20];
    char classnum[10];
    int house;
    bool operator==(const PersonalData& compared) const;
    PersonalData(const PersonalData& copyed);
    PersonalData(int mark);
    PersonalData() {};
    PersonalData(const char* name) { strcpy(this->name, name);strcpy(this->classnum, "\0"); strcpy(this->telenum, "\0"); this->house = 0; };
    void edit();
    int getHouse() { return this->house; };
    bool checkClassnum(const char* target) { return this->strequal(this->classnum, target); };
    void disp() { cout << name << endl; }
};

bool PersonalData::operator==(const PersonalData& compared) const
{
    return this->strequal(this->name, compared.name);
}

PersonalData::PersonalData(const PersonalData& copyed)
{
    this->strcpy(this->name, copyed.name);
    this->strcpy(this->classnum, copyed.classnum);
    this->strcpy(this->telenum, copyed.telenum);
    this->house = copyed.house;
}

PersonalData::PersonalData(int mark)
{
    cin >> this->name;
    cin >> this->telenum;
    cin >> this->classnum;
    cin >> this->house;
}

void PersonalData::edit()
{
    int operation;
    cin >> operation;
    if (operation == 1)
    {
        char tele[20];
        cin >> tele;
        this->strcpy(this->telenum, tele);
    }
    if (operation == 2)
    {
        char clas[10];
        cin >> clas;
        this->strcpy(this->classnum, clas);
    }
    if (operation == 3)
    {
        int new_house;
        cin >> new_house;
        this->house = new_house;
    }
}

template<class T>
class arraylist
{
private:
    T* datas;
    int count;
    void copy(T* copyed, T* to);

public:
    T& operator[](const unsigned int subscript) { return datas[subscript]; };
    int find_first(const T& target);
    void push_back(const T& element);
    void erase(const T& target);
    bool is_in(const T& target);
    int size() { return count; };
    arraylist();
    ~arraylist() { delete[] datas; };
};

template<class T>
void arraylist<T>::copy(T* copyed, T* to)
{
    for (size_t i = 0; i < count; i++)
    {
        to[i] = copyed[i];
    }
}

template<class T>
void arraylist<T>::push_back(const T& element)
{
    T* new_datas = new T[count + 1];
    copy(datas, new_datas);
    new_datas[count] = element;
    count++;
    delete[] datas;
    datas = new_datas;
}

template<class T>
int arraylist<T>::find_first(const T& target)
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
bool arraylist<T>::is_in(const T& target)
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
    arraylist<PersonalData> data;

    for (size_t i = 0; i < n; i++)
    {
        cin >> operation;
        if (operation == 0)
        {
            PersonalData newdata(1);
            data.push_back(newdata);
        }

        if (operation == 1)
        {
            char name[20];
            cin >> name;
            data.erase(name);
        }
        if (operation == 2)
        {
            char name[20];
            cin >> name;
            data[data.find_first(name)].edit();
        }
        if (operation == 3)
        {
            char name[20];
            cin >> name;
            cout << data.is_in(name);
        }
        if (operation == 4)
        {
            int ans = 0;
            char target[10];
            cin >> target;
            for (size_t i = 0; i < data.size(); i++)
            {
                if (data[i].checkClassnum(target))
                {
                    ans = ans ^ data[i].getHouse();
                }
            }
            cout << ans;
        }
    }
    
}

void Solution::test()
{
    arraylist<int> list;
    list.push_back(1);
    list.push_back(1);
    list.push_back(1);
    for (int i = 0;i < list.size();i++)
    {
        cout << list[i];
    }
    list.erase(1);
    for (int i = 0;i < list.size();i++)
    {
        cout << list[i];
    }
}



int main()
{
    Solution ans;
    ans.solute();
    // ans.test();
    // system("pause");
}