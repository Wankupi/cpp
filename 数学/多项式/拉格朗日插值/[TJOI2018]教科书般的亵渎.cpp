#include <cstdio>
#include <algorithm>

typedef long long ll;
ll const mod = 1000000007;

inline ll pls(ll a, ll b) { return a + b < mod ? a + b : a + b - mod; }
inline ll dec(ll a, ll b) { return a < b ? a - b + mod : a - b; }

inline ll pow(ll x, ll b) {
	ll r = 1;
	while (b) {
		if (b & 1) r = r * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return r;
}

int k = 0;
ll f[57];
ll pre[57], suf[57], fact[57];
void init() {
	for (int i = 1; i <= k + 2; ++i) f[i] = pls(f[i - 1], pow(i, k));
}
ll Lagrange(ll v) {
	if (v <= k + 2) return f[v];

	pre[0] = 1;
	for (int i = 1; i <= k + 2; ++i) pre[i] = pre[i - 1] * (v - i) % mod;
	suf[k + 3] = 1;
	for (int i = k + 2; i >= 1; --i) suf[i] = suf[i + 1] * (v - i) % mod;
	ll res = 0;
	for (int i = 1; i <= k + 2; ++i) {
		ll fz = pre[i - 1] * suf[i + 1] % mod;
		ll fm = fact[i - 1] * fact[k + 2 - i] % mod;
		if ((k + 2 - i) % 2 == 1) fm = mod - fm;
		res = pls(res, f[i] * fz % mod * pow(fm, mod - 2) % mod);
	}
	return res;
}

ll n = 0; int m = 0;
ll a[53];
int main() {
	fact[0] = 1;
	for (int i = 1; i <= 52; ++i) fact[i] = fact[i - 1] * i % mod;
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld %d", &n, &m);
		for (int i = 1; i <= m; ++i) scanf("%lld", a + i);
		std::sort(a + 1, a + m + 1);
		k = m + 1;
		while (a[m] == n) {
			--n; --m; --k;
		}
		init();	
		ll ans = Lagrange(n);
		for (int i = 1; i <= m; ++i) ans = pls(ans, Lagrange(n - a[i]));

		for (int i = 0; i <= m; ++i)
			for (int j = i + 1; j <= m; ++j)
				ans = dec(ans, pow(a[j] - a[i], k));
		printf("%lld\n", ans);
	}
	return 0;
}
