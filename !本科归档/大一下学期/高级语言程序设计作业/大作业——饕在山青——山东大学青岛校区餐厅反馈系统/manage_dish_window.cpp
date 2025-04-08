#include"manage_dish_window.h"
#include"system.h"
#include"log.h"

ManageDishWindow::ManageDishWindow(QWidget* parent)
	:QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("菜品管理");
	setWindowModality(Qt::ApplicationModal);

	connect(ui.app_dish, &QAction::triggered, this, &ManageDishWindow::on_add_action_triggered);
	connect(ui.delete_dish, &QAction::triggered, this, &ManageDishWindow::on_delete_action_triggered);
	connect(ui.search_button, &QPushButton::click, this, &ManageDishWindow::on_search_button_clicked);
	ui.dish_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.dish_table->setColumnCount(9);
	IniTable();
	Log("SYSTEM", "Open the dishes manage window");
	Log(System::admin.GetUsername(), "Start managing the dishes");
	System::manage_dish_window = this;

}

void ManageDishWindow::IniTable()
{
	ui.dish_table->clear();

	QStringList head;
	head << "菜品类" << "菜品名" << "食材" << "餐厅" << "楼层" << "窗口" << "价格" << "额外属性1" << "额外属性2";
	ui.dish_table->setHorizontalHeaderLabels(head);
	while (ui.dish_table->rowCount() > 0)
	{
		ui.dish_table->removeRow(0);
	}
	for (auto i = fired_dishs.begin(); i != fired_dishs.end(); ++i)
	{
		//	QString cntCol = QString::number(cnt);
		//	QTableWidgetItem* temp = new QTableWidgetItem(cntCol);
		int rowcnt = ui.dish_table->rowCount();
		ui.dish_table->insertRow(rowcnt);
		ui.dish_table->setItem(rowcnt, 0, new QTableWidgetItem("炒菜类"));
		ui.dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(i->second.GetName())));
		ui.dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(i->second.GetIngredients())));
		ui.dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceRestaurant())));
		ui.dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceFloor())));
		ui.dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceWindow())));
		ui.dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(i->second.GetPrice())));
		ui.dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraOne())));
		ui.dish_table->setItem(rowcnt, 8, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraTwo())));

	}
	{
		int rowcnt = ui.dish_table->rowCount();
		ui.dish_table->insertRow(rowcnt);
		ui.dish_table->setItem(rowcnt, 0, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 1, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 2, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 3, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 4, new QTableWidgetItem("类别分隔线"));
		ui.dish_table->setItem(rowcnt, 5, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 6, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 7, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 8, new QTableWidgetItem("--------"));
	}
	for (auto i = flour_dishs.begin(); i != flour_dishs.end(); ++i)
	{
		//	QString cntCol = QString::number(cnt);
		//	QTableWidgetItem* temp = new QTableWidgetItem(cntCol);
		int rowcnt = ui.dish_table->rowCount();
		ui.dish_table->insertRow(rowcnt);
		ui.dish_table->setItem(rowcnt, 0, new QTableWidgetItem("粉面类"));
		ui.dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(i->second.GetName())));
		ui.dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(i->second.GetIngredients())));
		ui.dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceRestaurant())));
		ui.dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceFloor())));
		ui.dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceWindow())));
		ui.dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(i->second.GetPrice())));
		ui.dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraOne())));
		ui.dish_table->setItem(rowcnt, 8, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraTwo())));

	}
	{
		int rowcnt = ui.dish_table->rowCount();
		ui.dish_table->insertRow(rowcnt);
		ui.dish_table->setItem(rowcnt, 0, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 1, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 2, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 3, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 4, new QTableWidgetItem("类别分隔线"));
		ui.dish_table->setItem(rowcnt, 5, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 6, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 7, new QTableWidgetItem("--------"));
		ui.dish_table->setItem(rowcnt, 8, new QTableWidgetItem("--------"));
	}
	for (auto i = halal_dishs.begin(); i != halal_dishs.end(); ++i)
	{
		//	QString cntCol = QString::number(cnt);
		//	QTableWidgetItem* temp = new QTableWidgetItem(cntCol);
		int rowcnt = ui.dish_table->rowCount();
		ui.dish_table->insertRow(rowcnt);
		ui.dish_table->setItem(rowcnt, 0, new QTableWidgetItem("清真类"));
		ui.dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(i->second.GetName())));
		ui.dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(i->second.GetIngredients())));
		ui.dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceRestaurant())));
		ui.dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceFloor())));
		ui.dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(i->second.GetPlaceWindow())));
		ui.dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(i->second.GetPrice())));
		ui.dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraOne())));
		ui.dish_table->setItem(rowcnt, 8, new QTableWidgetItem(QString::fromStdString(i->second.GetExtraTwo())));

	}
}
ManageDishWindow::~ManageDishWindow()
{

}
void ManageDishWindow::on_add_action_triggered()
{
	AddDishWindow* tem = new AddDishWindow(this);
	tem->show();

}
void ManageDishWindow::on_delete_action_triggered()
{
	QList<QTableWidgetItem*> selectedItems = ui.dish_table->selectedItems();
	if (selectedItems.isEmpty())
	{
		QMessageBox::information(this, "删除失败", "请先选中要删除的菜品", QMessageBox::Ok);
		Log(System::admin.GetUsername(), "Tried to delete dish,failed");
		return;
	}
	int a = selectedItems.first()->row();
	foreach(QTableWidgetItem* var,selectedItems)
	{
		if (a != var->row())
		{
			QMessageBox::information(this, "删除失败", "请选择单行进行操作", QMessageBox::Ok);
			Log(System::admin.GetUsername(), "Tried to delete dish,failed");

			return;
		}
	}
	QTableWidgetItem* tem_class = ui.dish_table->item(a, 0);
	QTableWidgetItem* tem_name = ui.dish_table->item(a,1);
	std::string tem_string_1 = tem_class->text().toStdString();
	std::string tem_string_2 = tem_name->text().toStdString();
	if (fired_dishs.count(tem_string_2) == 0 && flour_dishs.count(tem_string_2) == 0 && halal_dishs.count(tem_string_2) == 0)
	{
		QMessageBox::information(this, "删除失败", "请选择菜品行进行操作", QMessageBox::Ok);
		Log(System::admin.GetUsername(), "Tried to delete dish,failed");

		return;
	}
	
	QMessageBox::StandardButton box;
	box = QMessageBox::question(this, "确认删除", QString::fromStdString("确认要删除该菜品吗？\n菜品信息:" + tem_string_1 + " " + tem_string_2), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	if (box != QMessageBox::Yes)
	{
		return;
	}
	if (tem_string_1 == "炒菜类")
	{
		fired_dishs.erase(tem_string_2);
	}
	if (tem_string_1 == "粉面类")
	{
		flour_dishs.erase(tem_string_2);
	}
	if (tem_string_1 == "清真类")
	{
		halal_dishs.erase(tem_string_2);
	}
	System::dishes_whether_changed = true;
	System::comment_whether_changed = true;
	Log(System::admin.GetUsername(), "Tried to delete dish,successed,dish information:"+tem_string_1+" "+tem_string_2);
	this->IniTable();
}

void ManageDishWindow::on_search_button_clicked()
{
	std::string tem_string = ui.seach_what->text().toStdString();
	ui.dish_table->clear();
	QStringList head;
	head << "菜品类" << "菜品名" << "食材" << "餐厅" << "楼层" << "窗口" << "价格" << "额外属性1" << "额外属性2";
	ui.dish_table->setHorizontalHeaderLabels(head);
	while (ui.dish_table->rowCount() > 0)
	{
		ui.dish_table->removeRow(0);
	}
	if (fired_dishs.count(tem_string) == 0 && flour_dishs.count(tem_string) == 0 && halal_dishs.count(tem_string) == 0)
	{
		Log(System::admin.GetUsername(), "Tried to search the dish:" + tem_string + ",filed");
		QMessageBox::information(this, "搜索完成", QString::fromStdString("不存在菜色“" + tem_string + "”"), QMessageBox::Yes, QMessageBox::Yes);
		IniTable();
		return;
	}
	Log(System::admin.GetUsername(), "Tried to search the dish:" + tem_string + ",successed");
	
	if (fired_dishs.count(tem_string))
	{
		int rowcnt = ui.dish_table->rowCount();
		ui.dish_table->insertRow(rowcnt);
		ui.dish_table->setItem(rowcnt, 0, new QTableWidgetItem("炒菜类"));
		ui.dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetName())));
		ui.dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetIngredients())));
		ui.dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetPlaceRestaurant())));
		ui.dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetPlaceFloor())));
		ui.dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetPlaceWindow())));
		ui.dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetPrice())));
		ui.dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetExtraOne())));
		ui.dish_table->setItem(rowcnt, 8, new QTableWidgetItem(QString::fromStdString(fired_dishs.at(tem_string).GetExtraTwo())));
	}
	if (flour_dishs.count(tem_string))
	{
		int rowcnt = ui.dish_table->rowCount();
		ui.dish_table->insertRow(rowcnt);
		ui.dish_table->setItem(rowcnt, 0, new QTableWidgetItem("粉面类"));
		ui.dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetName())));
		ui.dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetIngredients())));
		ui.dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetPlaceRestaurant())));
		ui.dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetPlaceFloor())));
		ui.dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetPlaceWindow())));
		ui.dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetPrice())));
		ui.dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetExtraOne())));
		ui.dish_table->setItem(rowcnt, 8, new QTableWidgetItem(QString::fromStdString(flour_dishs.at(tem_string).GetExtraTwo())));
	}
	if (halal_dishs.count(tem_string))
	{
		int rowcnt = ui.dish_table->rowCount();
		ui.dish_table->insertRow(rowcnt);
		ui.dish_table->setItem(rowcnt, 0, new QTableWidgetItem("清真类"));
		ui.dish_table->setItem(rowcnt, 1, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetName())));
		ui.dish_table->setItem(rowcnt, 2, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetIngredients())));
		ui.dish_table->setItem(rowcnt, 3, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetPlaceRestaurant())));
		ui.dish_table->setItem(rowcnt, 4, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetPlaceFloor())));
		ui.dish_table->setItem(rowcnt, 5, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetPlaceWindow())));
		ui.dish_table->setItem(rowcnt, 6, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetPrice())));
		ui.dish_table->setItem(rowcnt, 7, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetExtraOne())));
		ui.dish_table->setItem(rowcnt, 8, new QTableWidgetItem(QString::fromStdString(halal_dishs.at(tem_string).GetExtraTwo())));
	}
}

void ManageDishWindow::closeEvent(QCloseEvent* e)
{
	Log("SYSTEM", "Close the dishes manage window");
	Log(System::admin.GetUsername(), "Stop managing the dishes");
	e->accept();
	delete(this);
}

AddDishWindow::AddDishWindow(QWidget* parent)
	:QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowModality(Qt::ApplicationModal);
	connect(ui.pushButton, &QPushButton::click, this, &AddDishWindow::on_pushButton_clicked);
	connect(ui.pushButton_2, &QPushButton::click, this, &AddDishWindow::on_pushButton_2_clicked);
	setWindowTitle("添加菜品");
}
AddDishWindow::~AddDishWindow()
{

}

void AddDishWindow::on_pushButton_2_clicked()
{
	this->close();
}
void AddDishWindow::on_pushButton_clicked()
{
	std::string tem_string_1 = ui.lineEdit->text().toStdString();
	std::string tem_string_2 = ui.lineEdit_2->text().toStdString();
	std::string tem_string_3 = ui.lineEdit_3->text().toStdString();
	std::string tem_string_4 = ui.lineEdit_4->text().toStdString();
	std::string tem_string_5 = ui.lineEdit_5->text().toStdString();
	std::string tem_string_6 = ui.lineEdit_6->text().toStdString();
	std::string tem_string_7 = ui.lineEdit_7->text().toStdString();
	std::string tem_string_8 = ui.lineEdit_8->text().toStdString();
	std::string tem_string_9 = ui.lineEdit_9->text().toStdString();
	if (tem_string_1 == "" || tem_string_2 == "" || tem_string_3 == "" || tem_string_4 == "" || tem_string_5 == "" || tem_string_6 == "" || tem_string_7 == "" || tem_string_8 == "" || tem_string_9 == "")
	{
		QMessageBox::information(this, "添加失败", "请输入完整信息", QMessageBox::Ok);
		Log(System::admin.GetUsername(), "Tried to add new dish,failed");
		return;
	}
	if (tem_string_1 != "炒菜类" && tem_string_1 != "粉面类" && tem_string_1 != "清真类")
	{
		QMessageBox::information(this, "添加失败", "请填写正确的菜品类别", QMessageBox::Ok);
		Log(System::admin.GetUsername(), "Tried to add new dish,failed");
		return;
	}
	Place tem_place(tem_string_4,tem_string_5,tem_string_6);
	Dish tem_dish(tem_string_2, tem_string_3, tem_place, tem_string_7);
	if (tem_string_1 == "炒菜类")
	{
		if (flour_dishs.count(tem_string_2) > 0)
		{
			QMessageBox::information(this, "添加失败", "该菜品已存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			Log(System::admin.GetUsername(), "Tried to add new dish,failed");
			return;
		}
		FiredDish tem_fired_dish(tem_dish, tem_string_8, tem_string_9);
		dishes_names.push_back(tem_string_2);
	}
	if (tem_string_1 == "粉面类")
	{
		if (fired_dishs.count(tem_string_2) > 0)
		{
			QMessageBox::information(this, "添加失败", "该菜品已存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			Log(System::admin.GetUsername(), "Tried to add new dish,failed");

			return;
		}
		FlourDish tem_FlorDish(tem_dish, tem_string_8, tem_string_9);
		dishes_names.push_back(tem_string_2);
	}
	if (tem_string_1 == "清真类")
	{
		if (halal_dishs.count(tem_string_2) > 0)
		{
			QMessageBox::information(this, "添加失败", "该菜品已存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			Log(System::admin.GetUsername(), "Tried to add new dish,failed");
			return;
		}
		HalalDish tem_halal_dish(tem_dish, tem_string_8, tem_string_9);
		dishes_names.push_back(tem_string_2);
	}
	System::manage_dish_window->IniTable();
	QMessageBox::information(this, "添加成功", QString::fromStdString("已添加菜品：\n" + tem_string_1 + " " + tem_string_2 + " " + tem_string_3 + " " + tem_string_4 + "、" + tem_string_5 + "楼、" + tem_string_6 + "窗口 " + tem_string_7 + "元 " + tem_string_8 + " " + tem_string_9), QMessageBox::Ok);
	System::dishes_whether_changed = true;
	Log(System::admin.GetUsername(), "Tried to add new dish,successed,dish information:" + tem_string_1 + " " + tem_string_2 + " " + tem_string_3 + " " + tem_string_4 + "、" + tem_string_5 + "、" + tem_string_6 + " " + tem_string_7 + " " + tem_string_8 + " " + tem_string_9);
	this->close();
}
void AddDishWindow::closeEvent(QCloseEvent* e)
{
	e->accept();
	delete(this);
}