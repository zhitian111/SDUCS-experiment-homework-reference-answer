#include"submit_window.h"
#include"system.h"
#include"log.h"
#include"qpushbutton.h"
#include"qmessagebox.h"
WindowSubmit::WindowSubmit(QWidget *parent):
	QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("提交意见");
	setWindowModality(Qt::ApplicationModal);

	connect(ui.submit_push_button, &QPushButton::click, this, &WindowSubmit::on_submit_push_button_clicked);
	connect(ui.cancel_push_button, &QPushButton::click, this, &WindowSubmit::on_cancel_push_button_clicked);


}


void WindowSubmit::on_submit_push_button_clicked()
{
	std::string tem_dish_name = ui.dish_name->text().toStdString();
	std::string tem_text = ui.main_text->toPlainText().toStdString();
	if (fired_dishs.count(tem_dish_name) == 0 && flour_dishs.count(tem_dish_name) == 0 && halal_dishs.count(tem_dish_name) == 0)
	{
		QMessageBox::information(this, "提交失败", "该菜品不存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::student_and_teacher.GetUsername(), "Tried to submit comment,failed");
		return;
	}
	for (int i = 0; i < tem_text.size(); i++)
	{
		if (tem_text[i] == '\n')
		{
			QMessageBox::information(this, "提交失败", "请勿在正文中键入换行符", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			Log(System::student_and_teacher.GetUsername(), "Tried to submit comment,failed");
			return;
		}
	}
	if (fired_dishs.count(tem_dish_name) == 1)
	{
		fired_dishs.at(tem_dish_name).AppComment(tem_text);
	}
	if (flour_dishs.count(tem_dish_name) == 1)
	{
		flour_dishs.at(tem_dish_name).AppComment(tem_text);
	}
	if (halal_dishs.count(tem_dish_name) == 1)
	{
		halal_dishs.at(tem_dish_name).AppComment(tem_text);
	}
	QMessageBox::information(this, "提交成功", "感谢您的反馈！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	System::comment_whether_changed = true;
	Log(System::student_and_teacher.GetUsername(), "Tried to submit comment,successed, dish name:" + tem_dish_name + " content:" + tem_text);
	ui.main_text->clear();
	ui.dish_name->clear();
}

void WindowSubmit::on_cancel_push_button_clicked()
{
	this->close();
}

void WindowSubmit::closeEvent(QCloseEvent* e)
{
	Log(System::student_and_teacher.GetUsername(), "Stop submitting comments");

	Log("SYSTEM", "Close the submit window");
	e->accept();
	delete(this);
}