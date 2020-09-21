#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 5005;
int n = 0, m = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
bool in[maxn];
int vis[maxn], dist[maxn];
bool spfa() {
	memset(dist, -0x3f, sizeof dist);
	//memset(in, 0, sizeof in);
	dist[0] = 0;
	queue<int> q;
	in[0] = true; q.push(0);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (dist[to[i]] < dist[x] + val[i]) {
				dist[to[i]] = dist[x] + val[i];
				if (!in[to[i]]) {
					if (++vis[to[i]] > n) return false;
					q.push(to[i]);
					in[to[i]] = true;
				}
			}
		in[x] = false;
	}
	return true;
}
int main() {
	scanf("%d %d", &n, &m);
	int a = 0, b = 0, c = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		insert(a, b, -c);
	}
	for (int i = 1; i <= n; ++i)
		insert(0, i, 0);
	if (spfa())
		for (int i = 1; i <= n; ++i)
			printf("%d ", dist[i]);
	else printf("NO");
	return 0;
}