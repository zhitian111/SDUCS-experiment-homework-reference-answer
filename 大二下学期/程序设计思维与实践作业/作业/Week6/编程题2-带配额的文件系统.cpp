#include <bits/stdc++.h>
#include <deque>
#include <pthread.h>
using namespace std;

// size_t MAX_SIZE = ~(size_t)0;
size_t MAX_SIZE = 0;
class my_file;
class my_folder;

vector<string> my_split(const string& s, char delimiter)
{
  vector<string> tokens;
  string token;
  for (char c : s)
  {
    if (c == delimiter)
    {
      if (!token.empty())
      {
        tokens.push_back(token);
        token.clear();
      }
    }
    else
    {
      token += c;
    }
  }
  if (!token.empty())
  {
    tokens.push_back(token);
  }
  return tokens;
}

class my_file
{
public:
  string name;
  size_t size;
  my_folder* parent;
  my_file(string name, size_t size, my_folder* parent);
  ~my_file();
};

class my_folder
{
public:
  map<string, my_file*> files;
  map<string, my_folder*> folders;
  my_folder* parent;
  string name;
  size_t LD;
  size_t RD;
  size_t used;
  size_t used_recursive;
  my_folder(string name, my_folder* parent);
  ~my_folder();
  bool set_quota(size_t LD, size_t RD);
};

my_file::my_file(string name, size_t size, my_folder* parent)
    : name(name), size(size), parent(parent)
{
  if (parent != nullptr)
  {
    parent->files[name] = this;
    parent->used += size;
  }
  auto tem = parent;
  while (tem != nullptr)
  {
    tem->used_recursive += size;
    tem = tem->parent;
  }
}

my_folder::my_folder(string name, my_folder* parent)
    : name(name), parent(parent), LD(MAX_SIZE), RD(MAX_SIZE), used(0),
      used_recursive(0)
{
  if (parent != nullptr)
  {
    parent->folders[name] = this;
  }
}

my_file::~my_file()
{
  if (parent != nullptr)
  {
    parent->files.erase(name);
    parent->used -= size;
  }
  while (parent != nullptr)
  {
    parent->used_recursive -= size;
    parent = parent->parent;
  }
}
my_folder::~my_folder()
{
  if (parent != nullptr)
  {
    parent->folders.erase(name);
  }
  // for (auto&& folder : folders)
  // {
  //   delete folder.second;
  // }
}

// bool my_folder::set_quota(size_t LD, size_t RD)
// {
//   if ((LD < used || RD < used_recursive) && LD != MAX_SIZE && RD != MAX_SIZE)
//   {
//     return false;
//   }
//   if (LD != MAX_SIZE && used > LD)
//   {
//     return false;
//   }
//   if (RD != MAX_SIZE && used_recursive > RD)
//   {
//     return false;
//   }
//   else
//   {
//     this->LD = LD;
//     this->RD = RD;
//     return true;
//   }
// }
bool my_folder::set_quota(size_t LD, size_t RD)
{
  if ((LD != MAX_SIZE && used > LD) || (RD != MAX_SIZE && used_recursive > RD))
  {
    return false;
  }
  this->LD = LD;
  this->RD = RD;
  return true;
}
my_folder root("root", nullptr);

void remove_file(string file_name, my_folder* current_folder)
{
  // vector<string> tokens = my_split(path, '/');
  // my_folder* current_folder = &root;
  // for (int i = 0; i < tokens.size() - 1; i++)
  // {
  //   if (current_folder->folders.count(tokens[i]) == 0)
  //   {
  //     return;
  //   }
  //   current_folder = current_folder->folders[tokens[i]];
  // }
  // if (current_folder->files.count(tokens[tokens.size() - 1]) != 0)
  // {
  //   my_file* file = current_folder->files[tokens[tokens.size() - 1]];
  //   current_folder->files.erase(tokens[tokens.size() - 1]);
  //   delete file;
  // }
  my_file* file = current_folder->files[file_name];
  current_folder->files.erase(file_name);
  delete file;
}

deque<my_file*> get_files_to_delete(my_folder* folder)
{
  deque<my_file*> files_to_delete;
  for (auto&& file : folder->files)
  {
    files_to_delete.push_back(file.second);
  }
  for (auto&& folder : folder->folders)
  {
    auto files = get_files_to_delete(folder.second);
    files_to_delete.insert(files_to_delete.end(), files.begin(), files.end());
  }
  return files_to_delete;
}

void remove_folder(string folder_name, my_folder* current_folder)
{
  // vector<string> tokens = my_split(path, '/');
  // my_folder* current_folder = &root;
  // for (int i = 0; i < tokens.size() - 1; i++)
  // {
  //   if (current_folder->folders.count(tokens[i]) == 0)
  //   {
  //     return;
  //   }
  //   current_folder = current_folder->folders[tokens[i]];
  // }
  // if (current_folder->folders.count(tokens[tokens.size() - 1]) != 0)
  // {
  //   my_folder* folder = current_folder->folders[tokens[tokens.size() - 1]];
  //   current_folder->folders.erase(tokens[tokens.size() - 1]);
  //   delete folder;
  // }
  auto files_to_delete =
      get_files_to_delete(current_folder->folders[folder_name]);
  for (auto&& file : files_to_delete)
  {
    delete file;
  }
  current_folder->folders.erase(folder_name);
}

my_folder* analyze_file(string path)
{
  auto tokens = my_split(path, '/');
  auto current_folder = &root;
  if (path == "/")
  {
    return current_folder;
  }
  for (int i = 0; i < int(tokens.size()) - 1; i++)
  {
    if (current_folder->folders.count(tokens[i]) == 0)
    {
      return nullptr;
    }
    current_folder = current_folder->folders[tokens[i]];
  }
  return current_folder;
}

void remove_operation(string path)
{
  auto tokens = my_split(path, '/');
  auto current_folder = analyze_file(path);
  if (current_folder == nullptr)
  {
    return;
  }
  if (current_folder->files.count(tokens[tokens.size() - 1]) != 0)
  {
    remove_file(tokens[tokens.size() - 1], current_folder);
  }
  else if (current_folder->folders.count(tokens[tokens.size() - 1]) != 0)
  {
    remove_folder(tokens[tokens.size() - 1], current_folder);
  }
}

bool is_file(string path)
{
  auto tokens = my_split(path, '/');
  auto current_folder = analyze_file(path);
  if (current_folder == nullptr)
  {
    return false;
  }
  if (current_folder->files.count(tokens[tokens.size() - 1]) != 0)
  {
    return true;
  }
  return false;
}

bool add_file(string path, size_t size)
{
  auto tokens = my_split(path, '/');
  auto current_folder = &root;
  bool is_exist = is_file(path);
  for (int i = 0; i < tokens.size() - 1; i++)
  {
    if (current_folder->files.count(tokens[i]) != 0)
    {
      return false;
    }
    if (is_exist &&
        current_folder->used_recursive + size > current_folder->RD &&
        current_folder->RD != MAX_SIZE)
    {
      return false;
    }
    if (current_folder->folders.count(tokens[i]) == 0)
    {
      my_folder* new_folder = new my_folder(tokens[i], current_folder);
      current_folder->folders[tokens[i]] = new_folder;
    }
    current_folder = current_folder->folders[tokens[i]];
  }
  if (current_folder->folders.count(tokens[tokens.size() - 1]) != 0)
  {
    return false;
  }
  if (current_folder->files.count(tokens[tokens.size() - 1]) != 0)
  {
    auto file = current_folder->files[tokens[tokens.size() - 1]];
    if (current_folder->used + size - file->size > current_folder->LD &&
        current_folder->LD != MAX_SIZE)
    {
      return false;
    }
    if (current_folder->used_recursive + size - file->size >
            current_folder->RD &&
        current_folder->RD != MAX_SIZE)
    {
      return false;
    }
    auto tem = file->parent;
    while (tem != nullptr)
    {
      if (tem->used_recursive + size - file->size > tem->RD &&
          tem->RD != MAX_SIZE)
      {
        return false;
      }
      tem = tem->parent;
    }
    delete file;
    current_folder->files.erase(tokens[tokens.size() - 1]);
    file = new my_file(tokens[tokens.size() - 1], size, current_folder);
    return true;
  }
  else
  {
    if (current_folder->used + size > current_folder->LD &&
        current_folder->LD != MAX_SIZE)
    {
      return false;
    }
    if (current_folder->used_recursive + size > current_folder->RD &&
        current_folder->RD != MAX_SIZE)
    {
      return false;
    }
    auto file = new my_file(tokens[tokens.size() - 1], size, current_folder);
    return true;
  }
  return false;
}

bool set_quota(string path, size_t LD, size_t RD)
{
  auto tokens = my_split(path, '/');
  // auto current_folder = analyze_file(path);
  auto current_folder = &root;

  if (path == "/")
  {
    return root.set_quota(LD, RD);
  }

  for (int i = 0; i < tokens.size() - 1; i++)
  {
    if (current_folder->folders.count(tokens[i]) == 0)
    {
      return false;
    }
    if (current_folder->files.count(tokens[i]) != 0)
    {
      return false;
    }
    current_folder = current_folder->folders[tokens[i]];
  }

  if (current_folder != nullptr)
  {
    if (current_folder->folders.count(tokens[tokens.size() - 1]) != 0)
    {
      my_folder* folder = current_folder->folders[tokens[tokens.size() - 1]];
      return folder->set_quota(LD, RD);
    }
  }
  return false;
}

void tree_all(my_folder* folder, size_t depth)
{
  if (folder == &root)
  {
    cout << "root" << endl;
  }

  for (auto&& file : folder->files)
  {
    cout << "└";
    for (int i = 0; i < depth; i++)
    {
      cout << "─";
    }
    cout << file.first << "\tsize: " << file.second->size << endl;
  }
  for (auto&& folder : folder->folders)
  {
    cout << "└";
    for (int i = 0; i < depth; i++)
    {
      cout << "─";
    }
    cout << folder.first
         << "\tused_recursive: " << folder.second->used_recursive << "/"
         << folder.second->RD << "\tused: " << folder.second->used << "/"
         << folder.second->LD << endl;
    tree_all(folder.second, depth + 1);
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
      if (add_file(path, size))
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
      remove_operation(path);
      cout << "Y" << endl;
    }
    if (op == 'Q')
    {
      string path;
      cin >> path;
      size_t LD, LR;
      cin >> LD >> LR;
      LD = LD == 0 ? MAX_SIZE : LD;
      LR = LR == 0 ? MAX_SIZE : LR;
      if (set_quota(path, LD, LR))
      {
        cout << "Y" << endl;
      }
      else
      {
        cout << "N" << endl;
      }
    }
    // tree_all(&root, 0);
  }
}

void test()
{
  string s = "/root/a/b/c/d";
  auto tokens = my_split(s, '/');
  for (auto i : tokens)
  {
    cout << i << endl;
  }
}

int main()
{
  solve();
  // test();
  return 0;
}
