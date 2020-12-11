#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
void read(int &x) {
	x = 0; int c = getchar();
	while (c < '0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
}
const int inf = 0x7fffffff, maxP = 2500, maxL = 2005001;
int n = 0, m = 0, e = 0, s = 0, t = 0;
int head[maxP], nxt[maxL], to[maxL], val[maxL], cnt = 1;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int d[maxP];
inline int min(int a, int b) { return a < b ? a : b; }
bool bfs() {
	memset(d, 0, sizeof(d));
	queue<int> q;
	q.push(s);
	d[s] = 1;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (!d[to[i]] && val[i]) {
				d[to[i]] = d[x] + 1;
				if (to[i] == t) return true;
				q.push(to[i]);
			}
	}
	return false;
}
int dfs(int x, int flow) {
	if (x == t) return flow;
	int use = 0;
	for (int i = head[x]; i; i = nxt[i]) {
		if (use >= flow) break;
		if (d[to[i]] == d[x] + 1 && val[i] > 0) {
			int k = dfs(to[i], min(val[i], flow - use));
			val[i] -= k;
			val[i ^ 1] += k;
			use += k;
		}
	}
	if (!use) d[x] = 0;
	return use;
}
int main() {
	read(n); read(m); read(e);
	s = n + m + 1;
	t = n + m + 2;
	int u = 0, v = 0;
	for (int i = 1; i <= e; ++i) {
		read(u); read(v);
		if (u > n || v > m) continue;
		insert(u, v + n, inf);
		insert(v + n, u, 0);
	}
	for (int i = 1; i <= n; ++i) {
		insert(s, i, 1); insert(i, s, 0);
	}
	for (int i = n + 1; i <= n + m; ++i) {
		insert(i, t, 1); insert(t, i, 0);
	}
	int sum = 0;
	while (bfs()) sum += dfs(s, inf);
	printf("%d", sum);
	return 0;
}