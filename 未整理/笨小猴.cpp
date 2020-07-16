#include <iostream>
#include <string>
using namespace std;
int t[26];
int min()
{
	int ret = 0x7fff;
	for (int i = 0; i != 26; ++i)
			if (t[i] != 0 && t[i] < ret)
			ret = t[i];
	return ret;
}
int max()
{
	int ret = 0;
	for (int i = 0; i != 26; ++i)
		if (t[i] > ret)
			ret = t[i];
	return ret;
}
bool pd(int x)
{
	if (x == 1 || x == 0)
		return false;
	if (x == 2)
		return true;
	if (x % 2 == 0)
		return false;
	for (int i = 3; i * i < x; ++i)
		if (x % i == 0)
			return false;
	return true;
}
int main()
{
	string str;
	getline(cin, str);
	for (int i = 0; i != str.size(); ++i)
		++t[str[i] - 'a'];
	int a = max() - min();
	if (pd(a))
		cout << "Lucky Word" << endl
			 << a;
	else
		cout << "No Answer\n"
				"0";
	return 0;
}