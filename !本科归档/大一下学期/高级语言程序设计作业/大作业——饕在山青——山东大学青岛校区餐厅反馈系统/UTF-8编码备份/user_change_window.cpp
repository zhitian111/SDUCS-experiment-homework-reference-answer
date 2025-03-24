#include"user_change_window.h"
#include"system.h"
#include<qmessagebox.h>
#include"log.h"
#include<QCloseEvent>
#include<qpushbutton.h>
UserChange::UserChange(QWidget* parent):QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowModality(Qt::ApplicationModal);
	setWindowTitle("账户管理");

	
	ui.change_password_1->setEchoMode(QLineEdit::Password);
	ui.change_password_2->setEchoMode(QLineEdit::Password);
	ui.change_password_3->setEchoMode(QLineEdit::Password);
	ui.delet_user_2->setEchoMode(QLineEdit::Password);

	connect(ui.change_password_push_button, &QPushButton::click, this, &UserChange::on_change_password_push_button_clicked);
	connect(ui.change_name_push_button, &QPushButton::click, this, &UserChange::on_change_name_push_button_clicked);
	connect(ui.delet_user_push_button, &QPushButton::click, this, &UserChange::on_delet_user_push_button_clicked);
	

	
	Log("SYSTEM", "Open account manage window of user:" + System::student_and_teacher.GetUsername());
	Log(System::student_and_teacher.GetUsername(), "Tried to manage the account,successed");
}

UserChange::~UserChange()
{

}


void UserChange::on_change_password_push_button_clicked()
{

	std::string tem_string_1 = ui.change_password_1->text().toStdString();
	std::string tem_string_2 = ui.change_password_2->text().toStdString();
	std::string tem_string_3 = ui.change_password_3->text().toStdString();
//	Log(System::student_and_teacher.GetPassword(), "Tries to reset password,failed");
	if (tem_string_1 == "" || tem_string_2 == "" || tem_string_3 == "")
	{
		QMessageBox::information(this, "修改失败", "请输入完整信息！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::student_and_teacher.GetUsername(), "Tries to reset password,failed");
		return;
	}
	if (PublicKey(tem_string_1) != System::student_and_teacher.GetPassword())
	{
		QMessageBox::information(this, "修改失败", "密码错误", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::student_and_teacher.GetUsername(), "Tries to reset password,failed");

		return;
	}
	if (tem_string_2 != tem_string_3)
	{
		QMessageBox::information(this, "修改失败", "两次输入的新密码不一致", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::student_and_teacher.GetUsername(), "Tries to reset password,failed");
		return;
	}
	students_and_teachers[System::student_and_teacher.GetUsername()].ResetPassword(tem_string_2);
	System::student_and_teacher.ResetPassword(tem_string_2);
	QMessageBox::information(this, "修改成功", "点击任意键继续", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	ui.change_password_1->clear();
	ui.change_password_2->clear();
	ui.change_password_3->clear();
	System::user_whether_changed = true;
}


void UserChange::on_change_name_push_button_clicked()
{
	std::string tem_string_1 = ui.change_name_1->text().toStdString();
	std::string tem_string_2 = ui.change_name_2->text().toStdString();
	std::string tem_string_3 = ui.change_name_3->text().toStdString();
	//	Log(System::student_and_teacher.GetPassword(), "Tries to reset password,failed");
	if (tem_string_1 == "" || tem_string_2 == "" || tem_string_3 == "")
	{
		QMessageBox::information(this, "修改失败", "请输入完整信息！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::student_and_teacher.GetUsername(), "Tries to reset name,failed");
		return;
	}
	if (PublicKey(tem_string_1) != System::student_and_teacher.GetPassword())
	{
		QMessageBox::information(this, "修改失败", "姓名错误", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::student_and_teacher.GetUsername(), "Tries to reset name,failed");

		return;
	}
	if (tem_string_2 != tem_string_3)
	{
		QMessageBox::information(this, "修改失败", "两次输入的新姓名不一致", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::student_and_teacher.GetUsername(), "Tries to reset name,failed");
		return;
	}
	students_and_teachers[System::student_and_teacher.GetUsername()].ResetName(tem_string_2);
	System::student_and_teacher.ResetName(tem_string_2);
	QMessageBox::information(this, "修改成功", "点击任意键继续", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	ui.change_password_1->clear();
	ui.change_password_2->clear();
	ui.change_password_3->clear();
	System::user_whether_changed = true;
}

void UserChange::on_delet_user_push_button_clicked()
{
	std::string tem_string_1 = ui.delet_user_1->text().toStdString();
	std::string tem_string_2 = ui.delet_user_2->text().toStdString();
	std::string tem_string_3 = ui.delet_user_3->text().toStdString();
	if (tem_string_1 != System::student_and_teacher.GetUsername())
	{
		QMessageBox::information(this, "注销失败", "账号错误", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::student_and_teacher.GetUsername(), "Tried to delet account,failed");
		return;
	}
	if (tem_string_2 != System::student_and_teacher.GetName())
	{
		QMessageBox::information(this, "注销失败", "姓名错误", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::student_and_teacher.GetName(), "Tried to delet account,failed");
		return;
	}
	if (tem_string_2 != System::student_and_teacher.GetPrivateKey())
	{
		QMessageBox::information(this, "注销失败", "密码错误", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::student_and_teacher.GetUsername(), "Tried to delet account,failed");
		return;
	}
	QMessageBox::StandardButton box;
	box = QMessageBox::question(this, "确认退出", "确认要注销账号吗？\n警告:该操作无法撤销", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	if (box != QMessageBox::Yes)
	{
		return;
	}
	Log(System::student_and_teacher.GetUsername(), "Tried to delet account,successed");
	Log("SYSTEM", "Delete a user,username:" + System::student_and_teacher.GetUsername());
	students_and_teachers.erase(System::student_and_teacher.GetUsername());
	System::student_and_teacher.Exit();
	System::user_whether_changed = true;
	System::main_window->IniView();
	System::main_window->LoginView(true);
	this->close();
}

void UserChange::closeEvent(QCloseEvent* e)
{
	Log(System::student_and_teacher.GetUsername(), "Stop managing account");
	Log("SYSTEM", "Close account manage window of user:" + System::student_and_teacher.GetUsername());
	e->accept();
}