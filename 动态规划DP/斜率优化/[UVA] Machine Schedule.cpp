#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n = 0, m = 0, k = 0;
int s = 0, t = 0;
int head[300], nxt[200001], to[200001], val[200001], cnt = 1;
inline void insert(int u, int e, int v) {
	nxt[++cnt] = head[u]; head[u] = cnt;
	to[cnt] = e; val[cnt] = v;
}
inline int min(int a, int b) { return a < b ? a : b; }
int d[300];
bool bfs() {
	memset(d, 0, sizeof d);
	queue<int> q; q.push(s);
	d[s] = 1;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(int i=head[x];i;i=nxt[i])
			if (!d[to[i]] && val[i] > 0) {
				d[to[i]] = d[x] + 1;
				q.push(to[i]);
			}
	}
	return d[t];
}
int dinic(int x, int flow) {
	if (x == t || flow == 0) return flow;
	int use = 0;
	for(int i=head[x];i;i=nxt[i]) 
		if (d[to[i]] == d[x] + 1 && val[i]) {
			int k = dinic(to[i], min(flow - use, val[i]));
			val[i] -= k;
			val[i ^ 1] += k;
			use += k;
		}
	if (!use) d[x] = 0;
	return use;
}
int main() {
	while (scanf("%d", &n) && n!= 0) {
		scanf("%d%d", &m, &k);
		s = 0, t = n + m + 1;
		int x = 0, y = 0, z = 0;
		for (int i = 1; i <= k; ++i) {
			scanf("%d%d%d", &z, &x, &y);
			if (x == 0 || y == 0) continue;
			insert(x, y + n, 1);
			insert(y + n, x, 0);
		}
		for (int i = 1; i <= n; ++i) {
			insert(s, i, 1);
			insert(i, s, 0);
		}
		for (int i = 1; i <= m; ++i) {
			insert(i + n, t, 1);
			insert(t, i + 1, 0);
		}
		int sum = 0;
		while (bfs()) sum += dinic(s, 0x7ffffff);
		printf("%d\n", sum);
		n = m = k=s = t = 0;
		memset(head, 0, sizeof head);
		cnt = 1;
	}
	return 0;
}