#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 1503, maxm = 600003;
int n = 0, m = 0;
int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
int Dis1 = 0, Dis2 = 0;
int head[maxn], nxt[maxm], to[maxm], val[maxm], cnt = 0;
inline void insert(int u, int e, int v) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
	val[cnt] = v;
}
int dis[4][maxn];
struct Point {
	Point(int To, int distance) { t = To; d = distance; }
	int t, d;
};
inline bool operator<(const Point &lhs, const Point &rhs) { return lhs.d > rhs.d; }
bool in[maxn];
void dij(int S, int now) {
	memset(dis[now], 0x3f, sizeof(dis[now]));
	memset(in, 0, sizeof in);
	dis[now][S] = 0;
	priority_queue<Point> q;
	q.push(Point(S, 0));
	while (!q.empty()) {
		int x = q.top().t; q.pop();
		if (in[x]) continue;
		in[x] = true;
		for (int i = head[x]; i; i = nxt[i])
			if (dis[now][to[i]] > dis[now][x] + val[i]) {
				dis[now][to[i]] = dis[now][x] + val[i];
				q.push(Point(to[i], dis[now][to[i]]));
			}
	}
}
int head2[maxn], nxt2[maxm], to2[maxm], val2[maxm], cnt2 = 0;
int d[maxn];
bool sign[maxn];
inline void insert2(int u, int e, int v) {
	nxt2[++cnt2] = head2[u];
	head2[u] = cnt2;
	to2[cnt2] = e;
	val2[cnt2] = v;
}
int f[maxn], ans = 0;
inline int max(int a, int b) { return a < b ? b : a; }
void topo() {
	memset(f, 0, sizeof f);
	queue<int> q;
	for (int x = 1; x <= n; ++x) if (sign[x] && d[x] == 0) q.push(x);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		ans = max(ans, f[x]);
		for (int i = head2[x]; i; i = nxt2[i]) {
			f[to2[i]] = max(f[to2[i]], f[x] + val2[i]);
			if (--d[to2[i]] == 0) q.push(to2[i]);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		insert(x, y, z);
		insert(y, x, z);
	}
	dij(x1, 0);
	dij(y1, 1);
	dij(x2, 2);
	dij(y2, 3);
	Dis1 = dis[0][y1]; Dis2 = dis[2][y2];
	for (int x = 1; x <= n; ++x)
		for (int i = head[x]; i; i = nxt[i])
			if (dis[0][x] + val[i] + dis[1][to[i]] == Dis1 && dis[2][x] + val[i] + dis[3][to[i]] == Dis2) {
				insert2(x, to[i], val[i]);
				++d[to[i]];
				sign[x] = sign[to[i]] = true;
			}
	topo();
	memset(head2, 0, sizeof head2);
	for (int x = 1; x <= n; ++x)
		for (int i = head[x]; i; i = nxt[i])
			if (dis[0][x] + val[i] + dis[1][to[i]] == Dis1 && dis[3][x] + val[i] + dis[2][to[i]] == Dis2) {
				insert2(x, to[i], val[i]);
				++d[to[i]];
				sign[x] = sign[to[i]] = true;
			}
	topo();
	printf("%d", ans);
	return 0;
}