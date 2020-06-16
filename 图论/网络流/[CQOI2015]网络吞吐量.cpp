#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;
const int maxn = 520, maxm = 200010;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n = 0, m = 0;
int head[maxn], nxt[maxm], to[maxm], cnt = 1;
ll val[maxm], w[maxn];
inline void insert(int u, int e, ll v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
ll dis[maxn];
bool in[maxn];
inline ll min(ll a, ll b) { return a < b ? a : b; }
ll spfa() {
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	queue<int> q;
	q.push(1);
	in[1] = true;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (dis[x] + val[i] < dis[to[i]]) {
				dis[to[i]] = dis[x] + val[i];
				if (!in[to[i]]) {
					q.push(to[i]);
					in[to[i]] = true;
				}
			}
		in[x] = false;
	}
	return dis[n];
}
int head2[maxn << 1], nxt2[maxm], to2[maxm], cnt2 = 1;
ll  val2[maxm];
inline void insert2(int u, int e, ll v) { nxt2[++cnt2] = head2[u]; head2[u] = cnt2; to2[cnt2] = e; val2[cnt2] = v; }
int deep[maxn << 1];
bool bfs() {
	memset(deep, 0, sizeof deep);
	queue<int> q;
	q.push(1);
	deep[1] = 1;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head2[x]; i; i = nxt2[i])
			if (deep[to2[i]] == 0 && val2[i] > 0) {
				deep[to2[i]] = deep[x] + 1;
				q.push(to2[i]);
			}
	}
	return deep[n + n];
}
ll dinic(int x, ll flow) {
	if (x == n + n) return flow;
	ll use = 0, k = 0;
	for (int i = head2[x]; i; i = nxt2[i])
		if (deep[to2[i]] == deep[x] + 1 && val2[i]) {
			k = dinic(to2[i], min(flow - use, val2[i]));
			if (k == 0) deep[to2[i]] = 0;
			val2[i] -= k;
			val2[i ^ 1] += k;
			use += k;
		}
	return use;
}
int main() {
	scanf("%d %d", &n, &m);
	int x = 0, y = 0;
	ll z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %lld", &x, &y, &z);
		insert(x, y, z); insert(y, x, z);
	}
	for (int i = 1; i <= n; ++i)
		scanf("%lld", w + i);
	w[1] = w[n] = inf;
	spfa();
	for (x = 1; x <= n; ++x) {
		insert2(x, x + n, w[x]); insert2(x + n, x, 0);
		for (int i = head[x]; i; i = nxt[i])
			if (dis[to[i]] == dis[x] + val[i]) {
				insert2(x + n, to[i], inf); insert2(to[i], x + n, 0);
			}
	}
	ll ans = 0;
	while (bfs()) ans += dinic(1, inf);
	printf("%lld", ans);
	return 0;
}