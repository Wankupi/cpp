#include <algorithm>
#include <cstdio>
int const maxn = 503, maxm = 1507 * 4;
int n = 0, m = 0;
template <unsigned int N, unsigned int M>
struct Graph {
	int head[N], nxt[M], to[M], val[M], cnt = 1;
	inline void insert(int u, int e, int v) {
		nxt[++cnt] = head[u];
		head[u] = cnt;
		to[cnt] = e;
		val[cnt] = v;
	}
	inline void insert2(int u, int e, int v) {
		insert(u, e, v);
		insert(e, u, 0);
	}
};
Graph<maxn, maxm> G;
Graph<maxn, maxn << 1> Tr;

namespace GHT {
int cur[maxn], dep[maxn];
int q[maxn], ql = 1, qr = 0;
bool bfs(int S, int T) {
	for (int i = 0; i <= n; ++i)
		dep[i] = 0, cur[i] = G.head[i];
	dep[S] = 1;
	q[ql = qr = 1] = S;
	while (ql <= qr) {
		int x = q[ql++];
		for (int i = G.head[x]; i; i = G.nxt[i]) {
			int y = G.to[i];
			if (dep[y] == 0 && G.val[i] > 0) {
				dep[y] = dep[x] + 1;
				q[++qr] = y;
				if (y == T) return true;
			}
		}
	}
	return false;
}
int dfs(int x, int flow, int T) {
	if (x == T) return flow;
	int use = 0;
	for (int i = cur[x]; i && use < flow; i = G.nxt[i]) {
		cur[x] = i;
		int y = G.to[i];
		if (dep[y] == dep[x] + 1 && G.val[i] > 0) {
			int k = dfs(y, std::min(G.val[i], flow - use), T);
			G.val[i] -= k;
			G.val[i ^ 1] += k;
			use += k;
		}
	}
	if (use < flow) dep[x] = 0;
	return use;
}
inline void init() {
	for (int i = 2; i <= G.cnt; i += 2) {
		G.val[i] += G.val[i + 1];
		G.val[i + 1] = 0;
	}
}
inline int dinic(int S, int T) {
	init();
	int sum = 0;
	while (bfs(S, T))
		sum += dfs(S, 0x7fffffff, T);
	return sum;
}

int p[maxn], p1[maxn], p2[maxn];
void getPre() {
	for (int i = 1; i <= n; ++i) p[i] = i;
}
void getGHT(int L, int R) {
	if (L == R) return;
	int S = p[L], T = p[L + 1];
	int cut = dinic(S, T);
	Tr.insert(S, T, cut);
	Tr.insert(T, S, cut);
	//printf("%d %d %d\n", S, T, cut);
	int c1 = 0, c2 = 0;
	for (int i = L; i <= R; ++i) {
		if (dep[p[i]])
			p1[++c1] = p[i];
		else
			p2[++c2] = p[i];
	}
	for (int i = 1; i <= c1; ++i)
		p[L + i - 1] = p1[i];
	for (int i = 1; i <= c2; ++i)
		p[L + c1 + i - 1] = p2[i];
	getGHT(L, L + c1 - 1);
	getGHT(L + c1, R);
}
} // namespace GHT

namespace MinE {
int fa[10][maxn], Mi[10][maxn], dep[maxn];
void dfs(int x) {
	for (int j = 1; j <= 9; ++j) {
		fa[j][x] = fa[j - 1][fa[j - 1][x]];
		Mi[j][x] = std::min(Mi[j - 1][x], Mi[j - 1][fa[j - 1][x]]);
	}
	for (int i = Tr.head[x]; i; i = Tr.nxt[i]) {
		int y = Tr.to[i];
		if (y != fa[0][x]) {
			fa[0][y] = x;
			Mi[0][y] = Tr.val[i];
			dep[y] = dep[x] + 1;
			dfs(y);
		}
	}
}
int query(int x, int y) {
	int ans = 0x7ffffff;
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int j = 9; ~j; --j)
		if (dep[fa[j][x]] >= dep[y]) {
			ans = std::min(ans, Mi[j][x]);
			x = fa[j][x];
		}
	if (x == y) return ans;
	for (int j = 9; ~j; --j)
		if (fa[j][x] != fa[j][y]) {
			ans = std::min(ans, std::min(Mi[j][x], Mi[j][y]));
			x = fa[j][x];
			y = fa[j][y];
		}
	ans = std::min(ans, std::min(Mi[0][x], Mi[0][y]));
	return ans;
}
} // namespace MinE

int main() {
	scanf("%d %d", &n, &m);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &x, &y, &z);
		G.insert2(x, y, z);
		G.insert2(y, x, z);
	}
	GHT::getPre();
	GHT::getGHT(0, n);
	MinE::fa[0][1] = 1;
	MinE::Mi[0][1] = 0x7fffffff;
	MinE::dep[1] = 1;
	MinE::dfs(1);
	scanf("%d", &z);
	for (int i = 1; i <= z; ++i) {
		scanf("%d %d", &x, &y);
		printf("%d\n", MinE::query(x, y));
	}
	return 0;
}