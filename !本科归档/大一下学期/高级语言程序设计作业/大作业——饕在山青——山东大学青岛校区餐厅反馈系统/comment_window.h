#pragma once
#include"ui_comment_window.h"
#include"qmainwindow.h"
#include<QCloseEvent>
class CommentWindow
	:public QMainWindow
{
	Q_OBJECT
public:
	CommentWindow(QWidget *parent);
	~CommentWindow();
private:
	Ui::comment_window ui;
protected slots:
	void on_action_1_clicked();
	void on_action_2_clicked();
	void on_pushButton_clicked();
public:
	void closeEvent(QCloseEvent* e);
};