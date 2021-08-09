#include <cstdio>
typedef long long ll;
ll const mod = 998244353;

long long n = 0;
int k = 0;

inline ll pow(ll x, ll b) {
	ll r = 1;
	b %= (mod - 1);
	while (b) {
		if (b & 1) r = r * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return r;
}

int main() {
	scanf("%lld %d", &n, &k);
	ll ans = 0;
	ll w1 = pow(3, (mod - 1) / k);
	ll w = 1;
	for (int i = 0; i < k; ++i) {
		ans = (ans + pow(w + 1, n)) % mod;
		w = w * w1 % mod;
	}
	ans = ans * pow(k, mod - 2) % mod;
	printf("%lld", ans);
	return 0;
}