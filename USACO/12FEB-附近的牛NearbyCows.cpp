#include <cstdio>
int n = 0, k = 0;
int head[100001], nxt[200005], to[200005], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int a[100001];
int f[100001][21], ans[100001];
void dfs(int x, int fa) {
	f[x][0] = a[x];
	for (int i = head[x]; i; i = nxt[i]) {
		if (to[i] != fa) {
			dfs(to[i], x);
			for (int j = 1; j <= k; ++j)
				f[x][j] += f[to[i]][j - 1];
		}
	}
}
void add(int x, int y) {
	for (int j = 1; j <= k; ++j) {
		f[x][j] += f[y][j - 1];
	}
}
void down(int x, int y) {
	for (int j = 1; j <= k; ++j) {
		f[x][j] -= f[y][j - 1];
	}
}
void dfs2(int x, int fa) {
	for (int j = 0; j <= k; ++j)
		ans[x] += f[x][j];
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa) {
			down(x, to[i]); add(to[i], x);
			dfs2(to[i], x);
			down(to[i], x); add(x, to[i]);
		}
}
int main() {
	scanf("%d%d", &n, &k);
	int x = 0, y = 0;
	for (int i = 1; i != n; ++i) {
		scanf("%d%d", &x, &y);
		insert(x, y); insert(y, x);
	}
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	dfs(1, 0); dfs2(1, 0);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}