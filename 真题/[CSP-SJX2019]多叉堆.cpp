#include <cstdio>
typedef long long ll;
ll mod = 1000000007;
int n = 0, q = 0;
int fa[300010], siz[300010];
ll val[300010];
ll fac[300010], facinv[300010];
ll pow(ll x, int a) {
	ll ans = 1;
	while (a) {
		if (a & 1) ans = ans * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return ans;
}
inline void init() {
	for (int i = 0; i != n; ++i) {
		fa[i] = i;
		siz[i] = val[i] = 1;
	}
	fac[0] = facinv[0] = 1;
	for (int i = 1; i <= n; ++i)
		fac[i] = fac[i - 1] * i % mod;
	facinv[n] = pow(fac[n], mod - 2);
	for (int i = n - 1; i >= 1; --i)
		facinv[i] = facinv[i + 1] * (i + 1ll) % mod;
}
inline ll Combine(int a, int b) {
	return fac[b] * facinv[a] % mod * facinv[b - a] % mod;
}
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) {
	x = find(x); y = find(y);
	val[y] = val[y] * val[x] % mod * Combine(siz[x], siz[x] + siz[y] - 1) % mod;
	siz[y] += siz[x];
	fa[x] = y;
}
int main() {
	scanf("%d%d", &n, &q);
	init();
	ll ans = 0;
	int opt = 0, x = 0, y = 0;
	for (int i = 0; i != q; ++i) {
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d%d", &x, &y);
			x = (x + ans) % n;
			y = (y + ans) % n;
			merge(x, y);
		}
		else {
			scanf("%d", &x);
			x = find((x + ans) % n);
			ans = val[x];
			printf("%lld\n", ans);
		}
	}
	return 0;
}