#include <cstdio>
#include <algorithm>
typedef long long ll;
ll const mod = 1000000009;
inline ll pls(ll a, ll b) { return a + b < mod ? a + b : a + b - mod; }
inline ll dec(ll a, ll b) { return a >= b ? a - b : a - b + mod; }
inline int read() {
	int x = 0, c = getchar(), f = +1;
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while ('0' <= c && c <= '9') { x = 10 * x + c - '0'; c = getchar(); }
	return f * x;
}
int n = 0, k = 0;
int a[2003], b[2003], c[2003];
ll fact[2003], ifact[2003];
ll pow(ll x, ll b) { ll r = 1; while (b) { if (b & 1) r = r * x % mod; x = x * x % mod; b >>= 1; } return r; }
ll binom(ll A, ll B) { return B < 0 || B > A ? 0 : fact[A] * ifact[B] % mod * ifact[A - B] % mod; }

void init() {
	fact[0] = 1;
	for (int i = 1; i <= 2000; ++i) fact[i] = fact[i - 1] * i % mod;
	ifact[2000] = pow(fact[2000], mod- 2);
	for (int i = 2000; i >= 1; --i) ifact[i - 1] = ifact[i] * i % mod;
}
ll g[2003];
int main() {
	// scanf("%d %d", &n, &k);
	n = read(); k = read();
	if ((n + k) & 1) { printf("0"); return 0; }
	k = (n + k) >> 1;
	init();
	for (int i = 1; i <= n; ++i) /* scanf("%d", a + i); */ a[i] = read();
	for (int i = 1; i <= n; ++i) /* scanf("%d", b + i); */ b[i] = read();
	std::sort(a + 1, a + n + 1);
	std::sort(b + 1, b + n + 1);
	for (int i = 1, j = 1; i <= n; ++i) {
		while (j <= n && b[j] < a[i]) ++j;
		c[i] = j - 1;
	}
	g[0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = c[i]; j >= 1; --j)
			g[j] = pls(g[j], g[j - 1] * (c[i] - j + 1) % mod);
	for (int j = k; j <= n; ++j) g[j] = g[j] * fact[n - j] % mod;
	ll ans = 0;
	for (int i = k; i <= n; ++i) {
		if ((i - k) & 1) ans = dec(ans, binom(i, k) * g[i] % mod);
		else ans = pls(ans, binom(i, k) * g[i] % mod);
		// ans = (ans + pow(mod - 1, i - k) * binom(i, k) % mod * g[i] % mod) % mod;
	}
	printf("%lld", ans);
	return 0;
}