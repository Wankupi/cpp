#include <cstdio>
#include <cstring>
const int maxn = 10003, maxm = 200003;
int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }
inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
int n = 0, m = 0;
int X[maxm], Y[maxm];
int head[maxn], nxt[maxm], to[maxm], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
namespace CirSqTree {
	int cPoint = 0;
	int head[maxn << 1], nxt[maxn << 2], to[maxn << 2], cnt = 0;
	inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
	int dep[maxn << 1], siz[maxn << 1], son[maxn << 1], top[maxn << 1], fa[maxn << 1];
	void dfs1(int x, int f) {
		fa[x] = f; dep[x] = dep[f] + 1; siz[x] = 1;
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != f) {
				dfs1(to[i], x);
				siz[x] += siz[to[i]];
				if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
			}
	}
	void dfs2(int x, int t) {
		top[x] = t;
		if (son[x]) dfs2(son[x], t);
		for (int i = head[x]; i; i = nxt[i]) if (to[i] != fa[x] && to[i] != son[x]) dfs2(to[i], to[i]);
	}
	inline int lca(int x, int y) {
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) swap(x, y);
			x = fa[top[x]];
		}
		return dep[x] > dep[y] ? y : x;
	}
	inline int dis(int x, int y) { return dep[x] + dep[y] - 2 * dep[lca(x, y)]; }
};
int dfn[maxn], low[maxn], cdfn = 0;
int stack[maxn], top = 0;
void tarjan(int x, int f) {
	dfn[x] = low[x] = ++cdfn;
	stack[++top] = x;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			if (!dfn[to[i]]) {
				tarjan(to[i], x);
				low[x] = min(low[x], low[to[i]]);
				if (low[to[i]] >= dfn[x]) {
					++CirSqTree::cPoint;
					int y = 0;
					do {
						y = stack[top--];
						CirSqTree::insert(y, CirSqTree::cPoint);
						CirSqTree::insert(CirSqTree::cPoint, y);
					} while (y != to[i]);
					CirSqTree::insert(x, CirSqTree::cPoint);
					CirSqTree::insert(CirSqTree::cPoint, x);
				}
			}
			else low[x] = min(low[x], dfn[to[i]]);
		}
}
int main() {
	while(true) {
		n = read(); m = read();
		if(n == 0 || m == 0)  break;
		for (int i = 1; i <= m; ++i) {
			X[i] = read(); Y[i] = read();
			insert(X[i], Y[i]);
			insert(Y[i], X[i]);
		}
		CirSqTree::cPoint = n;
		for (int i = 1; i <= n; ++i) tarjan(i, 0);
		for (int i = 1; i <= n; ++i) if (!CirSqTree::siz[i]) CirSqTree::dfs1(i, 0);
		for (int i = 1; i <= n; ++i) if (!CirSqTree::top[i]) CirSqTree::dfs2(i, i);
		int q = read();
		int a = 0, b = 0;
		for (int i = 1; i <= q; ++i) {
			a = read(); b = read();
			int ans = 0;
			ans = max(ans, CirSqTree::dis(X[a], X[b]) / 2 - 1);
			ans = max(ans, CirSqTree::dis(X[a], Y[b]) / 2 - 1);
			ans = max(ans, CirSqTree::dis(Y[a], X[b]) / 2 - 1);
			ans = max(ans, CirSqTree::dis(Y[a], Y[b]) / 2 - 1);
			printf("%d\n", ans);
		}
		cnt = cdfn = top = 0;
		memset(head,0,sizeof head);
		memset(dfn,0,sizeof dfn);
		memset(low,0,sizeof low);
		CirSqTree::cnt = 0;
		memset(CirSqTree::head, 0, sizeof CirSqTree::head);
		memset(CirSqTree::son, 0, sizeof CirSqTree::son);
		memset(CirSqTree::siz, 0, sizeof CirSqTree::siz);
		memset(CirSqTree::top, 0, sizeof CirSqTree::top);
		memset(CirSqTree::dep, 0, sizeof CirSqTree::dep);
	}
	return 0;
}