#include <cstdio>
#include <algorithm>
typedef long long ll;
ll const mod = 1000000007;
int n = 0, k = 0;
int a[503];
ll fact[1000003], inv[1000003];
ll pow(ll x, ll b) { ll ret = 1; while (b) { if (b & 1) ret = ret * x % mod; x = x * x % mod; b >>= 1; } return ret; }
void init() {
	fact[0] = 1;
	for (int i = 1; i <= 1000000; ++i) fact[i] = fact[i - 1] * i % mod;
	inv[1000000] = pow(fact[1000000], mod - 2);
	for (int i = 1000000; i >= 1; --i) inv[i - 1] = inv[i] * i % mod;
}
inline ll binom(int A, int B) { if (B > A) return 0; return fact[A] * inv[B] % mod * inv[A - B] % mod; }
int ch[503][2], siz[503];
int st[503], top = 0;
int root = 0;
ll f[503][503], g[503][503];
void dfs(int x, int t) {
	f[x][0] = 1, siz[x] = 1;
	for (int i = 0; i < 2; ++i) {
		if (ch[x][i]) {
			dfs(ch[x][i], a[x]);
			siz[x] += siz[ch[x][i]];
			for (int j = std::min(siz[x], k); ~j; --j)
				for (int l = 1; l <= std::min(siz[ch[x][i]], j); ++l)
					f[x][j] = (f[x][j] + 1ll * f[ch[x][i]][l] * f[x][j - l] % mod) % mod;
		}
	}
	for (int i = std::min(siz[x], k); ~i; --i) {
		for (int j = 1; j <= std::min(a[x] - t, i); ++j) {
			f[x][i] = (f[x][i] + 1ll * f[x][i - j] * fact[j] % mod * binom(a[x] - t, j) % mod * binom(siz[x] - (i - j), j) % mod) % mod;
		}
	}
}
int main() {
	init();
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	int cur = 0;
	for (int i = 1; i <= n; ++i) {
		cur = top;
		while (cur && a[i] < a[st[cur]]) --cur;
		if (cur) ch[st[cur]][1] = i;
		if (cur < top) ch[i][0] = st[cur + 1];
		st[++cur] = i;
		top = cur;
	}
	root = st[1];
	f[0][0] = 1;
	dfs(root, 0);
	printf("%lld", f[root][k]);
	return 0;
}