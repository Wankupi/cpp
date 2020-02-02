#include <cstdio>
#include <cstring>
#include <queue>
int n = 0, m = 0, k = 0;
int head[2010], to[2010], nxt[2010], val[2010], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int a[2010];
bool vis[2010];
bool check() {
	std::queue<int> q;
	for (int point = 1; point <= n + m; ++point)
		if (!vis[point]) {
			q.push(point);
			a[point] = 0;
			vis[point] = true;
			while (!q.empty()) {
				int x = q.front(); q.pop();
				for (int i = head[x]; i; i = nxt[i]) {
					if (!vis[to[i]]) {
						vis[to[i]] = true;
						a[to[i]] = val[i] - a[x];
						q.push(to[i]);
					} else if (a[to[i]] + a[x] != val[i])
						return false;
				}
			}
		}
	return true;
}
int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &k);
		memset(head,0,sizeof head);
		cnt = 0;
		int x = 0, y = 0, c = 0;
		for (int i = 1; i <= k; ++i) {
			scanf("%d%d%d", &x, &y, &c);
			insert(x, y + n, c);
			insert(y + n, x, c);
		}
		memset(vis, 0, sizeof vis);
		memset(a, 0, sizeof a);
		puts(check() ? "Yes" : "No");
	}
	return 0;
}