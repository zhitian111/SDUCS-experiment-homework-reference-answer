#include"log.h"
#include<fstream>


void Log(std::string _user,std::string _log)
{
	if (_user != "SYSTEM")
	{
		_user = "username : " + _user;
	}
	_log = "operation : " + _log;
	std::fstream temp;
	temp.open("log.txt", std::ios::out | std::ios::app);
	time_t global_current_time = time(0);
	tm local_current_time;
	localtime_s(&local_current_time,&global_current_time);
	temp << "\n[" << local_current_time.tm_year + 1900 << "-" << local_current_time.tm_mon + 1 << "-" << local_current_time.tm_mday << "-" << local_current_time.tm_hour << "-"
		<< local_current_time.tm_min << "-" << local_current_time.tm_sec << "] " << _user << " " << _log;
	temp.close();
}

void IniLog()
{
	std::fstream temp_file;
	temp_file.open("log.txt", std::ios::app | std::ios::out);
	temp_file << "\n\n";
	temp_file.close();
}