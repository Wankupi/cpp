#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;
int n = 0, m = 0;
int head[3005], nxt[10000], to[10000], cnt = 0;
ll val[10000], dis[3005], Ep[3005];
inline void insert(int u, int e, ll v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
bool inQ[3005], confirmed[3005];
int times[3005];
bool spfa() {
	memset(dis, 0x3f, sizeof(dis));
	dis[0] = 0;
	queue<int> q;
	q.push(0); inQ[0] = true;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		inQ[x] = false;
		for (int i = head[x]; i; i = nxt[i])
			if (dis[x] + val[i] < dis[to[i]]) {
				dis[to[i]] = dis[x] + val[i];
				if (++times[to[i]] > 2*n) return false;
				if (!inQ[to[i]]) {
					q.push(to[i]);
					inQ[to[i]] = true;
				}
			}
	}
	return true;
}
struct Point { int id; ll d; };
bool operator<(const Point &lhs, const Point &rhs) { return lhs.d > rhs.d; }
inline int min(int a, int b) { return a < b ? a : b; }
void dij(int S) {
	memset(dis, 0x3f, sizeof(dis));
	memset(inQ, 0, sizeof(inQ));
	memset(confirmed, 0, sizeof(confirmed));
	dis[S] = 0;
	priority_queue<Point> q;
	q.push({ S,0 });
	while (!q.empty()) {
		int x = q.top().id; q.pop();
		if (confirmed[x]) continue;
		confirmed[x] = true; inQ[x] = false;
		for (int i = head[x]; i; i = nxt[i])
			if (!confirmed[to[i]]) {
				if (dis[x] + val[i] - Ep[to[i]] + Ep[x] < dis[to[i]]) {
					dis[to[i]] = dis[x] + val[i] - Ep[to[i]] + Ep[x];
					q.push({ to[i],dis[to[i]]});
				}
				//else if (!inQ[to[i]]) {
				//	q.push({ to[i],dis[to[i]] });
				//} // It won't run
			}
	}

}
int main() {
	freopen("P5905_11.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d%d", &n, &m);
	int a = 0, b = 0;
	ll c = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%lld", &a, &b, &c);
		insert(a, b, c);
	}
	for (int i = 1; i <= n; ++i) insert(0, i, 0);
	if (!spfa()) {
		printf("-1\n");
		return 0;
	}
	for (int i = 1; i <= n; ++i) Ep[i] = dis[i];
	for (int x = 1; x <= n; ++x) {
		ll ans = 0;
		dij(x);
		for (int i = 1; i <= n; ++i) {
			ans += i * (dis[i] == 0x3f3f3f3f3f3f3f3f ? 1e9 : dis[i] + Ep[i] - Ep[x]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}