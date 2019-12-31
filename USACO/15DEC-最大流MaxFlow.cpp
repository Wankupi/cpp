#include <cstdio>
int n = 0, k = 0;
int head[100001], nxt[200001], to[200001], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int fa[100001], deep[100001], siz[100001], son[100001], top[100001], dfn[100001], cc = 0;
void dfs1(int x, int f) {
	fa[x] = f; deep[x] = deep[f] + 1;
	siz[x] = 1;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs1(to[i], x);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
		}
}
void dfs2(int x, int t) {
	dfn[x] = ++cc;
	top[x] = t;
	if (son[x]) dfs2(son[x], t);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x] && to[i] != son[x])
			dfs2(to[i], to[i]);
}
int d[100005];
void way(int x, int y) {
	while (top[x] != top[y]) {
		if (deep[top[x]] < deep[top[y]])
			x ^= y ^= x ^= y;
		d[dfn[top[x]]]++; d[dfn[x] + 1]--;
		x = fa[top[x]];
	}
	if (deep[x] < deep[y])
		x ^= y ^= x ^= y;
	d[dfn[y]]++; d[dfn[x] + 1]--;
}
int main() {
	scanf("%d%d", &n, &k);
	int u = 0, e = 0;
	for (int i = 1; i != n; ++i) {
		scanf("%d%d", &u, &e);
		insert(e, u);
		insert(u, e);
	}
	dfs1(1, 1); dfs2(1, 1);
	for (int i = 1; i <= k; ++i) {
		scanf("%d%d", &u, &e);
		way(u, e);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		d[i] += d[i - 1];
		if (d[i] > ans) ans = d[i];
	}
	printf("%d", ans);
	return 0;
}