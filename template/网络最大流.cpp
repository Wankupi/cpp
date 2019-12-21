#include <cstdio>
#include <cstring>
#include <queue>
const int maxn = 10001, maxm = 200005;
int n = 0, m = 0, s = 0, t = 0;
int head[maxn], nxt[maxm], to[maxm], val[maxm], cnt = 1;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
bool vis[maxn];
int deep[maxn];
bool bfs() {
	memset(vis, 0, sizeof(vis));
	std::queue<int> q;
	q.push(s); vis[s] = true;
	deep[s] = 1;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (!vis[to[i]] && val[i]) {
				deep[to[i]] = deep[x] + 1;
				if (to[i] == t) return true;
				vis[to[i]] = true;
				q.push(to[i]);
			}
	}
	return false;
}
inline int min(int a, int b) { return a < b ? a : b; }
int dinic(int x, int flow) {
	if (x == t) return flow;
	int use = 0, k = 0;
	for (int i = head[x]; i; i = nxt[i]) {
		if (val[i] && deep[to[i]] == deep[x] + 1) {
			k = dinic(to[i], min(flow - use, val[i]));
			if (!k) deep[to[i]] = 0;
			val[i] -= k; val[i ^ 1] += k;
			use += k;
		}
	}
	return use;
}
int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	int a = 0, b = 0, c = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		insert(a, b, c); insert(b, a, 0);
	}
	int ans = 0;
	while (bfs()) while (a = dinic(s, 0x7fffffff)) ans += a;
	printf("%d", ans);
	return 0;
}