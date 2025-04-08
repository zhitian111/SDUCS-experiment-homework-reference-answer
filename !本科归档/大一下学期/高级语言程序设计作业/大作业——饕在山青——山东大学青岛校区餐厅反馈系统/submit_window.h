#pragma once
#include"ui_SubmitWindow.h"
#include"qmainwindow.h"
#include<QCloseEvent>
class WindowSubmit
	:public QMainWindow
{
	Q_OBJECT
public:
	WindowSubmit(QWidget* parent);
	~WindowSubmit() {};
	void closeEvent(QCloseEvent* e);
protected slots:
	void on_submit_push_button_clicked();
	void on_cancel_push_button_clicked();
private:
	Ui::SubmintWindow ui;
};