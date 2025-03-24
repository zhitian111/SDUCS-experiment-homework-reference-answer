#pragma once
#ifndef IOSTREAM
#include <iostream>
#define IOSTREAM
#endif // !IOSTREAM

class CLIENT {
private:

public:
	static char ServerName;
	static int ClientNum;
	static void ChangeServerName(char a);
	CLIENT();
};