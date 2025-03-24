#pragma once
#include"ui_UserChangeWindow.h"
#include<qmainwindow.h>
#include<qwidget.h>
class UserChange
	:public QMainWindow
{
	Q_OBJECT

public:
	UserChange(QWidget* parent);
	~UserChange();
private:
	Ui::UserChangeWindow ui;
protected slots:
	void on_change_password_push_button_clicked();
	void on_change_name_push_button_clicked();
	void on_delet_user_push_button_clicked();

protected:
	void closeEvent(QCloseEvent* e);
};