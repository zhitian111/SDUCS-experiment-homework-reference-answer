#ifndef DISH_H
#define DISH_H
#include<string>
#include<vector>
#include<map>
#include"place.h"


class Dish
{
public:

	explicit Dish(std::string name, std::string ingredients, Place place, std::string price);
	~Dish() {};
	std::string GetName() { return name; };
	std::string GetPrice() { return price; };
	std::string GetIngredients() { return ingredients; };
	std::string GetPlaceRestaurant() { return place.GetRestaurant(); };
	std::string GetPlaceFloor() { return place.GetFloor(); };
	std::string GetPlaceWindow() { return place.GetWindow(); };
	std::string GetPlace() { return GetPlaceRestaurant() + "、" + GetPlaceFloor() + "、" + GetPlaceWindow(); };
	void AppComment(std::string comment) { this_comments.push_back(comment); };
	std::vector<std::string>& GetComments() { return this_comments; };
	std::vector<std::string> this_comments;					//反馈

protected:

	std::string tag;										//菜品分类
	std::string price;										//价格
	std::string name;										//菜名
	std::string ingredients;								//食材
	Place place;											//位置

};




void IniComments();
void OutPutComments();

#endif // !_DISH_H_
