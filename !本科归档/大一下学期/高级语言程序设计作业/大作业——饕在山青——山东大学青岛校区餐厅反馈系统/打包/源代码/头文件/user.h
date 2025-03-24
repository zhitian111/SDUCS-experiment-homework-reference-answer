#ifndef USER_H
#define USER_H

#define STUDENT_AND_TEACHER 1
#define ADMIN				0
#define NONE				-1

#include"permission.h"
#include"password.h"
#include<string>
#include<map>
#include<vector>
#include<fstream>
//用户类
class User
{
private:
	Password password;
	bool login_status = false;
protected:
	Permission permission;
	std::string username;
public:
	std::string GetPassword() { return password.GetPassword(); };
	std::string GetPrivateKey() { return password.GetPrivateKey(); };
	User():password("none"),username("none"),permission(black_permission) {};
	User(std::string username,std::string password,Permission permission)
		:username(username),password(password),permission(permission) {};
	~User() {};
	void ResetPassword(std::string password) { this->password.ResetPassword(password); };
	bool Login(std::string whether_password);								//登录函数
	void Exit();
	std::string GetUsername() { return username; };
};



//师生类
class StudentAndTeacher:
	public User
{
private:
	std::string name;
public:
	StudentAndTeacher() :name("none") {};
	StudentAndTeacher(std::string username, std::string password, std::string name, Permission permission = user_permission)
		: User(username, password, permission), name(name) {};
	void ResetName(std::string newname) { name = newname; };
	void Blacked();					//被加入黑名单
	void Whited();					//被移回白名单
	std::string GetName() { return name; };
};

//管理员类
class Admin:
	public User
{
public:
	Admin() {};
	Admin(std::string username, std::string password, Permission permission = admin_permission): User(username, password, permission){};
};



extern std::map<std::string, StudentAndTeacher> students_and_teachers;	//学生/老师用户列表
extern std::map<std::string, Admin> admins;							//管理员列表
extern std::map<std::string, StudentAndTeacher> black_list;			//黑名单
extern std::map<std::string, StudentAndTeacher> white_list;			//白名单
extern std::vector<std::string> admin_usernames;
extern std::vector<std::string> students_and_teacher_usernames;

//空用户
extern StudentAndTeacher null_user;


extern Admin null_admin;


void AddUser(std::string username, std::string password, std::string name);
void IniUser();
void IniAdmin();
void OutPutUsers();
void OutPutAdmins();

#endif
