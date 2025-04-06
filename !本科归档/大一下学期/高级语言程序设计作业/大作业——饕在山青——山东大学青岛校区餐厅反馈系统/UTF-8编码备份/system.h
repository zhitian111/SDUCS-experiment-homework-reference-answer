#ifndef SYSTEM_H
#define SYSTEM_H
#include"user.h"
#include"dishs.h"
#include"MainWindow.h"
#include"log.h"
#include"manage_dish_window.h"


class System
{
public:
	System() {};
	~System() {};
	static MainWindow* main_window;
	static int usertype;
	static Admin admin;
	static StudentAndTeacher student_and_teacher;
	static bool dishes_whether_changed;
	static bool user_whether_changed;
	static bool comment_whether_changed;
	static bool admin_whether_changed;
	static ManageDishWindow* manage_dish_window;
	
};
void init();

void OutPutData();
#endif // !_SYSTEM_H_

