// 虚树 LCA 树形DP
#include <cstdio>
#include <algorithm>
using std::sort;
const int maxn = 250003;
int n = 0, m = 0;
struct Map {
	int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 0;
	void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
};
Map g0, g1;
inline long long min(long long a, long long b) { return a < b ? a : b; }
// 树链剖分 开始
int dfn[maxn], low[maxn], fa[maxn], siz[maxn], dep[maxn], top[maxn], son[maxn];
int c1 = 0;
long long minv[maxn]; // with special intital value : minv[1] = infty
void dfs1(int x, int f) {
	dfn[x] = low[x] = ++c1;
	fa[x] = f;
	dep[x] = dep[f] + 1;
	siz[x] = 1;
	for (int i = g0.head[x]; i; i = g0.nxt[i]) {
		if (g0.to[i] != f) {
			minv[g0.to[i]] = min(minv[x], g0.val[i]);
			dfs1(g0.to[i], x);
			siz[x] += siz[g0.to[i]];
			if (siz[g0.to[i]] > siz[son[x]]) son[x] = g0.to[i];
		}
	}
}
void dfs2(int x, int t) {
	top[x] = t;
	if (son[x]) dfs2(son[x], t);
	for (int i = g0.head[x]; i; i = g0.nxt[i])
		if (g0.to[i] != son[x] && g0.to[i] != fa[x])
			dfs2(g0.to[i], g0.to[i]);
}
int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) x ^= y ^= x ^= y;
		x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
// 树链剖分 结束
//虚树 开始
int k = 0;
int h[maxn];
bool isP[maxn];
inline bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
int st[maxn], u = 0;
void CreateXvShu() {
	sort(h + 1, h + k + 1, cmp);
	st[1] = 1;
	st[u = 2] = h[1];
	for (int i = 2; i <= k; ++i) {
		int l = lca(st[u], h[i]);
		while (u > 1 && dfn[l] <= dfn[st[u - 1]]) {
			g1.insert(st[u - 1], st[u], 0);
			--u;
		}
		if (dfn[st[u]] != dfn[l]) {
			g1.insert(l, st[u], 0);
			st[u] = l;
		}
		st[++u] = h[i];
	}
	while (u > 1) {
		g1.insert(st[u - 1], st[u], 0);
		--u;
	}
	//这里还可以有优化
}
//虚树 结束
//DP
long long DP(int x) {
	if (g1.head[x] == 0) return minv[x];
	long long sum = 0;
	for (int i = g1.head[x]; i; i = g1.nxt[i])
		sum += DP(g1.to[i]);
	g1.head[x] = 0;
	if (isP[x] || minv[x] < sum) return minv[x];
	else return sum;
}
//

int main() {
	scanf("%d", &n);
	int u = 0, v = 0, w = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		g0.insert(u, v, w);
		g0.insert(v, u, w);
	}
	minv[1] = 0x7fffffffffffffff;
	dfs1(1, 0);
	dfs2(1, 1);
	scanf("%d", &m);
	for (int T = 1; T <= m; ++T) {
		scanf("%d", &k);
		for (int i = 1; i <= k; ++i) {
			scanf("%d", h + i);
			isP[h[i]] = true;
		}
		CreateXvShu();
		printf("%lld\n", DP(1));
		g1.cnt = 0;
		for (int i = 1; i <= k; ++i) isP[h[i]] = false;
	}
	return 0;
}