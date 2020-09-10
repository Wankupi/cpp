#include <cstdio>
typedef long long ll;
const ll mod = 998244353;
int n = 0;
ll k = 0, x[2001], y[2001];
ll mutiL[2010], mutiR[2010];
ll row(ll x, ll a) {
	ll ans = 1;
	while (a) {
		if (a & 1) ans = (ans * x) % mod;
		x = (x * x) % mod;
		a >>= 1;
	}
	return ans;
}
int main() {
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%lld%lld", x + i, y + i);
	mutiL[0] = mutiL[n + 1] = mutiR[0] = mutiR[n + 1] = 1;
	for (int i = 1; i <= n; ++i)
		mutiL[i] = (mutiL[i - 1] * (k - x[i])) % mod;
	for (int i = n; i >= 1; --i)
		mutiR[i] = (mutiR[i + 1] * (k - x[i])) % mod;
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		ll mu = 1;
		for (int j = 1; j <= n; ++j)
			if (i != j)
				mu = (mu * (x[i] - x[j])) % mod;
		if (mu < 0) mu += mod;
		mu = row(mu, mod - 2);
		ans = (ans + (((y[i] * mutiL[i - 1] % mod) * mutiR[i + 1] % mod) * mu % mod)) % mod;
	}
	ans = (ans + mod) % mod;
	printf("%lld", ans);
	return 0;
}