#ifndef FLOUR_H
#define FLOUR_H
#include"dish.h"
#include<map>
#include<string>
#include<vector>
class FlourDish :
	public Dish
{
public:
	FlourDish(Dish dish, std::string tasty, std::string extra);
	std::string GetExtraOne() { return tasty; };
	std::string GetExtraTwo() { return extra; };
private:
	std::string tasty;									//口味
	std::string extra;									//加料
};

extern std::map<std::string, FlourDish> flour_dishs;			//粉面集合
extern std::map<int, std::string> tasties;						//口味集合
extern std::map<int, std::string> extras;						//加料集合




#endif