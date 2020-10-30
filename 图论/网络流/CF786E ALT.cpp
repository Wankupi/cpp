#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int const maxn = 20003, inf = 0x7fffffff, maxP = maxn << 3;
template<unsigned int N, unsigned int M>
struct Graph {
	int head[N], nxt[M], to[M], val[M], cnt = 1;
	inline void insert(int u, int e, int v = 0) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
};
int n = 0, m = 0;
Graph<maxn, maxn * 2> tr;
Graph<maxP, 2000000> G;

int fa[maxn], dep[maxn], siz[maxn], son[maxn], top[maxn], dfn[maxn], idfn[maxn], cdfn = 0;
int from[maxn];
void dfs1(int x, int f);
void dfs2(int x, int t);

int SegRoot = 0;
int id[maxP], ls[maxP], rs[maxP], cNode = 0;
int pos[maxP];
void buildSeg(int &p, int L, int R);
void connect(int p, int L, int R, int l, int r, int x);
void AddLine(int x, int y, int citizen);

int S = 0, T = 0;
int cur[maxP], dis[maxP];
bool bfs();
int dinic(int x, int flow);

int belong[maxP];
void dfs3(int x, int k);
int ans1[maxn], ans2[maxn];
void getAns();

int main() {
	scanf("%d %d", &n, &m);
	S = 0;
	cNode = T = m + 1;
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		tr.insert(x, y);
		tr.insert(y, x);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	buildSeg(SegRoot, 1, n);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		AddLine(x, y, i);
		G.insert(S, i, 1);
		G.insert(i, S, 0);
	}
	int sum = 0;
	while (bfs()) sum += dinic(S, inf);
	printf("%d\n", sum);
	getAns();
	for (int i = 0; i <= ans1[0]; ++i) printf("%d ", ans1[i]);
	printf("\n");
	for (int i = 0; i <= ans2[0]; ++i) printf("%d ", ans2[i]);
	printf("\n");
	return 0;
}

void dfs1(int x, int f) {
	fa[x] = f; dep[x] = dep[f] + 1; siz[x] = 1;
	for (int i = tr.head[x]; i; i = tr.nxt[i]) {
		int y = tr.to[i];
		if (y != f) {
			from[y] = i >> 1;
			dfs1(y, x);
			siz[x] += siz[y];
			if (siz[y] > siz[son[x]]) son[x] = y;
		}
	}
}

void dfs2(int x, int t) {
	top[x] = t;
	dfn[x] = ++cdfn;
	idfn[cdfn] = x;
	if (son[x]) dfs2(son[x], t);
	for (int i = tr.head[x]; i; i = tr.nxt[i]) {
		int y = tr.to[i];
		if (y != fa[x] && y != son[x]) dfs2(y, y);
	}
}

void buildSeg(int &p, int L, int R) {
	p = ++cNode;
	if (L == R) {
		pos[p] = from[idfn[L]];
		G.insert(p, T, 1); G.insert(T, p, 0);
		return;
	}
	int mid = (L + R) >> 1;
	buildSeg(ls[p], L, mid); buildSeg(rs[p], mid + 1, R);
	G.insert(p, ls[p], inf); G.insert(ls[p], p, 0);
	G.insert(p, rs[p], inf); G.insert(rs[p], p, 0);
}

void connect(int p, int L, int R, int l, int r, int x) {
	if (l <= L && R <= r) {
		G.insert(x, p, inf); G.insert(p, x, 0);
		return;
	}
	int mid = (L + R) >> 1;
	if (l <= mid) connect(ls[p], L, mid, l, r, x);
	if (r > mid) connect(rs[p], mid + 1, R, l, r, x);
}

void AddLine(int x, int y, int citizen) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		connect(SegRoot, 1, n, dfn[top[x]], dfn[x], citizen);
		x = fa[top[x]];
	}
	if (x == y) return;
	if (dep[x] < dep[y]) std::swap(x, y);
	connect(SegRoot, 1, n, dfn[y] + 1, dfn[x], citizen);
}

int q[maxP], ql = 1, qr = 0;
bool bfs() {
	for (int i = 0; i <= cNode; ++i) cur[i] = G.head[i], dis[i] = 0;
	dis[S] = 1;
	q[ql = qr = 1] = S;
	while (ql <= qr) {
		int x = q[ql++];
		for (int i = G.head[x]; i; i = G.nxt[i]) {
			int y = G.to[i];
			if (dis[y] == 0 && G.val[i] > 0) {
				dis[y] = dis[x] + 1;
				q[++qr] = y;
			}
		}
	}
	return dis[T] != 0;
}
int dinic(int x, int flow) {
	if (x == T) return flow;
	int use = 0;
	for (int i = cur[x]; i && use < flow; i = G.nxt[i]) {
		cur[x] = i;
		int y = G.to[i];
		if (dis[y] == dis[x] + 1 && G.val[i] > 0) {
			int k = dinic(y, std::min(flow - use, G.val[i]));
			use += k;
			G.val[i] -= k;
			G.val[i ^ 1] += k;
		}
	}
	if (use < flow) dis[x] = 0;
	return use;
}

void dfs3(int x) {
	belong[x] = 1;
	for (int i = G.head[x]; i; i = G.nxt[i])
		if (belong[G.to[i]] == 0 && G.val[i] > 0)
			dfs3(G.to[i]);
}

void getAns() {
	dfs3(S);
	for (int i = G.head[S]; i; i = G.nxt[i]) {
		if (G.val[i] == 0 && belong[G.to[i]] == 0)
			ans1[++ans1[0]] = G.to[i];
	}
	for (int i = G.head[T]; i; i = G.nxt[i]) {
		if (G.val[i] > 0 && belong[G.to[i]] == 1)
			ans2[++ans2[0]] = pos[G.to[i]];
	}
	sort(ans1 + 1, ans1 + ans1[0] + 1);
	sort(ans2 + 1, ans2 + ans2[0] + 1);
}