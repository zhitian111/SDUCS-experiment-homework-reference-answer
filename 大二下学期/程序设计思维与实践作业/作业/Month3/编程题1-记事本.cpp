
// debug de吐了，放弃了直接抄了
#include<bits/stdc++.h>
using namespace std;

int r[999999], rs[999999];//记录每行的字符个数（包含'\n'）
string s = "\n", temp, paste, paste0;//paste：选中的字符串；paste0：粘贴板
int pos, nowr, nowl, maxr = 1, pos0;
//当前处于的位置，当前处于第几行，当前处于第几列，一共有多少-1行了，记录点
bool state = false, choose = false;//是否开启粘滞功能，是否处于选中状态

void upd() {	//更新每行的字符个数数组r
	int cnt = 1, index = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != '\n') {
			cnt++;
		}
		else {
			r[index] = cnt;
			if (index == 0) {
				rs[index] = r[index];
			}
			else {
				rs[index] = rs[index - 1] + cnt;
			}
			if (pos < r[0]) {
				nowr = 0;
				nowl = pos;
			}
			else if (index > 0 && pos < rs[index] && pos >= rs[index - 1]) {
				nowr = index;
				nowl = pos - rs[index - 1];
				if (rs[nowr] - 1 >= s.size()) {
					while (1);
				}
			}
			index++;
			cnt = 1;
		}
	}
	maxr = index - 1;
}

void move() {
	choose = false;
	int prepos = pos;
	if (temp == "Home") {
		pos -= nowl;
	}
	if (temp == "End") {
		//pos = rs[nowr] - 1;
		pos = s.find('\n', pos);
	}
	if (temp == "Up") {
		if (nowr != 0) {
			if (r[nowr - 1] <= nowl + 1) {
				pos -= nowl + 1;
			}
			else {
				pos -= r[nowr - 1];
			}
		}
	}
	if (temp == "Down") {
		if (nowr < maxr) {
			if (r[nowr + 1] <= nowl + 1) {
				pos = rs[nowr + 1] - 1;
			}
			else {
				pos += r[nowr];
			}
		}
	}
	if (temp == "Left") {
		if (pos > 0) {
			pos--;
		}
	}
	if (temp == "Right") {
		if (pos < s.size() - 1) {
			pos++;
		}
	}
}

void input() {
	if (temp == "Paste" && paste0.size() == 0) {
		return;
	}
	if (choose == true) {
		s.erase(min(pos, pos0), abs(pos - pos0));
		pos = min(pos, pos0);
		choose = false;
		upd();
	}
	if (temp == "Char") {
		//cout << "@@@@" << pos << "," << s.size() << endl;
		char t;
		cin >> t;
		s.insert(pos++, 1, t);
	}
	if (temp == "Enter") {
		s.insert(pos++, 1, '\n');
	}
	if (temp == "Space") {
		s.insert(pos++, 1, ' ');
	}
	if (temp == "Paste") {
		if (paste0.size() != 0) {
			s.insert(pos, paste0);
			pos += paste0.size();
		}
	}
}

void del() {
	if (choose == true) {
		s.erase(min(pos, pos0), abs(pos - pos0));
		if (pos > pos0) {
			pos = pos0;
		}
		choose = false;
	}
	else {
		if (temp == "Del" && pos < s.size() - 1) {
			s.erase(s.begin() + pos);
		}
		if (temp == "Backspace" && pos > 0) {
			s.erase(s.begin() + pos - 1);
			pos--;
		}
	}
}

void shift() {
	if (state == true) {
		if (pos != pos0) {
			choose = true;
			paste = s.substr(min(pos, pos0), abs(pos - pos0));
		}
		state = false;
	}
	else {
		if (choose == false) {
			pos0 = pos;
		}
		else {
			choose = false;
		}
		state = true;
	}
}

int find() {
	string word;
	int cnt = 0, idx = 0;
	cin >> word;
	if (choose == true) {
		while ((idx = paste.find(word, idx)) != paste.npos) {
			idx++;
			cnt++;
		}
	}
	else {
		while ((idx = s.find(word, idx)) != s.npos) {
			idx++;
			cnt++;
		}
	}
	return cnt;
}

int count() {
	int cnt = 0;
	if (choose == true) {
		for (int i = 0; i < paste.size(); i++) {
			if (paste[i] != '\n' && paste[i] != ' ') {
				cnt++;
			}
		}
	}
	else {
		for (int i = 0; i < s.size(); i++) {
			if (s[i] != '\n' && s[i] != ' ') {
				cnt++;
			}
		}
	}
	return cnt;
}

void copy() {
	if (choose == true) {
		paste0 = paste;
	}
	else if (r[nowr] > 1) {
		paste0 = s.substr(pos - nowl, r[nowr] - 1);
	}
}

void print() {
	cout << s;
	//for (int i = 0; i <= maxr; i++) {
	//	cout << r[i] << "*" << rs[i] << endl;
	//}
	//cout << nowr << "**" << nowl << endl;
}

int main()
{
	//freopen("Text.txt", "r", stdin);
	int n;
	string op;
	cin >> n;
	while (n--) {
		//cout << "%%%%%" << 4800 - n << endl;
		cin >> op;
		if (op == "MOVE") {
			cin >> temp;
			move();
		}
		if (op == "INSERT") {
			cin >> temp;
			input();
		}
		if (op == "REMOVE") {
			cin >> temp;
			del();
		}
		if (op == "SHIFT") {
			shift();
		}
		if (op == "FIND") {
			cout << find() << endl;
		}
		if (op == "COUNT") {
			cout << count() << endl;
		}
		if (op == "COPY") {
			copy();
		}
		if (op == "PRINT") {
			print();
		}
		upd();
	}
	return 0;
}

// #include <bits/stdc++.h>
// using namespace std;


// class text_editor
// {
// private:
//     vector<string>lines_buffer;
//     size_t cursor_row, cursor_col;
//     string copy_buffer;
//     size_t select_start_row, select_start_col, select_end_row, select_end_col;
//     int mode;// normal == 0, select == 1, selected = 2
// public:
//     text_editor()
//     {
//         string tem;
//         lines_buffer.emplace_back(tem);
//         cursor_col = 0;
//         cursor_row = 0;
//         select_start_col = 0;
//         select_start_row = 0;
//         select_end_col = 0;
//         select_end_row = 0;
//         mode = 0;
//     }

//     void insert(char c)
//     {
//         string tem;
//         if (mode == 0)
//         {
//             if (c == '\n')
//             {
//                 if (cursor_col == lines_buffer[cursor_row].size())
//                 {
//                     auto& line_buf = lines_buffer[cursor_row];
//                     line_buf.insert(line_buf.begin() + cursor_col, c);
//                     lines_buffer.insert(lines_buffer.begin() + cursor_row + 1, tem);
//                     cursor_col = 0;
//                     cursor_row++;
//                 }
//                 else
//                 {
//                     auto line_buf = lines_buffer[cursor_row];
//                     lines_buffer.insert(lines_buffer.begin() + cursor_row + 1, line_buf.substr(cursor_col));
//                     lines_buffer[cursor_row] = line_buf.substr(0, cursor_col);
//                     if (lines_buffer[cursor_row].back() != '\n')
//                     {
//                         lines_buffer[cursor_row].push_back('\n');
//                     }
                    
//                     cursor_col = 0;
//                     cursor_row++;
//                 }
//             }
//             else
//             {
//                 auto& line_buf = lines_buffer[cursor_row];
//                 line_buf.insert(line_buf.begin() + cursor_col, c);
//                 cursor_col++;
//             }
//         }
//         if (mode == 1 || mode == 2)
//         {
//             size_t start_row = 0;
//             size_t start_col = 0;
//             size_t end_row = 0;
//             size_t end_col = 0;


//             if (select_start_row < select_end_row)
//             {
//                 start_row = select_start_row;
//                 start_col = select_start_col;
//                 end_row = select_end_row;
//                 end_col = select_end_col;
//             }
//             else if (select_start_row > select_end_row)
//             {
//                 start_row = select_end_row;
//                 start_col = select_end_col;
//                 end_row = select_start_row;
//                 end_col = select_start_col;
//             }
//             else if (select_start_col < select_end_col)
//             {
//                 start_row = select_start_row;
//                 start_col = select_start_col;
//                 end_row = select_end_row;
//                 end_col = select_end_col;
//             }
//             else if (select_start_col > select_end_col)
//             {
//                 start_row = select_end_row;
//                 start_col = select_end_col;
//                 end_row = select_start_row;
//                 end_col = select_start_col;
//             }
//             if (start_row == end_row)
//             {
//                 if (start_col == end_col)
//                 {
//                     return;
//                 }
//                 auto tem = lines_buffer[start_row].substr(0, start_col) + lines_buffer[start_row].substr(end_col);
//                 lines_buffer[start_row] = tem;
//             }
//             else if (end_row - start_row > 1)
//             {
//                 lines_buffer[start_row] = lines_buffer[start_row].substr(0, start_col) + lines_buffer[end_row].substr(end_col);
//                 for (size_t i = start_row + 1; i <= end_row; i++)
//                 {
//                     lines_buffer.erase(lines_buffer.begin() + i);
//                 }
//             }
//             else if (end_row - start_row == 1)
//             {
//                 auto front = lines_buffer[start_row].substr(0, start_col);
//                 auto back = lines_buffer[end_row].substr(end_col);
//                 lines_buffer[start_row] = front + back;
//                 lines_buffer.erase(lines_buffer.begin() + end_row);
//             }
//             cursor_col = start_col;
//             cursor_row = start_row;
//             mode = 0;
//             insert(c);
//         }
//     }
//     void backspace()
//     {
//         if (mode == 1 || mode == 2)
//         {
//             insert(128);
//             mode = 0;
//             backspace();
//         }
//         else if (mode == 0)
//         {
//             auto& line_buf = lines_buffer[cursor_row];
//             if (cursor_col > 0)
//             {
//                 line_buf.erase(line_buf.begin() + cursor_col - 1);
//                 cursor_col--;
//             }
//             else
//             {
//                 if (cursor_row > 0)
//                 {
//                     cursor_row--;
//                     auto& line_buf = lines_buffer[cursor_row];
//                     line_buf.erase(line_buf.begin() + line_buf.size() - 1);//清楚换行符
//                     cursor_col = line_buf.size();
//                     line_buf += lines_buffer[cursor_row + 1];
//                     lines_buffer.erase(lines_buffer.begin() + cursor_row + 1);
//                 }
//             }
//         }

//     }
//     void enter()
//     {
//         insert('\n');
//     }
//     void whitespaces()
//     {
//         insert(' ');
//     }
//     size_t count(bool white = false)
//     {
//         size_t count = 0;
//         if (mode == 0)
//         {
//             for (auto& line : lines_buffer)
//             {
//                 for (auto& c : line)
//                 {
//                     if (c == ' ' || c == '\n')
//                     {
//                         if (white)
//                         {
//                             count++;
//                         }
//                     }
//                     else
//                     {
//                         count++;
//                     }
//                 }
//             }
//         }
//         if (mode == 2 || mode == 1)
//         {
//             size_t start_row = 0;
//             size_t start_col = 0;
//             size_t end_row = 0;
//             size_t end_col = 0;
//             if (select_start_row < select_end_row)
//             {
//                 start_row = select_start_row;
//                 start_col = select_start_col;
//                 end_row = select_end_row;
//                 end_col = select_end_col;
//             }
//             else if (select_start_row > select_end_row)
//             {
//                 start_row = select_end_row;
//                 start_col = select_end_col;
//                 end_row = select_start_row;
//                 end_col = select_start_col;
//             }
//             else if (select_start_col < select_end_col)
//             {
//                 start_row = select_start_row;
//                 start_col = select_start_col;
//                 end_row = select_end_row;
//                 end_col = select_end_col;
//             }
//             else if (select_start_col > select_end_col)
//             {
//                 start_row = select_end_row;
//                 start_col = select_end_col;
//                 end_row = select_start_row;
//                 end_col = select_start_col;
//             }
//             if (start_row == end_row)
//             {
//                 for (size_t i = start_col; i < end_col; i++)
//                 {
//                     auto c = lines_buffer[start_row][i];
//                     if (c == ' ' || c == '\n')
//                     {
//                         if (white)
//                         {
//                             count++;
//                         }
//                     }
//                     else
//                     {
//                         count++;
//                     }
//                 }
//             }
//             else
//             {
//                 for (size_t i = start_row; i <= end_row; i++)
//                 {
//                     if (i == start_row)
//                     {
//                         for (size_t j = start_col; j < lines_buffer[i].size(); j++)
//                         {
//                             auto c = lines_buffer[i][j];
//                             if (c == ' ' || c == '\n')
//                             {
//                                 if (white)
//                                 {
//                                     count++;
//                                 }
//                             }
//                             else
//                             {
//                                 count++;
//                             }
//                         }
//                     }
//                     else if (i == end_row)
//                     {
//                         for (size_t j = 0; j < end_col; j++)
//                         {
//                             auto c = lines_buffer[i][j];
//                             if (c == ' ' || c == '\n')
//                             {
//                                 if (white)
//                                 {
//                                     count++;
//                                 }
//                             }
//                             else
//                             {
//                                 count++;
//                             }
//                         }
//                     }
//                     else
//                     {
//                         for (size_t j = 0; j < lines_buffer[i].size(); j++)
//                         {
//                             auto c = lines_buffer[i][j];
//                             if (c == ' ' || c == '\n')
//                             {
//                                 if (white)
//                                 {
//                                     count++;
//                                 }
//                             }
//                             else
//                             {
//                                 count++;
//                             }
//                         }
//                     }

//                 }
//             }
//         }
//         return count;
//     }

//     void display()
//     {
//         if (mode == 1)
//         {
//             cout << "\033[34mmode: \nselect\033[0m" << endl;
//             cout << "\033[34mselect_start_row: " << select_start_row << " select_start_col: " << select_start_col << " select_end_row: " << select_end_row << " select_end_col: " << select_end_col << "\033[0m" << endl;
//         }
//         if (mode == 0)
//         {
//             cout << "\033[34mmode: \nnormal\033[0m" << endl;
//         }
//         if (mode == 2)
//         {
//             cout << "\033[34mmode: \nselected\033[0m" << endl;
//             cout << "\033[34mselect_start_row: " << select_start_row << " select_start_col: " << select_start_col << " select_end_row: " << select_end_row << " select_end_col: " << select_end_col << "\033[0m" << endl;
//         }
//         cout << "\033[35mcopy_buffer: \033[0m" << endl;
//         for (auto c : copy_buffer)
//         {
//             if (c == ' ')
//             {
//                 cout << "\033[7m" << c << "\033[0m";
//             }
//             else
//             {
//                 cout << c;
//             }
//         }
//         cout << endl;

//         cout << "\033[36mlines_buffer: \n\033[0m" << endl;

//         cout << "\033[32mcursor_row: " << cursor_row << " cursor_col: " << cursor_col << "\033[0m" << endl;
//         cout << "\033[33mchars_count: " << count() << "\033[0m" << endl;
//         size_t start_row = 0;
//         size_t start_col = 0;
//         size_t end_row = 0;
//         size_t end_col = 0;
//         if (mode == 2 || mode == 1)
//         {

//             if (select_start_row < select_end_row)
//             {
//                 start_row = select_start_row;
//                 start_col = select_start_col;
//                 end_row = select_end_row;
//                 end_col = select_end_col;
//             }
//             else if (select_start_row > select_end_row)
//             {
//                 start_row = select_end_row;
//                 start_col = select_end_col;
//                 end_row = select_start_row;
//                 end_col = select_start_col;
//             }
//             else if (select_start_col < select_end_col)
//             {
//                 start_row = select_start_row;
//                 start_col = select_start_col;
//                 end_row = select_end_row;
//                 end_col = select_end_col;
//             }
//             else if (select_start_col > select_end_col)
//             {
//                 start_row = select_end_row;
//                 start_col = select_end_col;
//                 end_row = select_start_row;
//                 end_col = select_start_col;
//             }
//         }
//         size_t col_count = 0;
//         for (size_t i = 0; i < lines_buffer.size(); i++)
//         {
//             col_count = max(col_count, lines_buffer[i].size());
//         }
//         for (size_t i = 0; i <= col_count; i++)
//         {
//             cout << "\033[36m" << i << " " << "\033[0m";
//         }
//         cout << endl;

//         for (size_t i = 0; i < lines_buffer.size(); i++)
//         {
//             cout << "\033[36m" << i + 1 << "\033[0m ";
//             for (size_t j = 0; j <= lines_buffer[i].size(); j++)
//             {
//                 if (mode == 1 || mode == 2)
//                 {
//                     if (i > start_row && i < end_row)
//                     {
//                         cout << "\033[7m";
//                     }
//                     if (i == start_row && j >= start_col)
//                     {
//                         cout << "\033[7m";
//                     }
//                     if (i == end_row && j <= end_col)
//                     {
//                         cout << "\033[7m";
//                     }
//                 }


//                 if (i == cursor_row && j == cursor_col)
//                 {
//                     cout << "\b|";
//                 }
//                 if (j == lines_buffer[i].size())
//                 {
//                     // cout << endl;
//                 }
//                 else
//                 {
//                     if (lines_buffer[i][j] == '\n')
//                     {
//                         cout << "\\n" << "\n";
//                     }

//                     if (lines_buffer[i][j] != '\n')
//                     {
//                         cout << lines_buffer[i][j];
//                         cout << " ";
//                         if (j >= 9)
//                         {
//                             cout << " ";
//                         }
//                     }
//                 }
//                 if (mode == 1 || mode == 2)
//                 {
//                     if (i > start_row && i < end_row)
//                     {
//                         cout << "\033[0m";
//                     }
//                     if (i == start_row && j >= start_col)
//                     {
//                         cout << "\033[0m";
//                     }
//                     if (i == end_row && j <= end_col)
//                     {
//                         cout << "\033[0m";
//                     }
//                 }
//             }
//         }
//         cout << endl;
//     }
//     void print()
//     {
//         for (auto& line : lines_buffer)
//         {
//             cout << line;
//         }
//         cout << endl;
//     }
//     void del()
//     {
//         if (mode == 1 || mode == 2)
//         {
//             insert(128);
//             mode = 0;
//             backspace();
//         }
//         else if (mode == 0)
//         {
//             auto& line_buf = lines_buffer[cursor_row];
//             if (line_buf.size() > 0 && line_buf[line_buf.size() - 1] == '\n')
//             {
//                 if (line_buf.size() > 1 && cursor_col < line_buf.size() - 1)
//                 {
//                     line_buf.erase(line_buf.begin() + cursor_col);
//                 }
//                 else if (line_buf.size() > cursor_col && line_buf[cursor_col] == '\n')
//                 {
//                     if (cursor_row < lines_buffer.size() - 1)
//                     {
//                         line_buf = line_buf + lines_buffer[cursor_row + 1];
//                         line_buf.erase(line_buf.begin() + cursor_col);
//                         lines_buffer.erase(lines_buffer.begin() + cursor_row + 1);
//                     }
//                 }
//                 else
//                 {
//                     line_buf = lines_buffer[cursor_row + 1];
//                 }
//             }
//             else if (line_buf.size() > 0 && line_buf[line_buf.size()] != '\n')
//             {
//                 if (cursor_col < line_buf.size())
//                 {
//                     line_buf.erase(line_buf.begin() + cursor_col);
//                 }
//                 else
//                 {
//                     if (cursor_row < lines_buffer.size() - 1)
//                     {
//                         line_buf = line_buf + lines_buffer[cursor_row + 1];
//                         lines_buffer.erase(lines_buffer.begin() + cursor_row + 1);
//                     }
//                 }
//             }
//         }
//     }

//     void copy()
//     {
//         if (mode == 1 || mode == 2)
//         {
//             size_t start_row = 0;
//             size_t start_col = 0;
//             size_t end_row = 0;
//             size_t end_col = 0;


//             if (select_start_row < select_end_row)
//             {
//                 start_row = select_start_row;
//                 start_col = select_start_col;
//                 end_row = select_end_row;
//                 end_col = select_end_col;
//             }
//             else if (select_start_row > select_end_row)
//             {
//                 start_row = select_end_row;
//                 start_col = select_end_col;
//                 end_row = select_start_row;
//                 end_col = select_start_col;
//             }
//             else if (select_start_col < select_end_col)
//             {
//                 start_row = select_start_row;
//                 start_col = select_start_col;
//                 end_row = select_end_row;
//                 end_col = select_end_col;
//             }
//             else if (select_start_col > select_end_col)
//             {
//                 start_row = select_end_row;
//                 start_col = select_end_col;
//                 end_row = select_start_row;
//                 end_col = select_start_col;
//             }
//             if (start_row == end_row && start_col == end_col)
//             {
//                 return;
//             }
//             copy_buffer.clear();
//             if (start_row == end_row)
//             {
//                 for (size_t i = start_col; i < end_col; i++)
//                 {
//                     copy_buffer += lines_buffer[start_row][i];
//                 }
//             }
//             else {
//                 for (size_t i = start_row; i <= end_row; i++)
//                 {
//                     if (i == start_row)
//                     {
//                         for (size_t j = start_col; j < lines_buffer[i].size(); j++)
//                         {
//                             copy_buffer += lines_buffer[i][j];
//                         }
//                     }
//                     else if (i == end_row)
//                     {
//                         for (size_t j = 0; j < end_col; j++)
//                         {
//                             copy_buffer += lines_buffer[i][j];
//                         }
//                     }
//                     else
//                     {
//                         for (size_t j = 0; j < lines_buffer[i].size(); j++)
//                         {
//                             copy_buffer += lines_buffer[i][j];
//                         }
//                     }
//                 }
//             }
//         }
//         if (mode == 0)
//         {
//             if (lines_buffer[cursor_row].size() > 0)
//             {
//                 if (lines_buffer[cursor_row].size() == 1)
//                 {
//                     if (lines_buffer[cursor_row][0] == '\n')
//                     {
//                         return;
//                     }
//                 }
//                 copy_buffer.clear();
//                 copy_buffer = lines_buffer[cursor_row];
//                 if (copy_buffer[copy_buffer.size() - 1] == '\n')
//                 {
//                     copy_buffer.erase(copy_buffer.size() - 1);
//                 }
//             }
//         }
//     }
//     void cursor_left()
//     {
//         switch (cursor_col)
//         {
//         case 0:
//             if (cursor_row > 0)
//             {
//                 cursor_row--;
//                 cursor_col = lines_buffer[cursor_row].size() - 1;
//             }
//             break;
//         default:
//             cursor_col--;
//             break;
//         }
//         if (mode == 1)
//         {
//             select_end_row = cursor_row;
//             select_end_col = cursor_col;
//         }
//         if (mode == 2)
//         {
//             mode = 0;
//         }
//     }
//     void cursor_right()
//     {
//         if (mode == 2)
//         {
//             mode = 0;
//         }
//         if (lines_buffer[cursor_row].size() == 0)
//         {
//             return;
//         }

//         if (lines_buffer[cursor_row][lines_buffer[cursor_row].size() - 1] == '\n')
//         {
//             if (cursor_col < lines_buffer[cursor_row].size() - 1 && lines_buffer[cursor_row].size() > 1)
//             {
//                 cursor_col++;
//             }
//             else if (cursor_col == lines_buffer[cursor_row].size() - 1 && lines_buffer[cursor_row].size() > 1)
//             {
//                 if (cursor_row < lines_buffer.size() - 1)
//                 {
//                     cursor_row++;
//                     cursor_col = 0;
//                 }
//             }
//             else if (lines_buffer[cursor_row].size() == 1)
//             {
//                 if (cursor_row < lines_buffer.size() - 1)
//                 {
//                     cursor_row++;
//                     cursor_col = 0;
//                 }
//             }
//         }
//         else
//         {
//             if (cursor_col < lines_buffer[cursor_row].size())
//             {
//                 cursor_col++;
//             }
//         }

//         if (mode == 1)
//         {
//             select_end_row = cursor_row;
//             select_end_col = cursor_col;
//         }

//     }
//     void cursor_up()
//     {
//         switch (cursor_row)
//         {
//         case 0:
//             break;
//         default:
//             cursor_row--;
//             if (cursor_col > lines_buffer[cursor_row].size())
//             {
//                 cursor_col = lines_buffer[cursor_row].size();

//             }
//             if (lines_buffer[cursor_row][cursor_col - 1] == '\n')
//             {
//                 cursor_col--;
//             }
//             break;
//         }
//         if (mode == 1)
//         {
//             select_end_row = cursor_row;
//             select_end_col = cursor_col;
//         }
//         if (mode == 2)
//         {
//             mode = 0;
//         }
//     }
//     void cursor_down()
//     {
//         if (cursor_row < lines_buffer.size() - 1)
//         {
//             cursor_row++;
//             if (cursor_col > lines_buffer[cursor_row].size())
//             {
//                 cursor_col = lines_buffer[cursor_row].size();
//             }
//             if (lines_buffer[cursor_row][cursor_col - 1] == '\n')
//             {
//                 cursor_col--;
//             }

//         }
//         if (mode == 1)
//         {
//             select_end_row = cursor_row;
//             select_end_col = cursor_col;
//         }
//         if (mode == 2)
//         {
//             mode = 0;
//         }
//     }
//     void home()
//     {
//         cursor_col = 0;
//         if (mode == 1)
//         {
//             select_end_row = cursor_row;
//             select_end_col = cursor_col;
//         }
//         if (mode == 2)
//         {
//             mode = 0;
//         }
//     }
//     void end()
//     {
//         cursor_col = lines_buffer[cursor_row].size();
//         if (lines_buffer[cursor_row][cursor_col - 1] == '\n')
//         {
//             cursor_col--;
//         }

//         if (mode == 1)
//         {
//             select_end_row = cursor_row;
//             select_end_col = cursor_col;
//         }
//         if (mode == 2)
//         {
//             mode = 0;
//         }
//     }
//     void paste()
//     {
//         for (auto c : copy_buffer)
//         {
//             insert(c);
//         }
//     }
//     void change_mode()
//     {
//         if (mode == 0)
//         {
//             change_to_select_mode();
//         }
//         else if (mode == 1)
//         {
//             change_to_selected_mode();
//         }
//         else if (mode == 2)
//         {
//             select_end_col = cursor_col;
//             select_end_row = cursor_row;
//             mode = 1;
//         }

//     }

//     void change_to_select_mode()
//     {
//         select_start_col = cursor_col;
//         select_start_row = cursor_row;
//         select_end_col = cursor_col;
//         select_end_row = cursor_row;
//         mode = 1;
//     }
//     void change_to_normal_mode()
//     {
//         mode = 0;
//     }
//     void change_to_selected_mode()
//     {
//         if (select_end_col == select_start_col && select_start_row == select_end_row)
//         {
//             mode = 0;
//             return;
//         }
//         mode = 2;
//     }
//     size_t find(string _s)
//     {
//         size_t count = 0;
//         if (mode == 0)
//         {
//             for (auto& line : lines_buffer)
//             {
//                 auto start = line.find(_s);
//                 while (start != string::npos)
//                 {
//                     count++;
//                     start = line.find(_s, start + 1);
//                 }
//             }
//         }
//         if (mode == 2 || mode == 1)
//         {
//             size_t start_row = 0;
//             size_t start_col = 0;
//             size_t end_row = 0;
//             size_t end_col = 0;
//             if (select_start_row < select_end_row)
//             {
//                 start_row = select_start_row;
//                 start_col = select_start_col;
//                 end_row = select_end_row;
//                 end_col = select_end_col;
//             }
//             else if (select_start_row > select_end_row)
//             {
//                 start_row = select_end_row;
//                 start_col = select_end_col;
//                 end_row = select_start_row;
//                 end_col = select_start_col;
//             }
//             else if (select_start_col < select_end_col)
//             {
//                 start_row = select_start_row;
//                 start_col = select_start_col;
//                 end_row = select_end_row;
//                 end_col = select_end_col;
//             }
//             else if (select_start_col > select_end_col)
//             {
//                 start_row = select_end_row;
//                 start_col = select_end_col;
//                 end_row = select_start_row;
//                 end_col = select_start_col;
//             }
//             if (start_row == end_row)
//             {
//                 auto& line = lines_buffer[start_row];
//                 auto start = start_col;
//                 start = line.find(_s, start);
//                 while (start < end_col)
//                 {
//                     count++;
//                     start = line.find(_s, start + 1);
//                 }
//             }
//             else
//             {
//                 for (size_t i = start_row; i <= end_row; i++)
//                 {
//                     if (i == start_row)
//                     {
//                         auto& line = lines_buffer[i];
//                         auto start = start_col;
//                         start = line.find(_s, start);
//                         while (start != string::npos)
//                         {
//                             count++;
//                             start = line.find(_s, start + 1);
//                         }
//                     }
//                     else if (i == end_row)
//                     {
//                         auto& line = lines_buffer[i];
//                         auto start = line.find(_s);
//                         while (start < end_col)
//                         {
//                             count++;
//                             start = line.find(_s, start + 1);
//                         }
//                     }
//                     else
//                     {
//                         auto& line = lines_buffer[i];
//                         auto start = line.find(_s);
//                         while (start != string::npos)
//                         {
//                             count++;
//                             start = line.find(_s, start + 1);
//                         }
//                     }
//                 }
//             }
//         }
//         return count;
//     }
// };

// void solve()
// {
//     ios::sync_with_stdio(false);
//     text_editor editor;
//     size_t n;
//     cin >> n;
//     string operation;
//     string op_buf;
//     char c;

//     for (size_t i = 0; i < n; i++)
//     {
//         editor.display();
//         cin >> operation;
//         if (operation == "INSERT")
//         {
//             cin >> op_buf;
//             if (op_buf == "Char")
//             {
//                 cin >> c;
//                 editor.insert(c);
//             }
//             if (op_buf == "Space")
//             {
//                 editor.whitespaces();
//             }
//             if (op_buf == "Enter")
//             {
//                 editor.enter();
//             }
//             if (op_buf == "Paste")
//             {
//                 editor.paste();
//             }

//             continue;
//         }
//         if (operation == "MOVE")
//         {
//             cin >> op_buf;
//             if (op_buf == "Home")
//             {
//                 editor.home();
//                 continue;
//             }
//             if (op_buf == "End")
//             {
//                 editor.end();
//                 continue;
//             }
//             if (op_buf == "Left")
//             {
//                 editor.cursor_left();
//                 continue;
//             }
//             if (op_buf == "Right")
//             {
//                 editor.cursor_right();
//                 continue;
//             }
//             if (op_buf == "Up")
//             {
//                 editor.cursor_up();
//                 continue;
//             }
//             if (op_buf == "Down")
//             {
//                 editor.cursor_down();
//                 continue;
//             }
//             continue;
//         }
//         if (operation == "REMOVE")
//         {
//             cin >> op_buf;
//             if (op_buf == "Backspace")
//             {
//                 editor.backspace();
//                 continue;
//             }
//             if (op_buf == "Del")
//             {
//                 editor.del();
//                 continue;
//             }
//         }
//         if (operation == "SHIFT")
//         {
//             editor.change_mode();
//             continue;
//         }
//         if (operation == "COPY")
//         {
//             editor.copy();
//             continue;
//         }
//         if (operation == "COUNT")
//         {
//             cout << editor.count() << endl;
//             continue;
//         }
//         if (operation == "FIND")
//         {
//             cin >> op_buf;
//             cout << editor.find(op_buf) << endl;
//             continue;
//         }
//         if (operation == "PRINT")
//         {
//             editor.print();
//             continue;
//         }
//     }
// }

// void test()
// {
//     text_editor editor;
//     string s = "hello\nworld";
//     for (auto c : s)
//     {
//         editor.insert(c);
//     }
//     editor.change_mode();
//     editor.display();
//     editor.cursor_left();
//     editor.display();
//     editor.cursor_left();
//     editor.display();
//     editor.change_mode();
//     editor.display();
//     editor.backspace();
//     editor.display();
// }
// int main()
// {
//     solve();
//     // test();
//     return 0;
// }