#include <cstdio>
#include <cstring>
typedef long long ll;
int n = 0, k = 0;
int head[2001], nxt[4003], to[4003], cnt = 0;
ll  val[4003];
inline void insert(int u, int e, ll v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int siz[2003];
ll f[2003][2003];
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }
inline ll max(ll a, ll b) { return a < b ? b : a; }
void dfs(int x, int fa) {
	siz[x] = 1;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa) {
			dfs(to[i], x);
			siz[x] += siz[to[i]];
			for (int j = min(k, siz[x]); j >= 0; --j) {
				for (int p = max(0, j - siz[x] + siz[to[i]]); p <= min(j, siz[to[i]]); ++p)
					f[x][j] = max(f[x][j], f[x][j - p] + f[to[i]][p] + val[i] * (((long long)k - p) * p + ((long long)n - k - siz[to[i]] + p) * ((long long)siz[to[i]] - p)));
			}
		}
}
int main() {
	scanf("%d%d", &n, &k);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		insert(x, y, z);
		insert(y, x, z);
	}
	dfs(1, 1);
	printf("%lld", f[1][k]);
	return 0;
}