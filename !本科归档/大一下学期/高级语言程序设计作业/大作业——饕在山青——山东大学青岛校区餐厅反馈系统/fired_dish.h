#ifndef FIRED_DISH_H
#define FIRED_DISH_H
#include"dish.h"
#include<map>
#include<string>
class FiredDish:
	public Dish
{
public:
	FiredDish(Dish dish, std::string cuisine,std::string meaty);
	std::string GetExtraOne() { return cuisine; };
	std::string GetExtraTwo() { return meaty; };
private:
	std::string cuisine;						//菜系
	std::string	meaty;							//荤素
};


extern std::map<std::string, FiredDish> fired_dishs;			//炒菜集合
extern std::map<int, std::string> cuisines;						//菜系集合







#endif