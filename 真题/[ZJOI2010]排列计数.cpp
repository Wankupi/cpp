// C++ 11+
#include <iostream>
using namespace std;
using ll = long long;
ll n = 0, m = 0;
int s[1000003];
ll row(ll x, ll a) { ll ret = 1; while (a) { if (a & 1)ret = ret * x % m; x = x * x % m; a >>= 1; } return ret; }
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) s[i] = 1;
	for (int i = n; i > 1; --i) s[i / 2] += s[i];
	ll fact = 1, muti = 1;
	for (int i = 1; i <= n; ++i) {
		fact = fact * i % m;
		muti = muti * s[i] % m;
	}
	cout << fact * row(muti, m - 2) % m;
	return 0;
}
