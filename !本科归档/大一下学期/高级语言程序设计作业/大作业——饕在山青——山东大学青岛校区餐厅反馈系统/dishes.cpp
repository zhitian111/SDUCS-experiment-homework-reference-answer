#include"dishs.h"
#include<fstream>
#include<qmessagebox>
#include<qmessagebox.h>
#include"system.h"
#include"log.h"
#include"qdebug.h"
#include <iostream>

//char szUTF_8BOM[4] = { char(0xEF), char(0xBB), char(0xBF), char(0) };
Place::Place(std::string restaurant, std::string floor, std::string window) :
	restaurant(restaurant),
	floor(floor),
	window(window) {}

Place::Place(std::string place)
{
	//QMessageBox::information(NULL, "a", QString::fromStdString(place), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	wchar_t temd = '、';
	long long fmark = place.find_first_of(temd);
	restaurant = place.substr(0, fmark-2);
	//QMessageBox::information(NULL, "a", QString::fromStdString(restaurant), QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
	long long bmark = place.find_last_of(temd);
	window = place.substr(bmark + 1, place.size() - bmark - 1);
	floor = place.substr(fmark + 1, bmark - fmark - 3);
	//QMessageBox::information(NULL, "a", QString::fromStdString(floor), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}



Dish::Dish(std::string name, std::string ingredients, Place place, std::string price) :
	name(name),
	ingredients(ingredients),
	place(place),
	price(price) {}

std::vector<std::string> dishes_names;

//菜色种类
std::map<int, std::string> dish_class = { {1,"炒菜类"},{2,"粉面类"} ,{3,"清真类"} };



//粉面类
std::map<std::string, FlourDish> flour_dishs;			//粉面集合
std::map<int, std::string> tasties = {					//口味集合
	{1,"清汤"},
	{2,"番茄"},
	{3,"微辣"},
	{4,"酸辣"},
	{5,"麻辣"}
};

std::map<int, std::string> extras = {					//加料集合
	{1,"牛肉"},
	{2,"火腿肠"},
	{3,"煎蛋"},
	{4,"卤蛋"}
};


//炒菜类
std::map<std::string, FiredDish> fired_dishs;			//炒菜集合
std::map<int, std::string> cuisines = {					//菜系集合
	{0,"东北菜"},
	{1,"鲁菜"},
	{2,"川菜"},
	{3,"粤菜"},
	{4,"江苏菜"},
	{5,"闽菜"},
	{6,"浙江菜"},
	{7,"湘菜"},
	{8,"徽菜"},
};



//清真菜类
std::map<std::string, HalalDish> halal_dishs;					//清真菜集合
std::map<int, std::string> halal_cuisines = {					//清真菜系集合
	{0,"西北菜系"},
	{1,"北京菜"},
	{2,"天津菜"},
	{3,"云南菜"},
	{4,"宁夏菜"},
	{5,"青海菜"},
	{6,"陕西菜"}
};



void OutPutDishes()
{
	std::fstream tem_file;
	tem_file.open("dishes.txt", std::ios::out);
	tem_file.clear();
	for (int i = 0; i != dishes_names.size(); i++)
	{
		std::string tem_name = dishes_names[i];
		if (fired_dishs.count(tem_name) == 1)
		{
			tem_file << QString::fromUtf8("炒菜类 ").toLocal8Bit().toStdString() ;
			tem_file << QString::fromUtf8(tem_name).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(fired_dishs.at(tem_name).GetIngredients()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(fired_dishs.at(tem_name).GetPlace()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(fired_dishs.at(tem_name).GetPrice()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(fired_dishs.at(tem_name).GetExtraOne()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(fired_dishs.at(tem_name).GetExtraTwo()).toLocal8Bit().toStdString() << QString::fromUtf8("\n").toLocal8Bit().toStdString();
		}
		if (flour_dishs.count(tem_name) == 1)
		{
			tem_file << QString::fromUtf8("粉面类 ").toLocal8Bit().toStdString();

			//tem_file << tem_name << " " << flour_dishs.at(tem_name).GetIngredients() << " " << flour_dishs.at(tem_name).GetPlace() << " " << flour_dishs.at(tem_name).GetPrice() << " " << flour_dishs.at(tem_name).GetExtraOne() << " " << flour_dishs.at(tem_name).GetExtraTwo()<<"\n";
			tem_file << QString::fromUtf8(tem_name).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(flour_dishs.at(tem_name).GetIngredients()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(flour_dishs.at(tem_name).GetPlace()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(flour_dishs.at(tem_name).GetPrice()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(flour_dishs.at(tem_name).GetExtraOne()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(flour_dishs.at(tem_name).GetExtraTwo()).toLocal8Bit().toStdString() << QString::fromUtf8("\n").toLocal8Bit().toStdString();
		}
		if (halal_dishs.count(tem_name) == 1)
		{
			tem_file << QString::fromUtf8("清真类 ").toLocal8Bit().toStdString();
			//tem_file << tem_name << " " << halal_dishs.at(tem_name).GetIngredients() << " " << halal_dishs.at(tem_name).GetPlace() << " " << halal_dishs.at(tem_name).GetPrice() << " " << halal_dishs.at(tem_name).GetExtraOne() << " " << halal_dishs.at(tem_name).GetExtraTwo()<<"\n";
			tem_file << QString::fromUtf8(tem_name).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(halal_dishs.at(tem_name).GetIngredients()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(halal_dishs.at(tem_name).GetPlace()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(halal_dishs.at(tem_name).GetPrice()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(halal_dishs.at(tem_name).GetExtraOne()).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8(halal_dishs.at(tem_name).GetExtraTwo()).toLocal8Bit().toStdString() << QString::fromUtf8("\n").toLocal8Bit().toStdString();
		}
	}
	tem_file.close();
	Log("SYSTEM", "Refresh the dishes file");
}




FiredDish::FiredDish(Dish dish, std::string cuisine,std::string meaty)
	:Dish(dish), cuisine(cuisine),meaty(meaty)
{

	if (fired_dishs.count(name) == 0)
	{
		fired_dishs.insert(std::pair<std::string, FiredDish>{name, * this});
	}
}


FlourDish::FlourDish(Dish dish, std::string tasty, std::string extra)
	:Dish(dish), tasty(tasty), extra(extra)
{
	if (flour_dishs.count(name) == 0)
	{
		flour_dishs.insert(std::pair<std::string, FlourDish>{name, * this});

	}
}


HalalDish::HalalDish(Dish dish, std::string cuisine, std::string meaty)
	:Dish(dish), cuisine(cuisine), meaty(meaty)
{

	if (halal_dishs.count(name) == 0)
	{
		halal_dishs.insert(std::pair<std::string, HalalDish>{name, * this});
	}
}




void IniDishs()
{
	std::fstream tem_file;
	tem_file.open("dishes.txt", std::ios::in);
	if (!tem_file.is_open())
	{
		QMessageBox::information(NULL, "初始化失败", "食品列表初始化失败");
		return;
	}
	std::string dish_class;
	std::string dish_name;
	std::string ingredients;
	std::string place;
	std::string price;
	std::string extra1;
	std::string extra2;
	if (tem_file.is_open())
	{


		while (tem_file>>dish_class>>dish_name>>ingredients>>place>>price>>extra1>>extra2)
		{

			dish_class = QString::fromLocal8Bit(dish_class).toUtf8();
			dish_name = QString::fromLocal8Bit(dish_name).toUtf8();
			ingredients = QString::fromLocal8Bit(ingredients).toUtf8();
			place = QString::fromLocal8Bit(place).toUtf8();
			price = QString::fromLocal8Bit(price).toUtf8();
			extra1 = QString::fromLocal8Bit(extra1).toUtf8();
			extra2 = QString::fromLocal8Bit(extra2).toUtf8();
			dishes_names.push_back(dish_name);




			Place tem_place(place);
			Dish tem_dish(dish_name, ingredients, tem_place, price);
			if (dish_class == "炒菜类")
			{
				FiredDish tem_fired_dish(tem_dish,extra1,extra2);
			}
			if (dish_class == "粉面类")
			{
				FlourDish tem_FlorDish(tem_dish, extra1,extra2);
			}
			if (dish_class == "清真类")
			{
				HalalDish tem_halal_dish(tem_dish, extra1, extra2);
			}
		}
	}
	
	tem_file.close();
}




void IniComments()
{
	std::fstream tem_file;
	std::string dish_name;
	std::string text;

	tem_file.open("comments.txt", std::ios::in);


	while (tem_file >> dish_name >> text)
	{
		dish_name = QString::fromLocal8Bit(dish_name).toUtf8();
		text = QString::fromLocal8Bit(text).toUtf8();
		if (fired_dishs.count(dish_name) == 1)
		{
			fired_dishs.at(dish_name).AppComment(text.substr(9, text.size() - 3));
	//		QMessageBox::information(NULL, QString::fromStdString(dish_name), QString::fromStdString(text));

		}
		if (flour_dishs.count(dish_name) == 1)
		{
			flour_dishs.at(dish_name).AppComment(text.substr(9, text.size() - 3));
		}
		if (halal_dishs.count(dish_name) == 1)
		{
			halal_dishs.at(dish_name).AppComment(text.substr(9, text.size() - 3));
		}
	}
	//qDebug() << fired_dishs.at("番茄炒蛋").GetComments()[0];
	tem_file.close();
}

void OutPutComments()
{

	std::fstream tem_file;
	tem_file.open("comments.txt", std::ios::out);
	tem_file.clear();
	//tem_file << szUTF_8BOM;
	for (auto i = fired_dishs.begin(); i != fired_dishs.end(); i++)
	{
		if (!(*i).second.GetComments().empty())
		{
			for (int j = 0; j < (*i).second.GetComments().size(); j++)
			{
				tem_file << QString::fromUtf8((*i).first).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8("反馈：" + (*i).second.this_comments[j]).toLocal8Bit().toStdString() << QString::fromUtf8("\n").toLocal8Bit().toStdString();
			}
		}
	}
	for (auto i = halal_dishs.begin(); i != halal_dishs.end(); i++)
	{
		if (!(*i).second.GetComments().empty())
		{
			for (int j = 0; j < (*i).second.GetComments().size(); j++)
			{
				tem_file << QString::fromUtf8((*i).first).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8("反馈：" + (*i).second.this_comments[j]).toLocal8Bit().toStdString() << QString::fromUtf8("\n").toLocal8Bit().toStdString();

			}
		}
	}
	for (auto i = flour_dishs.begin(); i != flour_dishs.end(); i++)
	{
		if (!(*i).second.GetComments().empty())
		{
			for (int j = 0; j < (*i).second.GetComments().size(); j++)
			{
				tem_file << QString::fromUtf8((*i).first).toLocal8Bit().toStdString() << QString::fromUtf8(" ").toLocal8Bit().toStdString() << QString::fromUtf8("反馈：" + (*i).second.this_comments[j]).toLocal8Bit().toStdString() << QString::fromUtf8("\n").toLocal8Bit().toStdString();

			}
		}
	}
	tem_file.close();
	//std::ofstream put("comments.txt", std::ios::binary | std::ios::out);
	//std::ifstream get("new_comments.txt", std::ios::binary | std::ios::in);
	//
	//put << get.rdbuf();
	//get.close();
	//put.close();
	//remove("new_comments.txt");
}