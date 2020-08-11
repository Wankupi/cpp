#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int dx[4] = { 0, 0, +1, -1 }, dy[4] = { +1, -1, 0, 0 }, maxn = 10003;
inline int min(int a, int b) { return a < b ? a : b; }
int n = 0, m = 0, S = 0, T = 0;
inline int func(int y, int x) { return (y - 1) * m + x; }
int a[101][101];
int head[maxn], nxt[100000], to[100000], val[100000], cnt = 1;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int dep[maxn], cur[maxn];
bool bfs() {
	memset(dep, 0, sizeof dep);
	memcpy(cur, head, sizeof head);
	queue<int> q;
	dep[S] = 1;
	q.push(S);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (!dep[to[i]] && val[i]) {
				dep[to[i]] = dep[x] + 1;
				if (to[i] == T) return true;
				q.push(to[i]);
			}
	}
	return false;
}
int dinic(int x, int flow) {
	if (x == T) return flow;
	int use = 0;
	for (int i = cur[x]; i && use < flow; i = nxt[i]) {
		cur[x] = i;
		if (dep[to[i]] == dep[x] + 1 && val[i]) {
			int k = dinic(to[i], min(flow - use, val[i]));
			use += k;
			val[i] -= k;
			val[i ^ 1] += k;
		}
	}
	if (use < flow) dep[x] = 0;
	return use;
}
int main() {
	scanf("%d%d", &n, &m);
	S = 0;
	T = n * m + 1;
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &a[i][j]);
			sum += a[i][j];
			if (((i ^ j) & 1) == 0) {
				insert(S, func(i, j), a[i][j]);
				insert(func(i, j), S, 0);
				for (int k = 0; k < 4; ++k) {
					int y = i + dy[k], x = j + dx[k];
					if (y < 1 || y > n || x < 1 || x > m) continue;
					insert(func(i, j), func(y, x), 0x3f3f3f3f);
					insert(func(y, x), func(i, j), 0);
				}
			}
			else {
				insert(func(i, j), T, a[i][j]);
				insert(T, func(i, j), 0);
			}
		}
	}
	int maxFlow = 0;
	while (bfs())
		maxFlow += dinic(S, 0x3f3f3f3f);
	printf("%d", sum - maxFlow);
	return 0;
}