#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int inf = 0x7fffffff, maxn = 8000;
int n = 0, m = 0;
int s = 0, t = 0, c1 = 0;
int a[201][201], x[201][201], y[201][201];
int head[maxn], nxt[maxn], to[maxn], val[maxn], cnt = 1;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int xToYvan[maxn], yToYvan[maxn];
bool added[maxn];
void CreateNewMap() {
	s = 0; t = 1; c1 = 1;
	for (int i = 1; i <= m; ++i) { // 拆 行
		xToYvan[++c1] = i;
		for (int j = 1; j <= n; ++j)
			if (a[i][j] == 0)	x[i][j] = c1;
			else if (a[i][j] == 2)
				xToYvan[++c1] = i;
	}
	for (int j = 1; j <= n; ++j) { // 拆 列
		yToYvan[++c1] = j;
		for (int i = 1; i <= m; ++i)
			if (a[i][j] == 0)	y[i][j] = c1;
			else if (a[i][j] == 2)
				yToYvan[++c1] = j;
	}
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j)
			if (a[i][j] == 0) {
				insert(x[i][j], y[i][j], 1);
				insert(y[i][j], x[i][j], 0);
				if (!added[x[i][j]]) {
					insert(s, x[i][j], 1);
					insert(x[i][j], s, 0);
					added[x[i][j]] = true;
				}
				if (!added[y[i][j]]) {
					insert(y[i][j], t, 1);
					insert(t, y[i][j], 0);
					added[y[i][j]] = true;
				}
			}
}
inline int min(int a, int b) { return a < b ? a : b; }
int deep[maxn];
bool bfs() {
	memset(deep, 0, sizeof deep);
	deep[s] = 1;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (!deep[to[i]] && val[i]) {
				deep[to[i]] = deep[x] + 1;
				q.push(to[i]);
			}
	}
	return deep[t];
}
int dinic(int x, int flow) {
	if (x == t || !flow) return flow;
	int use = 0;
	for (int i = head[x]; i; i = nxt[i])
		if (deep[to[i]] == deep[x] + 1 && val[i] > 0) {
			int k = dinic(to[i], min(flow - use, val[i]));
			val[i] -= k;
			val[i ^ 1] += k;
			use += k;
			if (use == flow) break;
		}
	if (use == 0) deep[x] = 0;
	return use;
}
void find(int x) {
	for (int i = head[x]; i; i = nxt[i])
		if (val[i] == 0)
			printf("%d %d\n", xToYvan[x], yToYvan[to[i]]);
}
int main() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &a[i][j]);
	CreateNewMap();
	int sum = 0;
	while (bfs())
		sum += dinic(s, inf);
	printf("%d\n", sum);
	for (int i = head[s]; i; i = nxt[i])
		if (val[i] == 0)
			find(to[i]);
	return 0;
}