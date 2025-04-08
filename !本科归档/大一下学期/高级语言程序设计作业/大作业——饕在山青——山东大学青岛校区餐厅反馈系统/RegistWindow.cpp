#include"regist_window.h"
#include"user.h"
#include<qmessagebox.h>
#include"log.h"

RegistWindow::RegistWindow(QWidget* parent): QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowModality(Qt::ApplicationModal);
	setWindowTitle("注册窗口");
	ui.password1->setEchoMode(QLineEdit::Password);
	ui.password2->setEchoMode(QLineEdit::Password);
	connect(ui.regist_push_button,&QPushButton::click, this, &RegistWindow::on_regist_push_button_clicked);
	connect(ui.cancel_push_button,&QPushButton::click, this, &RegistWindow::on_cancel_push_button_clicked);
	connect(ui.username, SIGNAL(returnPressed()), this, SLOT(on_regist_push_button_clicked()));
	connect(ui.name, SIGNAL(returnPressed()), this, SLOT(on_regist_push_button_clicked()));
	connect(ui.password1, SIGNAL(returnPressed()), this, SLOT(on_regist_push_button_clicked()));
	connect(ui.password2, SIGNAL(returnPressed()), this, SLOT(on_regist_push_button_clicked()));

	Log("SYSTEM", "Open the registration window");

}

void RegistWindow::on_regist_push_button_clicked()
{
	std::string username = ui.username->text().toStdString();
	std::string name = ui.name->text().toStdString();
	std::string password1 = ui.password1->text().toStdString();
	std::string password2 = ui.password2->text().toStdString();
	if (username == "" || name == "" || password1 == "" || password2 == "")
	{
		Log(username, "Tried to regist,failed");
		QMessageBox::information(this, "注册失败", "请输入完整信息", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	if (password1 != password2)
	{
		Log(username, "Tried to regist,failed");
		QMessageBox::information(this, "注册失败", "两次输入的密码不一致", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	if (students_and_teachers.count(username) == 1 || admins.count(username) == 1)
	{
		Log(username, "Tried to regist,failed");
		QMessageBox::information(this, "注册失败", "该用户已存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	AddUser(username,password1,name);
	Log(username, "Tried to regist,successed");
	Log("SYSTEM", "Add a new user, username: "+username);
	QMessageBox::information(this, "注册成功", "注册成功,按任意键继续", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	this->close();
}
void RegistWindow::closeEvent(QCloseEvent* e)
{
	Log("SYSTEM", "Close the registration window");
	e->accept();
}
void RegistWindow::on_cancel_push_button_clicked()
{

	this->close();

}