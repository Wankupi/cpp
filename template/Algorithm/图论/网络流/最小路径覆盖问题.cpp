#include <cstdio>
#include <cstring>
int const maxn = 303, maxm = 15000, inf = 0x7fffffff;
inline int min(int a, int b) { return a < b ? a : b; }
int n = 0, m = 0, S = 0, T = 0;
int head[maxn], nxt[maxm], to[maxm], val[maxm], cnt = 1;

inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }

int cur[maxn], dep[maxn];
int q[maxn];
bool bfs() {
	memset(dep, 0, sizeof dep);
	memcpy(cur, head, sizeof cur);
	dep[S] = 1;
	int ql = 1, qr = 1;
	q[1] = S;
	while (ql <= qr) {
		int x = q[ql++];
		for (int i = head[x]; i; i = nxt[i]) {
			if (dep[to[i]] == 0 && val[i] > 0) {
				dep[to[i]] = dep[x] + 1;
				q[++qr] = to[i];
			}
		}
	}
	return dep[T] > 0;
}
int dfs(int x, int flow) {
	if (x == T) return flow;
	int use = 0;
	for (int i = cur[x]; i && use < flow; i = nxt[i]) {
		cur[x] = i;
		if (dep[to[i]] == dep[x] + 1 && val[i] > 0) {
			int k = dfs(to[i], min(flow - use, val[i]));
			use += k;
			val[i] -= k;
			val[i ^ 1] += k;
		}
	}
	if (use < flow) dep[x] = 0;
	return use;
}
int lp[maxn], np[maxn];
int main() {
	scanf("%d %d", &n, &m);
	T = 2 * n + 1;
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		insert(x, y + n, 1); insert(y + n, x, 0);
	}
	for (int i = 1; i <= n; ++i) {
		insert(S, i, 1); insert(i, S, 0);
		insert(i + n, T, 1); insert(T, i + n, 0);
	}
	int ans = n;
	while (bfs()) ans -= dfs(S, inf);
	for (int i = 1; i <= m; ++i) {
		int k = 2 * i;
		if (val[k] == 0) {
			lp[to[k] - n] = to[k ^ 1];
			np[to[k ^ 1]] = to[k] - n;
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (lp[i] == 0) {
			for (x = i; x; x = np[x])
				printf("%d ", x);
			printf("\n");
		}
	}
	printf("%d\n", ans);
	return 0;
}