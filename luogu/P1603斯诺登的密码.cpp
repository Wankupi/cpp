#include <iostream>
#include <string>
using namespace std;
int cnt[101];
string fun(int x) {
	string ret;
	ret += (x / 10 + '0');
	ret += (x % 10 + '0');
	return ret;
}
int main() {
	string str, ans="0";
	while(cin>>str&&str!=".") {
		if(str=="one"||str=="a"||str=="first"||str=="another")	++cnt[1];
		else if (str=="two"||str=="both"||str=="second")		++cnt[4];
		else if (str=="three"||str=="third")					++cnt[9];
		else if (str=="four")		++cnt[16];
		else if (str=="five")		++cnt[25];
		else if (str=="six")		++cnt[36];
		else if (str=="seven")		++cnt[49];
		else if (str=="eight")		++cnt[64];
		else if (str=="nine")		++cnt[81];
		else if (str=="ten")		++cnt[0];
		else if (str=="eleven")		++cnt[21];
		else if (str=="twelve")		++cnt[44];
		else if (str=="thirteen")	++cnt[69];
		else if (str=="fourteen")	++cnt[96];
		else if (str=="fifteen")	++cnt[25];
		else if (str=="sixteen")	++cnt[56];
		else if (str=="seventeen")	++cnt[89];
		else if (str=="eighteen")	++cnt[18*18%100];
		else if (str=="nineteen")	++cnt[19*19%100];
		else if (str=="twenty")		++cnt[20*20%100];
	}
	bool flag = true;
	for (int i = 1;i<100; ++i){
		for (int j = 1; j <= cnt[i];++j){
			if(flag)
				ans = to_string(i), flag = false;
			else ans += fun(i);
		}
	}
	if(flag)
		cout << 0;
	else
		cout << ans;
	return 0;
}