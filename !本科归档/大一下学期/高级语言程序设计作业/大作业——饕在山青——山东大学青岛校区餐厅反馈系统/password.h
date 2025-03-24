#ifndef PASSWORD_H
#define PASSWORD_H
#include<string>
extern std::string PublicKey(std::string _key);

class Password
{
protected:
	std::string password;
	std::string private_key;
public:
	Password(std::string password) :password(PublicKey(password)),private_key(password) {};
	std::string GetPassword() { return password; };
	std::string GetPrivateKey() { return private_key; };
	void ResetPassword(std::string password) { this->password = PublicKey(password); this->private_key = password; };

};









#endif // !_PASSWORD_H_
