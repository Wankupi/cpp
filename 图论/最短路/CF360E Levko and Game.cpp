#include <cstdio>
#include <queue>
typedef long long ll;
ll const inf = 0x7fffffffffffffff;
int const maxn = 10003;
int n = 0, m = 0, k = 0;
int S1 = 0, S2 = 0, T = 0;
struct Line { int x, y, l, r; } a[maxn + 100];
int head[maxn], nxt[maxn + 100], to[maxn + 100], val[maxn + 100], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }

ll dis[2][maxn];
struct Point { int id; ll d; };
inline bool operator<(Point const &lhs, Point const &rhs) { return lhs.d > rhs.d; }
bool vis[maxn];
void dijkstra(int S, ll (&dis)[maxn]) {
	for (int i = 1; i <= n; ++i) dis[i] = inf, vis[i] = false;
	std::priority_queue<Point> q;
	dis[S] = 0;
	q.push(Point{S, 0});
	while (q.size()) {
		int x = q.top().id; q.pop();
		if (vis[x]) continue;
		vis[x] = true;
		for (int i = head[x]; i; i = nxt[i])
			if (dis[to[i]] > dis[x] + val[i]) {
				dis[to[i]] = dis[x] + val[i];
				q.push(Point{to[i], dis[to[i]]});
			}
	}
}
bool changed[101];
int main() {
	scanf("%d %d %d", &n, &m, &k);
	scanf("%d %d %d", &S1, &S2, &T);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].l);
		a[i].r = a[i].l;
		insert(a[i].x, a[i].y, a[i].l);
	}
	for (int i = 1; i <= k; ++i) {
		scanf("%d %d %d %d", &a[i].x, &a[i].y, &a[i].l, &a[i].r);
		insert(a[i].x, a[i].y, a[i].r);
	}
	bool sign = true;
	while (sign) {
		sign = false;
		dijkstra(S1, dis[0]); dijkstra(S2, dis[1]);
		if (dis[0][T] < dis[1][T]) break;
		for (int i = 1; i <= k; ++i) if (!changed[i] && dis[0][a[i].x] <= dis[1][a[i].x]) {
			changed[i] = true;
			val[m + i] = a[i].l;
			sign = true;
			break;
		}
	}
	if (dis[0][T] < dis[1][T]) {
		puts("WIN");
		for (int i = 1; i <= k; ++i) printf("%d ", val[m + i]);
	}
	else if (dis[0][T] == dis[1][T]) {
		puts("DRAW");
		for (int i = 1; i <= k; ++i) printf("%d ", val[m + i]);
	}
	else puts("LOSE");
	return 0;
}