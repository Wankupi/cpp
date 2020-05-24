#include <cstdio>
#include <cstring>
typedef long long ll;
const ll mod = 1000000007;
int n = 0;
int head[1001], nxt[2005], to[2005], val[2005], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }

int siz[1001];
ll C[1001][1001];
ll f[1001][1001], sum[1001][1001];
void clear() {
	memset(head, 0, sizeof(head));
	cnt = 0;
	memset(f, 0, sizeof(f));
}
inline ll binom(int _n, int m) { return C[_n][m]; }
inline int max(int a, int b) { return a < b ? b : a; }
void dfs(int x, int fa) {
	siz[x] = 1; f[x][1] = 1;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa) {
			dfs(to[i], x);
			if (val[i])
				for (int j = siz[x] + siz[to[i]]; j; --j) {
					ll t = 0;
					for (int k = max(1, j - siz[to[i]]); k <= siz[x] && k <= j; ++k) {
						ll A = binom(j - 1, k - 1) * binom(siz[x] + siz[to[i]] - j, siz[x] - k) % mod * f[x][k] % mod;
						t = t + (sum[to[i]][siz[to[i]]] - sum[to[i]][j - k] + mod) % mod * A % mod;
						t %= mod;
					}
					f[x][j] = t;
				}
			else
				for (int j = siz[x] + siz[to[i]]; j; --j) {
					ll t = 0;
					for (int k = 1; k <= siz[x] && k <= j; ++k) {
						ll A = binom(j - 1, k - 1) * binom(siz[x] + siz[to[i]] - j, siz[x] - k) % mod * f[x][k] % mod;
						t = t + sum[to[i]][j - k] * A % mod;
						t %= mod;
					}
					f[x][j] = t;
				}
			siz[x] += siz[to[i]];
		}
	for (int i = 1; i <= siz[x]; ++i) {
		sum[x][i] = (sum[x][i - 1] + f[x][i]) % mod;
	}
}
int main() {
	C[0][0] = 1;
	for (int i = 1; i <= 1000; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
	int T = 0;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		scanf("%d", &n);
		int x = 0, y = 0, opt = 0;
		for (int i = 1; i < n; ++i) {
			scanf("%d", &x);
			do opt = getchar(); while (opt != '<' && opt != '>');
			scanf("%d", &y);
			insert(x, y, opt == '<');
			insert(y, x, opt != '<');
		}
		dfs(0, 0);
		ll ans = 0;
		for (int i = 1; i <= siz[0]; ++i)
			ans = (ans + f[0][i]) % mod;
		printf("%lld\n", ans);
		if (t != T) clear();
	}
	return 0;
}