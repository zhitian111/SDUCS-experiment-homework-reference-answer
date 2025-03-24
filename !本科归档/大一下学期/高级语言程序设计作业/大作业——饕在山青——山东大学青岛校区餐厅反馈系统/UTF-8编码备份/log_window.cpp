#include"log_window.h"
#include"log.h"
#include"system.h"
#include<fstream>
#include"qmessagebox"
LogWindow::LogWindow(QWidget* parent) :
	QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("查看日志");
	setWindowModality(Qt::ApplicationModal);
	connect(ui.next, &QPushButton::click, this, &LogWindow::on_next_clicked);
	connect(ui.last, &QPushButton::click, this, &LogWindow::on_last_clicked);
	connect(ui.checkBox, &QCheckBox::click, this, &LogWindow::on_checkBox_clicked);
	ui.checkBox->setChecked(true);
	Log("SYSTEM", "Open the log window");
	Log(System::admin.GetUsername(), "Start checking the log");
	
	IniTextBroswer(true,-1);
	std::fstream tem_file;
	std::string tem_string;
	biggest_day = 0;
	tem_file.open("log.txt", std::ios::in);
	while (std::getline(tem_file,tem_string))
	{
		if (tem_string=="")
		{
			biggest_day++;
		}
	}
	biggest_day = biggest_day / 2;
	now = 1;
	ui.last->setEnabled(false);
	ui.next->setEnabled(false);
}


LogWindow::~LogWindow()
{

}

void LogWindow::IniTextBroswer(bool all,int day)
{
	if (day > biggest_day)
	{
		QMessageBox::information(this, "切换失败", "已经是最后一条了", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		now -= 1;
		return;
	}
	if (day == 0)
	{
		QMessageBox::information(this, "切换失败", "已经是第一条了", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		now += 1;
		return;
	}
	std::fstream tem_file;
	std::string tem_string;
	tem_file.open("log.txt", std::ios::in);
	ui.textBrowser->clear();
	int cnt = 0;
	if (all)
	{
		while (std::getline(tem_file, tem_string))
		{
			ui.textBrowser->append(QString::fromStdString(tem_string));
		}
		return;
	}
	if (!all)
	{
		while (std::getline(tem_file, tem_string))
		{
			if (tem_string == "")
			{
				cnt++;
			}
			if (cnt == day * 2 + 1)
			{
				while (std::getline(tem_file,tem_string))
				{
					if (tem_string == "")
					{
						break;
					}
					ui.textBrowser->append(QString::fromStdString(tem_string));
				}
				break;
			}
		}
		return;
	}
	tem_file.close();
}



void LogWindow::closeEvent(QCloseEvent* e)
{
	Log(System::admin.GetUsername(), "Stop checking the log");
	Log("SYSTEM", "Close the log window");
	e->accept();
}


void LogWindow::on_checkBox_clicked()
{
	if (ui.checkBox->isChecked() == true)
	{
		ui.last->setEnabled(false);
		ui.next->setEnabled(false);
		IniTextBroswer(true, -1);
	}
	if (ui.checkBox->isChecked() == false)
	{
		ui.last->setEnabled(true);
		ui.next->setEnabled(true);
		now = 1;
		IniTextBroswer(false, now);
	}
}

void LogWindow::on_last_clicked()
{
	now -= 1;
	IniTextBroswer(false, now);
}

void LogWindow::on_next_clicked()
{
	now += 1;
	IniTextBroswer(false, now);
}