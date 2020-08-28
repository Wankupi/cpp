#include <cstdio>
#include <cstring>
const int maxn = 300007;
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9')
		x = 10 * x + c - '0', c = getchar();
	return x;
}
int n = 0, m = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 0;
inline void insert(int u, int e, int v) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
	val[cnt] = v;
}
int fa[maxn], siz[maxn], dep[maxn], son[maxn], top[maxn];
int dis[maxn];
void dfs1(int x, int f) {
	fa[x] = f;
	dep[x] = dep[f] + 1;
	siz[x] = 1;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dis[to[i]] = dis[x] + val[i];
			dfs1(to[i], x);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
		}
}
void dfs2(int x, int t) {
	top[x] = t;
	if (son[x]) dfs2(son[x], t);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x] && to[i] != son[x])
			dfs2(to[i], to[i]);
}
int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] >= dep[top[y]])
			x = fa[top[x]];
		else
			y = fa[top[y]];
	}
	return dep[x] > dep[y] ? y : x;
}
int X[maxn], Y[maxn], LCA[maxn], len[maxn];
int maxLen = 0;
int d[maxn], tick = 0, maxReduce = 0;
void dfs(int x) {
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x]) {
			dfs(to[i]);
			d[x] += d[to[i]];
			if (d[to[i]] == tick && val[i] > maxReduce) maxReduce = val[i];
		}
}
bool check(int x) {
	tick = 0;
	maxReduce = 0;
	memset(d, 0, sizeof d);
	for (int i = 1; i <= m; ++i)
		if (len[i] > x) {
			++d[X[i]];
			++d[Y[i]];
			d[LCA[i]] -= 2;
			++tick;
		}
	dfs(1);
	return maxLen - maxReduce <= x;
}
int main() {
	n = read();
	m = read();
	int x = 0, y = 0, z = 0;
	for (int i = 1; i < n; ++i) {
		x = read();
		y = read();
		z = read();
		insert(x, y, z);
		insert(y, x, z);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	for (int i = 1; i <= m; ++i) {
		X[i] = read(); Y[i] = read();
		LCA[i] = lca(X[i], Y[i]);
		len[i] = dis[X[i]] - dis[LCA[i]] + dis[Y[i]] - dis[LCA[i]];
		if (len[i] > maxLen) maxLen = len[i];
	}
	int L = 0, R = maxLen, mid = 0;
	while (L <= R) {
		mid = (L + R) >> 1;
		if (check(mid))
			R = mid - 1;
		else
			L = mid + 1;
	}
	printf("%d", R + 1);
	return 0;
}