#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
int read() {
	int x = 0, c = getchar();
	while (c < '0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x;
}
typedef long long ll;
ll const inf = 0x3f3f3f3f3f3f3f3f;
int const maxn = 200003, maxm = maxn << 1;
int n = 0, m = 0, Q = 0;
int head[maxn], nxt[maxm], to[maxm], val[maxm], cntEdge = 1;
inline void insert(int u, int e, int v) { nxt[++cntEdge] = head[u]; head[u] = cntEdge; to[cntEdge] = e; val[cntEdge] = v; }

struct Point {
	Point(int Identity, ll Distance) :id(Identity), d(Distance) {}
	int id; ll d;
};
bool operator<(Point const &lhs, Point const &rhs) { return lhs.d > rhs.d; }

ll disZ[maxn], disF[maxn];
bool vis[maxn];
int from[maxn];

void Dijkstra(int S, ll(&dis)[maxn]) {
	for (int i = 1; i <= n; ++i) dis[i] = inf, vis[i] = false;
	dis[S] = 0;
	from[S] = 0;
	priority_queue<Point> q;
	q.push(Point(S, 0));
	while (!q.empty()) {
		int x = q.top().id;
		q.pop();
		if (vis[x]) continue;
		vis[x] = true;
		for (int i = head[x]; i; i = nxt[i])
			if (dis[to[i]] > dis[x] + val[i]) {
				dis[to[i]] = dis[x] + val[i];
				from[to[i]] = i;
				q.push(Point(to[i], dis[to[i]]));
			}
	}
}
int per[maxn];
int fa[19][maxn], dep[maxn];
bool on[maxn]; int Id[maxn], cntPath = 0;
void getTree() {
	for (int i = 1; i <= n; ++i) per[i] = i;
	sort(per + 1, per + n + 1, [](int a, int b) ->bool {return disZ[a] < disZ[b]; });
	for (int i = 1; i <= n; ++i) {
		int x = per[i];
		fa[0][x] = to[from[x] ^ 1];
		if (x == 1) fa[0][x] = 1;
		dep[x] = dep[fa[0][x]] + 1;
		for (int j = 1; j <= 18; ++j) fa[j][x] = fa[j - 1][fa[j - 1][x]];
	}
}
void findPath() {
	per[0] = 0;
	for (int x = n; x != 1; x = to[from[x] ^ 1]) {
		on[from[x] >> 1] = true;
		per[++per[0]] = to[from[x] ^ 1];
	}
	for (int i = per[0]; i >= 1; --i) Id[per[i]] = ++cntPath;
	Id[n] = cntPath + 1;
}
inline int lca(int x, int y) {
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int j = 18; ~j; --j) if (dep[fa[j][x]] >= dep[y]) x = fa[j][x];
	if (x == y) return x;
	for (int j = 18; ~j; --j) if (fa[j][x] != fa[j][y]) x = fa[j][x], y = fa[j][y];
	return fa[0][x];
}

inline ll disExcept(int i) { return std::min(disZ[to[i << 1]] + disF[to[i << 1 | 1]], disZ[to[i << 1 | 1]] + disF[to[i << 1]]); }
inline ll disCross(int i) { return disExcept(i) + val[i << 1]; }

ll mi[maxm << 2];
void Modify(int p, int L, int R, int l, int r, ll v) {
	if (l <= L && R <= r) { mi[p] = std::min(mi[p], v); return; }
	if (mi[p] <= v) return;
	int mid = (L + R) >> 1;
	if (l <= mid) Modify(p << 1, L, mid, l, r, v);
	if (r > mid) Modify(p << 1 | 1, mid + 1, R, l, r, v);
}
ll query(int p, int L, int R, int x) {
	if (L == R) return mi[p];
	int mid = (L + R) >> 1;
	if (x <= mid) return std::min(mi[p], query(p << 1, L, mid, x));
	else return std::min(mi[p], query(p << 1 | 1, mid + 1, R, x));
}

int main() {
	n = read(); m = read(); Q = read();
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		x = read(); y = read(); z = read();
		insert(x, y, z);
		insert(y, x, z);
	}

	Dijkstra(1, disZ);
	getTree();
	findPath();
	Dijkstra(n, disF);

	memset(mi, 0x3f, sizeof mi);
	for (int i = 1; i <= m; ++i) {
		if (on[i]) continue;
		int u = to[i << 1], e = to[i << 1 | 1];
		ll dis = disCross(i);
		u = lca(u, n); e = lca(e, n);
		if (u == e) continue;
		if (Id[u] > Id[e]) std::swap(u, e);
		Modify(1, 1, cntPath, Id[u], Id[e] - 1, dis);
	}

	for (int i = 1; i <= Q; ++i) {
		x = read(); z = read();
		if (on[x]) {
			if (z <= val[x << 1]) printf("%lld\n", disExcept(x) + z);
			else {
				ll ans = disExcept(x) + z;
				int u = to[x << 1], e = to[x << 1 | 1];
				if (Id[u] > Id[e]) std::swap(u, e);
				ans = std::min(ans, query(1, 1, cntPath, Id[u]));
				printf("%lld\n", ans);
			}
		}
		else {
			ll ans = disZ[n];
			if (z <= val[x << 1]) ans = std::min(disZ[n], disExcept(x) + z);
			printf("%lld\n", ans);
		}
	}
	return 0;
}