#include <cstdio>
typedef long long ll;
int const maxn = 4007, mod = 924844033;

inline int pls(int a, int b) { return a + b < mod ? a + b : a + b - mod; }

int n = 0, k = 0;

bool ban[maxn];
int f[maxn][maxn], g[maxn][maxn];
int fact[maxn];

int main() {
	scanf("%d %d", &n, &k);
	int p = 0;
	for (int i = 1; i <= k; ++i) {
		ban[++p] = true;
		p += (n - i) / k;
		ban[++p] = true;
		p += (n - i) / k;
	}
	if (p != 2 * n) putchar('!');
	f[0][0] = 1;
	for (int i = 1; i <= p; ++i) {
		f[i][0] = 1;
		for (int j = 1; j <= (i + 1) / 2; ++j) {
			f[i][j] = pls(f[i - 1][j], g[i - 1][j]);
			g[i][j] = ban[i] ? 0 : f[i - 1][j - 1];
		}
	}
	fact[0] = 1;
	for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * ll(i) % mod;
	ll ans = 0;
	for (int i = 0; i <= n; ++i) {
		ll tem = ll(f[p][i] + g[p][i]) * fact[n - i] % mod;
		ans += (i & 1) ? -tem : +tem;
		if (ans >= mod) ans -= mod;
		if (ans < 0) ans += mod;
	}
	printf("%lld\n", ans);
	return 0;
}