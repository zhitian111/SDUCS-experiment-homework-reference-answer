#include"show_table.h"
#include"log.h"
#include"system.h"
#include"dishs.h"
#include<qmessagebox>
ShowTable::ShowTable(QWidget* parent , int mode):QMainWindow(parent)
{
	Log(System::student_and_teacher.GetUsername(), "Tried to check out the dishes,successed");
	Log("SYSTEM", "Open the show_table window");
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowModality(Qt::ApplicationModal);
	ui.fired_dish_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.flour_dish_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.halal_dish_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	setWindowTitle("菜色列表");
	int tem = 8;
	ui.fired_dish_table->setColumnCount(tem);
	ui.flour_dish_table->setColumnCount(tem);
	ui.halal_dish_table->setColumnCount(tem);
	connect(ui.search_push_button, &QPushButton::click, this, &ShowTable::on_search_push_button_clicked);
	connect(ui.search_what, SIGNAL(returnPressed()), this, SLOT(on_search_button_clicked()));
	if (mode == 1)
	{
		CheckView();
	}
	if (mode == 4)
	{
		SearchView();
	}
}

void ShowTable::SearchView()
{
	ui.search_push_button->setVisible(true);
	ui.search_what->setVisible(true);
	ui.checkBox->setVisible(true);
}


void ShowTable::CheckView()
{
	ui.search_push_button->setVisible(false);
	ui.search_what->setVisible(false);
	ui.checkBox->setVisible(false);

	//分别初始化这三个表格

	//	int cnt = 1;
	for (auto i = fired_dishs.begin(); i != fired_dishs.end(); ++i)
	{
		//	QString cntCol = QString::number(cnt);
		//	QTableWidgetItem* temp = new QTableWidgetItem(cntCol);
		int rowcnt = ui.fired_dish_table->rowCount();
		ui.fired_dish_table->insertRow(rowcnt);
		ui.fired_dish_table->setItem(rowcnt, 0, new QTableWidgetItem(QString::fromStdString(i->second.GetName())));
		ui.fired_dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(i->second.GetIngredients())));
		ui.fired_dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceRestaurant())));
		ui.fired_dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceFloor())));
		ui.fired_dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceWindow())));
		ui.fired_dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(i->second.GetPrice())));
		ui.fired_dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraOne())));
		ui.fired_dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraTwo())));

	}
	for (auto i = flour_dishs.begin(); i != flour_dishs.end(); ++i)
	{
		//	QString cntCol = QString::number(cnt);
		//	QTableWidgetItem* temp = new QTableWidgetItem(cntCol);
		int rowcnt = ui.flour_dish_table->rowCount();
		ui.flour_dish_table->insertRow(rowcnt);
		ui.flour_dish_table->setItem(rowcnt, 0, new QTableWidgetItem(QString::fromStdString(i->second.GetName())));
		ui.flour_dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(i->second.GetIngredients())));
		ui.flour_dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceRestaurant())));
		ui.flour_dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceFloor())));
		ui.flour_dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceWindow())));
		ui.flour_dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(i->second.GetPrice())));
		ui.flour_dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraOne())));
		ui.flour_dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraTwo())));

	}
	for (auto i = halal_dishs.begin(); i != halal_dishs.end(); ++i)
	{
		//	QString cntCol = QString::number(cnt);
		//	QTableWidgetItem* temp = new QTableWidgetItem(cntCol);
		int rowcnt = ui.halal_dish_table->rowCount();
		ui.halal_dish_table->insertRow(rowcnt);
		ui.halal_dish_table->setItem(rowcnt, 0, new QTableWidgetItem(QString::fromStdString(i->second.GetName())));
		ui.halal_dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(i->second.GetIngredients())));
		ui.halal_dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceRestaurant())));
		ui.halal_dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceFloor())));
		ui.halal_dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceWindow())));
		ui.halal_dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(i->second.GetPrice())));
		ui.halal_dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraOne())));
		ui.halal_dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraTwo())));

	}
}


void ShowTable::closeEvent(QCloseEvent* e)
{
	Log(System::student_and_teacher.GetUsername(), "Stop checking out the dishes");
	Log("SYSTEM", "Close the show_table window");
	e->accept();
	delete(this);
}


ShowTable::~ShowTable()
{

}

void ShowTable::on_search_push_button_clicked()
{
	
	if (!ui.checkBox->isChecked())
	{
		while (ui.fired_dish_table->rowCount() > 0)
		{
			ui.fired_dish_table->removeRow(0);
		}
		while (ui.flour_dish_table->rowCount() > 0)
		{
			ui.flour_dish_table->removeRow(0);
		}
		while (ui.halal_dish_table->rowCount() > 0)
		{
			ui.halal_dish_table->removeRow(0);
		}
	}
	std::string tem_string = ui.search_what->text().toStdString();


	if (fired_dishs.count(tem_string) == 0 && flour_dishs.count(tem_string) == 0 && halal_dishs.count(tem_string) == 0) 
	{
		Log(System::student_and_teacher.GetUsername(), "Tried to search the dish:" + tem_string + ",filed");
		QMessageBox::information(this, "搜索完成", QString::fromStdString("不存在菜色“" + tem_string + "”"), QMessageBox::Yes, QMessageBox::Yes);
		return;
	}
	Log(System::student_and_teacher.GetUsername(), "Tried to search the dish:" + tem_string + ",successed");

	if (fired_dishs.count(tem_string))
	{
		int rowcnt = ui.fired_dish_table->rowCount();
		ui.fired_dish_table->insertRow(rowcnt);
		ui.fired_dish_table->setItem(rowcnt, 0, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetName())));
		ui.fired_dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetIngredients())));
		ui.fired_dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetPlaceRestaurant())));
		ui.fired_dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetPlaceFloor())));
		ui.fired_dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetPlaceWindow())));
		ui.fired_dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetPrice())));
		ui.fired_dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetExtraOne())));
		ui.fired_dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetExtraTwo())));
	}
	if (flour_dishs.count(tem_string))
	{
		int rowcnt = ui.flour_dish_table->rowCount();
		ui.flour_dish_table->insertRow(rowcnt);
		ui.flour_dish_table->setItem(rowcnt, 0, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetName())));
		ui.flour_dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetIngredients())));
		ui.flour_dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetPlaceRestaurant())));
		ui.flour_dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetPlaceFloor())));
		ui.flour_dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetPlaceWindow())));
		ui.flour_dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetPrice())));
		ui.flour_dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetExtraOne())));
		ui.flour_dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetExtraTwo())));
	}
	if (halal_dishs.count(tem_string))
	{
		int rowcnt = ui.halal_dish_table->rowCount();
		ui.halal_dish_table->insertRow(rowcnt);
		ui.halal_dish_table->setItem(rowcnt, 0, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetName())));
		ui.halal_dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetIngredients())));
		ui.halal_dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetPlaceRestaurant())));
		ui.halal_dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetPlaceFloor())));
		ui.halal_dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetPlaceWindow())));
		ui.halal_dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetPrice())));
		ui.halal_dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetExtraOne())));
		ui.halal_dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetExtraTwo())));
	}
}