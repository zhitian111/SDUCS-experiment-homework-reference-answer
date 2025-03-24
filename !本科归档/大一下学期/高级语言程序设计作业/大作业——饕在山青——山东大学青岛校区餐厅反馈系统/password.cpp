#include"password.h"
std::string PublicKey(std::string _key)		//公钥函数，用于生成密码对应的散列值
{
	int _sum = 0;
	for (int i = 0; i < _key.size(); i++)
	{
		if (_key[i] > '5')
		{
			_sum += _key[i];
			_key[i] = '0' + _sum;
		}
		else
		{
			_key[i] = '1' + _sum;
		}
	}
	for (int i = 0; i < _key.size(); i++)
	{
		_key[i] += _sum;
	}
	return _key;
}
