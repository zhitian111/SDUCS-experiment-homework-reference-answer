#pragma once
#include"ui_show_table.h"
#include<qmainwindow.h>
#include<QCloseEvent>

class ShowTable:public QMainWindow
{
	Q_OBJECT
public:
	ShowTable(QWidget* parent,int mode);
	~ShowTable();
	void CheckView();
	void SearchView();
private:
	Ui::show_table ui;
protected:
	void closeEvent(QCloseEvent* e);
protected slots:
	void on_search_push_button_clicked();

};