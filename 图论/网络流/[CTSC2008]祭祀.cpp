#include <cstdio>
#include <algorithm>
using namespace std;
int const inf = 0x7fffffff;
int n = 0, m = 0;
bool G[101][101];

int N = 0, S = 0, T = 0;
int head[230], nxt[40000], to[40000], val[40000], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
inline void init(int _N, int _S, int _T) {
	N = _N; cnt = 1; S = _S; T = _T;
	for (int i = 0; i <= N; ++i) head[i] = 0;
}
int dep[230], cur[230];
int q[230], ql = 1, qr = 0;
bool bfs() {
	for (int i = 0; i <= N; ++i) dep[i] = 0, cur[i] = head[i];
	dep[S] = 1;
	q[ql = qr = 1] = S;
	while (ql <= qr) {
		int x = q[ql++];
		for (int i = head[x]; i; i = nxt[i])
			if (dep[to[i]] == 0 && val[i] > 0) {
				dep[to[i]] = dep[x] + 1;
				if (to[i] == T) return true;
				q[++qr] = to[i];
			}
	}
	return false;
}
int dfs(int x, int flow) {
	if (x == T) return flow;
	int use = 0;
	for (int i = cur[x]; i && use < flow; i = nxt[i]) {
		cur[x] = i;
		if (dep[to[i]] == dep[x] + 1 && val[i] > 0) {
			int k = dfs(to[i], min(val[i], flow - use));
			use += k;
			val[i] -= k;
			val[i ^ 1] += k;
		}
	}
	if (use < flow) dep[x] = 0;
	return use;
}
inline int dinic() {
	int sum = 0;
	while (bfs()) sum += dfs(S, inf);
	return sum;
}
int match[103];
bool vis[230];
void dfsAns(int x) {
	vis[x] = true;
	for (int i = 1; i <= n; ++i)
		if (G[i][x - n] && !vis[i]) {
			vis[i] = true;
			dfsAns(match[i]);
		}
}
int main() {
	scanf("%d %d", &n, &m);
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		G[x][y] = true;
	}
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i) {
			if (!G[i][k]) continue;
			for (int j = 1; j <= n; ++j)
				G[i][j] |= G[k][j];
		}
	
	init(2 * n + 1, 0, 2 * n + 1);
	for (int i = 1; i <= n; ++i) {
		insert(S, i, 1); insert(i, S, 0);
		insert(i + n, T, 1); insert(T, i + n, 0);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (G[i][j]) { insert(i, j + n, 1); insert(j + n, i, 0); }
	int Ans = n - dinic();
	printf("%d\n", Ans);
	for (int i = 1; i <= n; ++i) if (!val[i * 4 - 2]) {
		for (int j = head[i]; j; j = nxt[j])
			if (to[j] != S && val[j] == 0) {
				match[i] = to[j];
				break;
			}
	}
	for (int i = 1; i <= n; ++i) if (val[i * 4] == 1) dfsAns(i + n);
	for (int i = 1; i <= n; ++i)
		printf("%d", int(!vis[i] && vis[i + n]));
	puts("");
	for (int i = 1; i <= n; ++i) {
		static int del[103];
		int cntPoint = 0;
		for (int j = 1; j <= n; ++j) del[j] = (i == j || G[i][j] || G[j][i]);
		init(2 * n + 1, 0, 2 * n + 1);
		for (int j = 1; j <= n; ++j)
			if (!del[j]) {
				insert(S, j, 1);
				insert(j, S, 0);
				insert(j + n, T, 1);
				insert(T, j + n, 0);
				++cntPoint;
			}
		for (int j = 1; j <= n; ++j)
			if (!del[j])
				for (int k = 1; k <= n; ++k)
					if (!del[k] && G[j][k]) {
						insert(j, k + n, 1); insert(k + n, j, 0);
					}
		printf("%d", int(cntPoint - dinic() == Ans - 1));
	}
	printf("\n");
	return 0;
}