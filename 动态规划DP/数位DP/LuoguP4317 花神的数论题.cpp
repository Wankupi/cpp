#include <cstdio>
typedef long long ll;
const ll mod = 10000007;
ll n = 0, f[70];
ll pow(ll x, ll a) {
	ll ret = 1;
	while (a) {
		if (a & 1) ret = ret * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return ret;
}
int main() {
	scanf("%lld", &n);
	int c = 0;
	for (int j = 50; j >= 0; --j) {
		for (int i = 50; i; --i)
			f[i] += f[i - 1];
		if ((n >> j) & 1) ++f[c++];
	}
	++f[c];
	ll ans = 1;
	for (int i = 1; i <= 50; ++i)
		ans = ans * pow(i, f[i]) % mod;
	printf("%lld", ans);
	return 0;
}