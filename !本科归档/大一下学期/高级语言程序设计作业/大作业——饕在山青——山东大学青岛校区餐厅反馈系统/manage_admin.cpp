#include"manage_admin.h"
#include"system.h"
#include"log.h"
#include"qstandarditemmodel.h"
ManageAdminWindow::ManageAdminWindow(QWidget* parent):
	QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("用户管理");
	connect(ui.reset_password, &QPushButton::click,this,&ManageAdminWindow::on_reset_password_clicked);
	connect(ui.add_admin, &QPushButton::click, this, &ManageAdminWindow::on_add_admin_clicked);
	connect(ui.reset_password, &QPushButton::click, this, &ManageAdminWindow::on_delete_admin_clicked);
	connect(ui.delete_user_button, &QPushButton::click, this, &ManageAdminWindow::on_delete_user_button_clicked);
	setWindowModality(Qt::ApplicationModal);
	
	ui.admin_list->setEditTriggers(QListView::NoEditTriggers);
	ui.admin_list_2->setEditTriggers(QListView::NoEditTriggers);
	ui.add_admin->setFocusPolicy(Qt::NoFocus);
	ui.delete_admin->setFocusPolicy(Qt::NoFocus);
	ui.reset_password->setFocusPolicy(Qt::NoFocus);
	ui.admin_list->setFocusPolicy(Qt::NoFocus);
	ui.admin_list_2->setFocusPolicy(Qt::NoFocus);
	ui.delete_user_button->setFocusPolicy(Qt::NoFocus);
	ui.add_admin_2->setEchoMode(QLineEdit::Password);
	ui.reset_password_1->setEchoMode(QLineEdit::Password);
	ui.reset_password_2->setEchoMode(QLineEdit::Password);
	ui.reset_password_3->setEchoMode(QLineEdit::Password);
	ui.delet_admin_2->setEchoMode(QLineEdit::Password);
	PrintAdmins();
	PrintUsers();

	Log("SYSTEM", "Open the user management window");
	Log(System::admin.GetUsername(), "Start managing users");

}


void ManageAdminWindow::PrintAdmins()
{
	QStandardItemModel* model = new QStandardItemModel;
	for (auto i = admins.begin(); i != admins.end(); ++i)
	{
		QStandardItem* temitem = new QStandardItem(QString::fromStdString((*i).second.GetUsername()));
		model->appendRow(temitem);
	}
	ui.admin_list->setModel(model);
}

void ManageAdminWindow::PrintUsers()
{
	QStandardItemModel* model = new QStandardItemModel;
	for (auto i = students_and_teachers.begin(); i != students_and_teachers.end(); ++i)
	{
		QStandardItem* temitem = new QStandardItem(QString::fromStdString((*i).second.GetUsername() + " " + (*i).second.GetName()));
		model->appendRow(temitem);
	}
	ui.admin_list_2->setModel(model);
}


void ManageAdminWindow::on_delete_user_button_clicked()
{

	std::string tem_string = ui.delet_user->text().toStdString();

	if (tem_string=="")
	{
		QMessageBox::information(this, "删除失败", "请输入完整信息", QMessageBox::Ok);
		Log(System::admin.GetUsername(), "Tried to delete a user account,failed");

		return;
	}

	if (students_and_teachers.count(tem_string) == 0)
	{
		QMessageBox::information(this, "删除失败", "此用户不存在", QMessageBox::Ok);
		Log(System::admin.GetUsername(), "Tried to delete a user account,failed");
		return;
	}

		QMessageBox::StandardButton box;
		box = QMessageBox::question(this, "确认删除", "确认要删除这个账号吗？\n警告：此操作不可撤销", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (box != QMessageBox::Yes)
		{
			return;
		}
		students_and_teachers.erase(tem_string);
		System::user_whether_changed = true;
		PrintUsers();
		Log(System::admin.GetUsername(), "Tried to delete a user account,successed");
		Log("SYSTEM", "Delete a user account,username:" + tem_string);
		ui.delet_user->clear();
		return;
}


ManageAdminWindow::~ManageAdminWindow()
{

}


void ManageAdminWindow::closeEvent(QCloseEvent* e)
{
	Log("SYSTEM", "Close the user management window");
	Log(System::admin.GetUsername(), "Stop managing users");
	e->accept();
	delete(this);
}
 
void ManageAdminWindow::on_reset_password_clicked()
{

	std::string tem_string_1 = ui.reset_password_1->text().toStdString();
	std::string tem_string_2 = ui.reset_password_2->text().toStdString();
	std::string tem_string_3 = ui.reset_password_3->text().toStdString();
	//	Log(System::student_and_teacher.GetPassword(), "Tries to reset password,failed");
	if (tem_string_1 == "" || tem_string_2 == "" || tem_string_3 == "")
	{
		QMessageBox::information(this, "修改失败", "请输入完整信息！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::admin.GetUsername(), "Tries to reset password,failed");
		return;
	}
	if (PublicKey(tem_string_1) != System::admin.GetPassword())
	{
		QMessageBox::information(this, "修改失败", "密码错误", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::admin.GetUsername(), "Tries to reset password,failed");

		return;
	}
	if (tem_string_2 != tem_string_3)
	{
		QMessageBox::information(this, "修改失败", "两次输入的新密码不一致", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::admin.GetUsername(), "Tries to reset password,failed");
		return;
	}
	admins[System::admin.GetUsername()].ResetPassword(tem_string_2);
	System::admin.ResetPassword(tem_string_2);
	QMessageBox::information(this, "修改成功", "点击任意键继续", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	ui.reset_password_1->clear();
	ui.reset_password_2->clear();
	ui.reset_password_3->clear();
	System::admin_whether_changed = true;
}


void ManageAdminWindow::on_add_admin_clicked()
{
	std::string tem_string_1 = ui.add_admin_1->text().toStdString();
	std::string tem_string_2 = ui.add_admin_2->text().toStdString();

	if (tem_string_1 == "" || tem_string_2 == "")
	{
		QMessageBox::information(this, "添加失败", "请输入完整信息", QMessageBox::Ok);
		Log(System::admin.GetUsername(), "Tried to add an admin account,failed");
		return;
	}
	if (admins.count(tem_string_1) > 0)
	{
		QMessageBox::information(this, "添加失败", "该管理员账户已存在", QMessageBox::Ok);
		Log(System::admin.GetUsername(), "Tried to add an admin account,failed");
		return;
	}


	QMessageBox::StandardButton box;
	box = QMessageBox::question(this, "确认管理员信息", QString::fromStdString("确认添加以下管理员账户？\nusername:"+tem_string_1+"\npassword:"+tem_string_2), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	if (box != QMessageBox::Yes)
	{
		return;
	}
	Admin* tem = new Admin(tem_string_1,tem_string_2);
	admins.insert(std::pair<std::string, Admin>(tem->GetUsername(), *tem));
	admin_usernames.push_back(tem_string_1);
	System::admin_whether_changed = true;
	Log(System::admin.GetUsername(), "Tried to add an admin account,successed");
	Log("SYSTEM", "Add an admin account,username:" + tem_string_1);
	ui.add_admin_1->clear();
	ui.add_admin_2->clear();
	PrintAdmins();

}
void ManageAdminWindow::on_delete_admin_clicked()
{
	std::string tem_string_1 = ui.delet_admin_1->text().toStdString();
	std::string tem_string_2 = ui.delet_admin_2->text().toStdString();

	if (tem_string_1 == "" || tem_string_2 == "")
	{
		QMessageBox::information(this, "删除失败", "请输入完整信息", QMessageBox::Ok);
		Log(System::admin.GetUsername(), "Tried to delete an admin account,failed");

		return;
	}

	if (admins.count(tem_string_1) == 0)
	{
		QMessageBox::information(this, "删除失败", "此管理员用户不存在", QMessageBox::Ok);
		Log(System::admin.GetUsername(), "Tried to delete an admin account,failed");
		return;
	}

	if (admins.at(tem_string_1).GetPrivateKey() != tem_string_2)
	{
		QMessageBox::information(this, "删除失败", "密码错误", QMessageBox::Ok);
		Log(System::admin.GetUsername(), "Tried to delete an admin account,failed");
		return;
	}
	
	if (tem_string_1 != System::admin.GetUsername())
	{
		QMessageBox::StandardButton box;
		box = QMessageBox::question(this, "确认删除", "确认要删除这个账号吗？\n警告：此操作不可撤销", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (box != QMessageBox::Yes)
		{
			return;
		}
		admins.erase(tem_string_1);
		System::admin_whether_changed = true;
		PrintAdmins();
		Log(System::admin.GetUsername(), "Tried to delete an admin account,successed");
		Log("SYSTEM", "Delete an admin account,username:" + tem_string_1);
		ui.delet_admin_1->clear();
		ui.delet_admin_2->clear();

		return;
	}
	if (tem_string_1 == System::admin.GetUsername())
	{
		QMessageBox::StandardButton box;
		box = QMessageBox::question(this, "确认删除", "这个账号是你正在登录的账号\n确认要注销账号吗？\n警告：此操作不可撤销", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (box != QMessageBox::Yes)
		{
			return;
		}
		Log(System::admin.GetUsername(), "Tried to delete an admin account,successed");
		Log("SYSTEM", "Delete an admin account,username:" + tem_string_1);
		admins.erase(System::admin.GetUsername());
		System::admin.Exit();
		System::admin_whether_changed = true;
		System::main_window->IniView();
		System::main_window->LoginView(true);
		ui.delet_admin_1->clear();
		ui.delet_admin_2->clear();
		this->close();
	}
	
}