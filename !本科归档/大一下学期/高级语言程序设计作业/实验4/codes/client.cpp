#include"client.h"

char CLIENT::ServerName = 'a';
int CLIENT::ClientNum = 0;

CLIENT::CLIENT() {
	ClientNum++;
}

void CLIENT::ChangeServerName(char a) {
	ServerName = a;
}