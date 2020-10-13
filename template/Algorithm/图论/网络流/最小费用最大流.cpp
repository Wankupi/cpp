#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
void read(int &x) {
	x = 0; int c = getchar();
	while (c < '0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
}
const int maxn = 5001;
int n = 0, m = 0, s = 0, t = 0;
int head[maxn], nxt[100010], to[100010], val[100010], cost[100010], cnt = 1;
inline void insert(int u, int e, int v, int c) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; cost[cnt] = c; }
bool in[maxn];
int dis[maxn], pre[maxn];
bool spfa() {
	memset(in, 0, sizeof(in));
	memset(dis, 0x3f, sizeof(dis));
	memset(pre, 0, sizeof(pre));
	queue<int> q;
	q.push(s); in[s] = true; dis[s] = 0;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i]) {
			if (val[i] && cost[i] + dis[x] < dis[to[i]]) {
				dis[to[i]] = dis[x] + cost[i];
				pre[to[i]] = i;
				if (!in[to[i]]) {
					in[to[i]] = true;
					q.push(to[i]);
				}
			}
		}
		in[x] = false;
	}
	return dis[t] != 0x3f3f3f3f;
}
inline int min(int a, int b) { return a < b ? a : b; }
int sumCost = 0, maxFlow = 0;
void getCost() {
	int flow = 0x7fffffff;
	for (int i = t; i != s; i = to[pre[i] ^ 1])
		flow = min(flow, val[pre[i]]);
	maxFlow += flow;
	for (int i = t; i != s; i = to[pre[i] ^ 1]) {
		val[pre[i]] -= flow;
		val[pre[i] ^ 1] += flow;
		sumCost += flow * cost[pre[i]];
	}
}
int main() {
	read(n); read(m); read(s); read(t);
	int x = 0, y = 0, w = 0, f = 0;
	for (int i = 1; i <= m; ++i) {
		read(x); read(y); read(w); read(f);
		insert(x, y, w, f);
		insert(y, x, 0, -f);
	}
	while (spfa()) getCost();
	printf("%d %d", maxFlow, sumCost);
	return 0;
}