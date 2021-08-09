#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
int const maxn = 20003;
int n = 0, m = 0, Q = 0;
int cPoint = 0;
struct Graph {
	int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
	ll val[maxn << 1];
	inline void insert(int u, int e, ll v) {
		nxt[++cnt] = head[u];
		head[u] = cnt;
		to[cnt] = e;
		val[cnt] = v;
	}
};
Graph G, T;
int dfn[maxn], low[maxn], cdfn = 0;
int stack[maxn], top = 0;
int v[maxn], fa[maxn];
ll dis[maxn], len[maxn];
void solve_Circle(int x, int y, ll w) {
	len[++cPoint] = w;
	for (int k = y; k != x; k = fa[k]) {
		dis[k] = len[cPoint];
		len[cPoint] += v[k];
	}
	for (int k = y; k != x; k = fa[k]) {
		ll d = min(dis[k], len[cPoint] - dis[k]); // I believe that x must on the top of these points in the new tree
		T.insert(cPoint, k, d);
		T.insert(k, cPoint, d);
	}
	T.insert(cPoint, x, 0);
	T.insert(x, cPoint, 0);
}
void tarjan(int x) {
	dfn[x] = low[x] = ++cdfn;
	stack[++top] = x;
	for (int i = G.head[x]; i; i = G.nxt[i])
		if (dfn[G.to[i]] == 0) {
			fa[G.to[i]] = x;
			v[G.to[i]] = G.val[i];
			tarjan(G.to[i]);
			low[x] = std::min(low[x], low[G.to[i]]);
			if (low[G.to[i]] > dfn[x]) {
				T.insert(x, G.to[i], G.val[i]);
				T.insert(G.to[i], x, G.val[i]);
			}
		}
		else if (G.to[i] != fa[x])
			low[x] = std::min(low[x], dfn[G.to[i]]);

	for (int i = G.head[x]; i; i = G.nxt[i])
		if (fa[G.to[i]] != x && dfn[G.to[i]] > dfn[x])
			solve_Circle(x, G.to[i], G.val[i]);
	if (low[x] == dfn[x]) {
		int y = 0; do y = stack[top--]; while (y != x);
	}
}
inline ll disOnCir(int x, int y, int idSq) {
	ll l = std::abs(dis[x] - dis[y]);
	return min(l, len[idSq] - l);
}
int Fa[15][maxn], dep[maxn];
ll Dis[maxn];
void dfs(int x, int f) {
	Fa[0][x] = f;
	for (int j = 1; j <= 14; ++j) Fa[j][x] = Fa[j - 1][Fa[j - 1][x]];
	dep[x] = dep[f] + 1;
	for (int i = T.head[x]; i; i = T.nxt[i])
		if (T.to[i] != f) {
			Dis[T.to[i]] = Dis[x] + T.val[i];
			dfs(T.to[i], x);
		}
}
ll getDis(int x, int y) {
	int X = x, Y = y;
	if (dep[X] < dep[Y]) std::swap(X, Y);
	for (int j = 14; ~j; --j) if (dep[Fa[j][X]] >= dep[Y]) X = Fa[j][X];
	if (X == Y) return Dis[x] + Dis[y] - 2 * Dis[X];
	for (int j = 14; ~j; --j) if (Fa[j][X] != Fa[j][Y]) X = Fa[j][X], Y = Fa[j][Y];
	int lca = Fa[0][X];
	if (lca <= n) return Dis[x] + Dis[y] - 2 * Dis[lca];
	else return Dis[x] + Dis[y] - Dis[X] - Dis[Y] + disOnCir(X, Y, lca);
}
int main() {
	scanf("%d %d %d", &n, &m, &Q);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &x, &y, &z);
		G.insert(x, y, z);
		G.insert(y, x, z);
	}
	cPoint = n;
	tarjan(1);
	dfs(1, 1);
	for (int i = 1; i <= Q; ++i) {
		scanf("%d %d", &x, &y);
		printf("%lld\n", getDis(x, y));
	}
	return 0;
}