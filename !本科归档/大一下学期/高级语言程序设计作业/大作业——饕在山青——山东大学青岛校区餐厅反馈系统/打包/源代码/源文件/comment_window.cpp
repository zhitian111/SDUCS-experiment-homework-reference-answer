#include"comment_window.h"

#include"log.h"

#include"qmessagebox.h"

#include"system.h"

CommentWindow::CommentWindow(QWidget* parent) :
	QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowModality(Qt::ApplicationModal);
	setWindowTitle("查看反馈");
	connect(ui.action, &QAction::triggered, this, &CommentWindow::on_action_1_clicked);
	connect(ui.action_2, &QAction::triggered, this, &CommentWindow::on_action_2_clicked);
	connect(ui.pushButton, &QPushButton::click, this, &CommentWindow::on_pushButton_clicked);
	connect(ui.seach_what, SIGNAL(returnPressed()), this, SLOT(on_pushButton_clicked()));

	Log("SYSTEM", "Open the comments shown window");
	Log(System::admin.GetUsername(), "Star checking the comments");
	ui.action->triggered();
}


CommentWindow::~CommentWindow()
{

}

void CommentWindow::on_action_1_clicked()
{
	ui.seach_what->setVisible(true);
	ui.pushButton->setVisible(true);
	ui.show_text->clear();
	ui.seach_what->clear();
	ui.label->setVisible(true);
	ui.label_2->setVisible(false);
}

void CommentWindow::on_action_2_clicked()
{
	ui.seach_what->setVisible(false);
	ui.pushButton->setVisible(false);
	ui.show_text->clear();
	ui.label->setVisible(false);
	ui.label_2->setVisible(true);
	for (auto i = fired_dishs.begin(); i != fired_dishs.end(); i++)
	{
		if (!(*i).second.GetComments().empty())
		{
			ui.show_text->append("----------------------------");
			for (int j = 0; j < (*i).second.GetComments().size(); j++)
			{
				ui.show_text->append(QString::fromStdString((*i).first + " " + "反馈：" + (*i).second.this_comments[j]));
			}
			ui.show_text->append("----------------------------");

		}
	}
	for (auto i = halal_dishs.begin(); i != halal_dishs.end(); i++)
	{
		if (!(*i).second.GetComments().empty())
		{
			ui.show_text->append("----------------------------");
			for (int j = 0; j < (*i).second.GetComments().size(); j++)
			{
				ui.show_text->append(QString::fromStdString((*i).first + " " + "反馈：" + (*i).second.this_comments[j]));
			}
			ui.show_text->append("----------------------------");
		}
	}
	for (auto i = flour_dishs.begin(); i != flour_dishs.end(); i++)
	{
		if (!(*i).second.GetComments().empty())
		{
			ui.show_text->append("----------------------------");
			for (int j = 0; j < (*i).second.GetComments().size(); j++)
			{
				ui.show_text->append(QString::fromStdString((*i).first + " " + "反馈：" + (*i).second.this_comments[j]));
			}
			ui.show_text->append("----------------------------");
		}
	}
}

void CommentWindow::on_pushButton_clicked()
{
	ui.show_text->clear();
	std::string tem_string = ui.seach_what->text().toStdString();
	if (fired_dishs.count(tem_string) == 0 && flour_dishs.count(tem_string) == 0 && halal_dishs.count(tem_string) == 0)
	{
		QMessageBox::information(this, "搜索失败", "该菜品不存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		Log(System::admin.GetUsername(), "Tried to search comment,failed");
		return;
	}
	if (fired_dishs.count(tem_string) == 1)
	{
		for (int i = 0; i < fired_dishs.at(tem_string).this_comments.size(); i++)
		{
			ui.show_text->append(QString::fromStdString(tem_string+" "+"反馈："+fired_dishs.at(tem_string).this_comments[i]));
		}
	}
	if (flour_dishs.count(tem_string) == 1)
	{
		for (int i = 0; i < flour_dishs.at(tem_string).this_comments.size(); i++)
		{
			ui.show_text->append(QString::fromStdString(tem_string + " " + "反馈：" + flour_dishs.at(tem_string).this_comments[i]));
		}
	}
	if (halal_dishs.count(tem_string) == 1)
	{
		for (int i = 0; i < halal_dishs.at(tem_string).this_comments.size(); i++)
		{
			ui.show_text->append(QString::fromStdString(tem_string + " " + "反馈：" + halal_dishs.at(tem_string).this_comments[i]));
		}
	}

	Log(System::admin.GetUsername(), "Tried to search comment,successed");

}

void CommentWindow::closeEvent(QCloseEvent* e)
{
	Log("SYSTEM", "Close the comments shown window");
	Log(System::admin.GetUsername(), "Stop checking the comments");
	e->accept();
	delete(this);
}