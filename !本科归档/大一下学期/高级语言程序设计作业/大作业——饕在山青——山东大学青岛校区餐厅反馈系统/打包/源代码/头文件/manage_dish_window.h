#pragma once
#include"ui_manage_dish_window.h"
#include"qmainwindow.h"
#include<QCloseEvent>
#include"ui_add_dish_window.h"
class ManageDishWindow
	:public QMainWindow
{
	Q_OBJECT
public:
	ManageDishWindow(QWidget* parent);
	~ManageDishWindow();
	void IniTable();
	void closeEvent(QCloseEvent* e);
protected slots:
	void on_search_button_clicked();
	void on_add_action_triggered();
	void on_delete_action_triggered();
private:
	Ui::manage_dish_window ui;
};

class AddDishWindow
	:public QMainWindow
{
	Q_OBJECT
public:
	void closeEvent(QCloseEvent* e);
	AddDishWindow(QWidget* parent);
	~AddDishWindow();
private:
	Ui::add_window ui;
protected slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
};