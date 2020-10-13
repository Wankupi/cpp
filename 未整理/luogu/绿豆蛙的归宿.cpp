#include <cstdio>
#include <queue>
const int maxn = 100001;
int n = 0, m = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int d[maxn], d2[maxn];
double f[maxn];
int main() {
	scanf("%d%d", &n, &m);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		insert(y, x, z); ++d[x];
	}
	for (int i = 1; i <= n; ++i) d2[i] = d[i];
	f[n] = 0.0;
	std::queue<int> q; q.push(n);
	while (!q.empty()) {
		x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i]) {
			f[to[i]] += (f[x] + val[i]) / d[to[i]];
			if (--d2[to[i]] == 0) q.push(to[i]);
		}
	}
	printf("%.2lf", f[1]);
	return 0;
}