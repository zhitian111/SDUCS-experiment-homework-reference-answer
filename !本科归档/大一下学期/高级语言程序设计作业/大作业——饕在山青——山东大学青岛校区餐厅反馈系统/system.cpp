#include"system.h"
int System::usertype = NONE;
Admin System::admin = null_admin;
StudentAndTeacher System::student_and_teacher = null_user;
bool System::dishes_whether_changed = false;
bool System::user_whether_changed = false;
MainWindow* System::main_window = NULL;
bool System::comment_whether_changed = false;
ManageDishWindow* System::manage_dish_window = NULL;
bool System::admin_whether_changed = false;

void OutPutData()
{
    if (System::dishes_whether_changed == true)
    {
        OutPutDishes();
    }
    if (System::user_whether_changed == true)
    {
        OutPutUsers();
    }
    if (System::comment_whether_changed == true)
    {
        OutPutComments();
    }
    if (System::admin_whether_changed == true)
    {
        OutPutAdmins();
    }
}


Admin default_admin("admin", "admin", admin_permission);
StudentAndTeacher default_studentandteacher("default", "default", "defatult", user_permission);
void init()
{
	//students_and_teachers.insert(std::pair<std::string, StudentAndTeacher>("default", default_studentandteacher));
	//admins.insert(std::pair<std::string, Admin>("admin", default_admin));
	IniDishs();
	IniLog();
	IniAdmin();
	IniUser();
	IniComments();
}
