#ifndef PLACE_H
#define PLACE_H
#include<string>

class Place
{
public:
	explicit Place(std::string restaurant,std::string floor,std::string window);
	explicit Place(std::string place);
	std::string GetRestaurant() { return restaurant; };
	std::string GetFloor() { return floor; };
	std::string GetWindow() { return window; };
private:
	std::string restaurant;			//餐厅
	std::string	floor;				//楼层
	std::string window;				//窗口
};




#endif