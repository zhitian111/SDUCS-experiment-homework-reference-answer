#pragma once
#include"ui_log_window.h"
#include<QCloseEvent>
class LogWindow
	:public QMainWindow
{
	Q_OBJECT
public:
	LogWindow(QWidget* parent);
	~LogWindow();
	int biggest_day;
	int now;
private:
	Ui::ui_log_window ui;
protected slots:
	void on_next_clicked();
	void on_last_clicked();
	void on_checkBox_clicked();
	void IniTextBroswer(bool all,int day);
protected:
	void closeEvent(QCloseEvent* e);
};