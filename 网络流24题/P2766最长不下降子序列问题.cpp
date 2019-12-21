#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int inf = 999999;
int n = 0;
int a[501], dp[501];
inline int max(int a, int b) { return a < b ? b : a; }
inline int min(int a, int b) { return a < b ? a : b; }
int s = 0, t = 0;
int head[520], nxt[3000], to[3000], val[3000], f[3000], cnt = 1;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; f[cnt] = 0;}
int d[520];
bool bfs() {
	queue<int> q; q.push(s);
	memset(d, 0, sizeof(d));
	d[s] = 1;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (!d[to[i]] && val[i] - f[i] > 0) {
				d[to[i]] = d[x] + 1;
				if (to[i] == t) return true;
				q.push(to[i]);
			}
	}
	return false;
}
int dfs(int x, int flow) {
	if (x == t) return flow;
	int use = 0, k = 0;
	for (int i = head[x]; i; i = nxt[i])
		if (d[to[i]] == d[x] + 1 && val[i] - f[i] > 0) {
			k = dfs(to[i], min(flow - use, val[i] - f[i]));
			if (!k) d[to[i]] = 0;
			f[i] += k; f[i ^ 1] -= k;
			use += k;
		}
	return use;
}
inline int dinic() {
	int sum = 0;
	while (bfs())
		sum += dfs(s, inf);
	return sum;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	a[n + 1] = inf;
	for (int i = 1; i <= n + 1; ++i) {
		for (int j = 1; j != i; ++j)
			if (a[i] >= a[j]) dp[i] = max(dp[i], dp[j]);
		++dp[i];
	}
	int len = 0;
	for (int i = 1; i <= n; ++i)
		len = max(len, dp[i]);
	printf("%d\n", len);
	s = 0; t = n + 1;
	for (int i = 1; i <= n + 1; ++i) {
		for (int j = 0; j != i; ++j) {
			if (a[i] >= a[j] && dp[i] == dp[j] + 1) {
				insert(j, i, 1); insert(i, j, 0);
			}
		}
	}
	printf("%d\n", dinic());
	memset(f, 0, sizeof(f));
	for (int i = head[s]; i; i = nxt[i])
		if (to[i] == 1) {
			val[i] = inf;
			break;
		}
	for (int i = head[n]; i; i = nxt[i])
		if (to[i] == t) {
			val[i] = inf;
			break;
		}	
	printf("%d", dinic());
	return 0;
}