#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

class Folder;
class File;
size_t MAX_SIZE = ~(size_t)0;

class Folder{      //文件夹类
public:
    string path;    //文件路径
    string name;    //文件名
    Folder* parent;    //父文件夹
    size_t used;       //已使用空间
    size_t used_recursion;    //已使用空间（递归）
    vector<File*> files;    //文件列表
    vector<Folder*> folders;    //文件夹列表
    size_t quota_l;      //配额LD大小
    size_t quota_r;      //配额RD大小
    Folder(string path, string name, Folder* parent) :
        path(path), name(name), parent(parent), used(0), used_recursion(0), quota_l(MAX_SIZE), quota_r(MAX_SIZE)
    {
        if (parent!= nullptr)
        {
            parent->folders.push_back(this);            
        }
    }
};

class File {    //文件类
public:
    string path;    //文件路径
    string name;    //文件名
    Folder* parent;    //父文件夹
    size_t size;       //文件大小
};



Folder root("/", "root", nullptr);
map<string, Folder*> folder_map;
map<string, File*> file_map;

bool is_valid_format(string path)
{
    if (path[0] != '/')
    {
        return false;
    }

    if (path[path.size() - 1] == '/')
    {
        return false;
    }

    if (path.find("//") != string::npos)
    {
        return false;
    }
    return true;
}

bool is_file_in_path(string path)
{
    if (path == "/")
    {
        return false;
    }
    string file_name = path.substr(path.rfind('/') + 1);    // 解析文件名
    path = path.substr(0, path.rfind('/'));                 // 解析路径
    cout << "path: " << path << endl;
    cout << "file_name: " << file_name << endl;
    auto left = path.begin() + 1;
    auto right = find(left, path.end(), '/');

    if (path == "/" || path == "")
    {
        return false;
    }

    Folder* current = &root;
    while (true)
    {
        string name = string(left, right);
        cout << name << endl;

        for (auto& file : current->files)
        {
            if (file->name == name)
            {
                return true;
            }
        }
        bool mark = false;
        for (auto& dir : current->folders)
        {
            if (dir->name == name)
            {
                current = dir;
                mark = false;
                break;
            }
        }
        if (!mark)
        {
            return false;
        }

        left = right + 1;
        right = find(left, path.end(), '/');
    }

    return false;
}
bool is_valid_path(string path)
{
    if (!is_valid_format(path))
    {
        return false;
    }
    if (!is_file_in_path(path))
    {
        return false;
    }

    return true;
}

bool is_exits_file(string path)
{
    if (!is_valid_path(path))
    {
        return false;
    }

    if (path == "/")
    {
        return false;
    }
    string file_name = path.substr(path.rfind('/') + 1);    // 解析文件名
    path = path.substr(0, path.rfind('/'));                 // 解析路径
    auto left = path.begin() + 1;
    auto right = find(left, path.end(), '/');
    Folder* current = &root;
    while (true)
    {

        string name = string(left, right);

        for (auto& file : current->files)
        {
            if (file->name == name)
            {
                return false;
            }
        }
        for (auto& dir : current->folders)
        {
            if (dir->name == name)
            {
                current = dir;
                break;
            }
        }
        if (right == path.end())
        {
            break;
        }
        
        left = right + 1;
        right = find(left, path.end(), '/');
    }
    for (auto& file : current->files)
    {
        if (file->name == file_name)
        {
            return true;
        }
    }

    return false;
}

bool create_folder(string path)
{
    // if (!is_valid_path(path))
    // {
    //     return false;
    // }
    // cout << "path: " << path << endl;
    auto left = path.begin() + 1;
    auto right = find(left, path.end(), '/');
    string name;

    // cout << string(left, right) << endl;
    
    Folder* current = &root;
    while (true)
    {

        name = string(left, right);
        // cout << "name: " << name << endl;
        // cout << "current: " << current->path << endl;
        bool mark = false;
        for (auto& dir : current->folders)
        {
            if (dir->name == name)
            {
                current = dir;
                mark = true;
                break;
            }
            
        }
        if (!mark)
        {
            break;    
        }

        if (right == path.end())
        {
            break;
        }

        left = right + 1;
        right = find(left, path.end(), '/');

    }
    while (true)
    {
        name = string(left, right);
        cout << "name: " << name << endl;
        cout << "parent: " << current->name << endl;
        Folder* new_folder = new Folder(current->path + "/" + name, name, current);

        current->folders.push_back(new_folder);
        folder_map[new_folder->path] = new_folder;

        if (right == path.end())
        {
            break;
        }
        current = new_folder;

        left = right + 1;
        right = find(left, path.end(), '/');
    }
    
}

bool create_file(string path, size_t size)
{

}

bool remove_file(string path)
{

}

bool remove_folder(string path)
{

}

bool set_quota(string path, size_t LD, size_t RD)
{

}

void tree_all(Folder* folder)
{
    for (auto& file : folder->files)
    {
        cout << file->path << " " << file->name << " " << file->size << endl;
    }
    for (auto& subfolder : folder->folders)
    {
        cout << subfolder->path << " " << subfolder->name << endl;
        tree_all(subfolder);
    }
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char op;
        cin >> op;
        if (op == 'C')
        {
            string path;
            size_t size;
            cin >> path >> size;
            
            if (create_file(path, size))
            {
                cout << "Y" << endl;
            }
            else
            {
                cout << "N" << endl;
            }

        }
        if (op == 'R')
        {
            string path;
            cin >> path;
        }
        if (op == 'Q')
        {
            string path;
            cin >> path;
            size_t LD, LR;
            cin >> LD >> LR;
        }

    }
}

void test()
{
    create_folder("/a");
    create_folder("/a/b/d");
    create_folder("/a/b/e");
    tree_all(&root);
}

int main()
{
    // solve();
    test();
    return 0;
}