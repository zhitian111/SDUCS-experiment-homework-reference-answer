#ifndef HALAL_DISH_H
#define HALAL_DISH_H
#include"dish.h"
#include<map>
#include<string>
class HalalDish
	:public Dish
{
public:
	HalalDish(Dish dish, std::string cuisine, std::string meaty) ;
	std::string GetExtraOne() { return cuisine; };
	std::string GetExtraTwo() { return meaty; };
private:
	std::string cuisine;					//菜系
	std::string meaty;						//荤素
};


extern std::map<std::string, HalalDish> halal_dishs;					//清真菜集合
extern std::map<int, std::string> halal_cuisines;						//清真菜系集合






#endif