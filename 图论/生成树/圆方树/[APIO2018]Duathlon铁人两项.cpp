#include <cstdio>
#include <assert.h>
typedef long long ll;
int const maxn = 100003, maxm = 200003 << 1, maxP = maxn << 1;
int n = 0, m = 0, cPoint = 0;
namespace Graph {
	int dfn[maxn], low[maxn], cDfn = 0;
	int stack[maxn], top = 0;
	void insert(int, int);
	void tarjan(int);
}
namespace CirSqTr {
	int w[maxP];
	bool vis[maxP];
	void insert(int, int);
	void dfs1(int, int);
	void dfs2(int);
}
ll ans = 0;
int main() {
	scanf("%d %d", &n, &m);
	cPoint = n;
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		Graph::insert(x, y);
		Graph::insert(y, x);
	}
	for (int i = 1; i <= n; ++i)
		if (!Graph::dfn[i])
			Graph::tarjan(i);
	for (int i = 1; i <= n; ++i) CirSqTr::w[i] = -1;
	for (int i = 1; i <= n; ++i)
		if (!CirSqTr::vis[i]) {
			CirSqTr::dfs1(i, 0);
			CirSqTr::dfs2(i);
		}
	printf("%lld", ans);
	return 0;
}
inline int min(int a, int b) { return a < b ? a : b; }
namespace Graph {
	int head[maxn], nxt[maxm], to[maxm], cnt = 0;
	void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
	void tarjan(int x) {
		dfn[x] = low[x] = ++cDfn;
		stack[++top] = x;
		for (int i = head[x]; i; i = nxt[i]) {
			if(!dfn[to[i]]) {
				tarjan(to[i]);
				low[x] = min(low[x], low[to[i]]);
				if (low[to[i]] >= dfn[x]) {
					int y = 0, k = ++cPoint;
					do {
						y = stack[top--];
						CirSqTr::insert(k, y);
						CirSqTr::insert(y, k);
						++CirSqTr::w[k];
					} while (y != to[i]);
					CirSqTr::insert(k, x);
					CirSqTr::insert(x, k);
					++CirSqTr::w[k];
				}
			}
			else low[x] = min(low[x], dfn[to[i]]);
		}
	}
}
namespace CirSqTr {
	int head[maxP], nxt[maxP << 1], to[maxP << 1], cnt = 0;
	void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
	int fa[maxP], siz[maxP];
	ll f[maxP];
	void dfs1(int x, int fath) {
		vis[x] = true;
		siz[x] = (x <= n);
		f[x] = -(x <= n);
		fa[x] = fath;
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != fath) {
				dfs1(to[i], x);
				siz[x] += siz[to[i]];
				f[x] += f[to[i]] + (long long)siz[to[i]] * w[x];
			}
	}
	void dfs2(int x) {
		if (x <= n) ans += f[x] - w[x];
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != fa[x]) {
				ll T = f[x] - (f[to[i]] + (long long)siz[to[i]] * w[x]);
				int sizT = siz[x] - siz[to[i]];
				f[to[i]] += T + (long long)sizT * w[to[i]];
				siz[to[i]] += sizT;
				dfs2(to[i]);
			}
	}
}