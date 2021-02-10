#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using ll = long long;
int const maxn = 5001, maxm = 50001;

struct Graph {
	int head[maxn], nxt[maxm], to[maxm], val[maxm], cnt = 0;
	void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
};


int n = 0, b = 0, s = 0, r = 0;
Graph gZ, gF;
int dist[2][maxn];

struct Point { int id, d; };
inline bool operator<(Point const &lhs, Point const &rhs) { return lhs.d > rhs.d; }
void dij(Graph const &G, int S, int (&dis)[maxn]) {
	memset(dis, 0x3f, sizeof dis);
	std::priority_queue<Point> q;
	q.push(Point{S, dis[S] = 0});
	while (q.size()) {
		int x = q.top().id, _d = q.top().d; q.pop();
		if (dis[x] < _d) continue;
		for (int i = G.head[x]; i; i = G.nxt[i])
			if (dis[G.to[i]] > dis[x] + G.val[i])
				q.push(Point{G.to[i], dis[G.to[i]] = dis[x] + G.val[i]});
	}
}

ll a[maxn];
ll f[2][maxn]; int cur[2][maxn];
int main() {
	scanf("%d %d %d %d", &n, &b, &s, &r);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= r; ++i) {
		scanf("%d %d %d", &x, &y, &z);
		gZ.insert(x, y, z); gF.insert(y, x, z);
	}
	dij(gZ, b + 1, dist[0]); dij(gF, b + 1, dist[1]);
	for (int i = 1; i <= b; ++i) a[i] = dist[0][i] + dist[1][i];
	std::sort(a + 1, a + b + 1);
	for (int i = 1; i <= b; ++i) {
		a[i] += a[i - 1];
		f[1][i] = a[i] * i;
		// cur[1][i] = 0;
	}
	cur[0][b + 1] = cur[1][b + 1] = b + 1;
	for (int k = 2; k <= s; ++k) {
		int st = k & 1, fr = st ^ 1;
		memset(f[st], 0x3f, sizeof f[st]);
		for (int i = b; i >= 1; --i) {
			for (int j = cur[fr][i]; j <= cur[st][i + 1] && j < i; ++j) {
				ll v = f[fr][j] + (i - j) * (a[i] - a[j]);
				if (v < f[st][i]) { f[st][i] = v; cur[st][i] = j; }
			}
		}
	}
	ll ans = f[s & 1][b] - a[b];
	printf("%lld", ans);
	return 0;
}