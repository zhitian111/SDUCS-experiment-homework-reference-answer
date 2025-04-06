#pragma once
#include"ui_manage_admin.h"
#include<QCloseEvent>

class ManageAdminWindow :
	public QMainWindow
{
	Q_OBJECT
public:
	ManageAdminWindow(QWidget* parent);
	~ManageAdminWindow();
	void closeEvent(QCloseEvent* e);
	void PrintAdmins();
	void PrintUsers();
private:
	Ui::manage_admin_window ui;
protected slots:
	void on_reset_password_clicked();
	void on_add_admin_clicked();
	void on_delete_admin_clicked();
	void on_delete_user_button_clicked();
};
