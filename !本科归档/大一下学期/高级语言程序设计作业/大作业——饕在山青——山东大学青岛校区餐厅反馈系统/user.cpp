#include"user.h"
#include<vector>
#include<qmessagebox.h>


#include"log.h"
#include"system.h"
#include"MainWindow.h"
//被加入黑名单
void StudentAndTeacher::Blacked()
{
	black_list.insert(std::pair<std::string, StudentAndTeacher>(username, *this));
	white_list.erase(username);
	permission = black_permission;
}

//被移回白名单
void StudentAndTeacher::Whited()
{
	white_list.insert(std::pair<std::string, StudentAndTeacher>(username, *this));
	black_list.erase(username);
	permission = user_permission;
}




//登录函数
bool User::Login(std::string whether_password)
{
	if (PublicKey(whether_password) == password.GetPassword())
	{
		login_status = true;
		return true;
	}
	else
	{
		login_status = false;
		return false;
	}
}

//退出函数
void User::Exit()
{
	login_status = false;
}

std::map<std::string, StudentAndTeacher> students_and_teachers;	//学生/老师用户列表
std::map<std::string, Admin> admins;							//管理员列表
std::map<std::string, StudentAndTeacher> black_list;			//黑名单
std::map<std::string, StudentAndTeacher> white_list;			//白名单
std::vector<std::string> students_and_teacher_usernames;
std::vector<std::string> admin_usernames;

//空用户
StudentAndTeacher null_user("none", "none", "none", black_permission);


Admin null_admin("none", "none", black_permission);

void AddUser(std::string username, std::string password, std::string name)
{
	StudentAndTeacher* temp = new StudentAndTeacher(username, password, name);
	students_and_teachers.insert(std::pair<std::string, StudentAndTeacher>(username, *temp));
	students_and_teacher_usernames.push_back(username);
	//std::fstream user_file;
	//user_file.open("users.txt", std::ios::out | std::ios::app);
	//user_file << "\n" << name << " " << username << " " << password ;
	//user_file.close();
	System::user_whether_changed = true;
}

void IniAdmin()
{
	std::fstream admin_file;
	admin_file.open("admin.txt", std::ios::in);
	if (!admin_file.is_open())
	{
		QMessageBox::information(NULL, "初始化失败", "管理员列表初始化失败");
		return;
	}
	std::string username;
	std::string password;
	if (admin_file.is_open())
	{
		while (admin_file>>username>>password)
		{
			//username = QString::fromLocal8Bit(username).toUtf8();
			//password = QString::fromLocal8Bit(password).toUtf8();
			if (username == "\n")
			{
				break;
			}
			Admin* temp = new Admin(username, password);
			admins.insert(std::pair<std::string, Admin>(username, *temp));
			admin_usernames.push_back(username);
		}
	}
}

void IniUser()
{
	std::fstream user_file;
	user_file.open("users.txt", std::ios::in);
	if (!user_file.is_open())
	{
		QMessageBox::information(NULL, "初始化失败", "用户列表初始化失败");
		return;
	}
	std::string username;
	std::string password;
	std::string name;
	if (user_file.is_open())
	{
		while (user_file >> name >> username >> password)
		{
			//name = QString::fromLocal8Bit(name).toUtf8();
			//username = QString::fromLocal8Bit(username).toUtf8();
			//password = QString::fromLocal8Bit(password).toUtf8(); 
			if (name == "\n")
			{
				break;
			}
			StudentAndTeacher* temp = new StudentAndTeacher(username, password, name);
			students_and_teachers.insert(std::pair<std::string, StudentAndTeacher>(username, *temp));
			students_and_teacher_usernames.push_back(username);
		}
	}
}


void OutPutUsers()
{

	std::fstream user_file;
	user_file.open("users.txt",std::ios::out);
	user_file.clear();
	if (user_file.is_open())
	{
		auto i = students_and_teachers.begin();
		user_file << (*i).second.GetName() << " " << (*i).second.GetUsername() << " " << (*i).second.GetPrivateKey();
		i++;
		for (; i != students_and_teachers.end(); ++i)
		{
			user_file << "\n" << (*i).second.GetName() << " " << (*i).second.GetUsername() << " " << (*i).second.GetPrivateKey();
		}
	}
	
	user_file.close();
	Log("SYSTEM", "Refresh the users file");

}



void OutPutAdmins()
{

	std::fstream user_file;
	user_file.open("admin.txt", std::ios::out);
	user_file.clear();
	if (user_file.is_open())
	{
		auto i = admins.begin();
		user_file << (*i).second.GetUsername() << " " << (*i).second.GetPrivateKey();
		i++;
		for (; i != admins.end(); ++i)
		{
			user_file << "\n" << (*i).second.GetUsername() << " " << (*i).second.GetPrivateKey();
		}
	}

	user_file.close();
	Log("SYSTEM", "Refresh the admins file");

}