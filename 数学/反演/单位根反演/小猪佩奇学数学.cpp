#include <cstdio>
using namespace std;
typedef long long ll;
ll const mod = 998244353;
inline ll pls(ll a, ll b) { return a + b < mod ? a + b : a + b - mod; }
inline ll dec(ll a, ll b) { return a >= b ? a - b : a - b + mod; }
inline ll pow(ll x, ll b) {
	ll r = 1;
	while (b) {
		if (b & 1) r = r * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return r;
}


int main() {
	int n = 0, p = 0, k = 0;
	scanf("%d %d %d", &n, &p, &k);
	ll p1n = pow(p + 1, n);
	ll ans = pls(pow(p + 1, n - 1) * n % mod * p % mod, p1n);
	ll w1 = pow(3, (mod - 1) / k), wi = 1;
	ll invk = pow(k, mod - 2);
	for (int i = 1; i <= k; ++i) {
		wi = wi * w1 % mod;
		ll a = pow(wi - 1, mod - 2) * dec(wi * pow(p * wi % mod + 1, n) % mod, p1n) % mod;
		ans = pls(ans, a % mod);
	}
	ans = dec(invk * ans % mod, p1n);
	printf("%lld\n", ans);
	return 0;
}