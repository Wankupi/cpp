#include <cstdio>
const double eps = 1e-9;
int n = 0, m = 0;
int head[3001], nxt[100007], to[100007], cnt = 0;
double val[100007];
inline void insert(int u, int e, double v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
double L = -1e9, R = 1e9, mid = 0.0;
double dis[3001];
bool in[3001], sign[3001];
bool dfs(int x) {
	sign[x] = in[x] = true;
	for (int i = head[x]; i; i = nxt[i]) {
		if (dis[to[i]] > dis[x] + val[i] - mid ) {
			dis[to[i]] = dis[x] + val[i] - mid;
			if (in[to[i]] || dfs(to[i])) return true;
		}
	}
	in[x] = false;
	return false;
}
bool check() {
	for (int i = 1; i <= n; ++i) { dis[i] = 0; in[i] = false; sign[i] = false; }
	// 注意dis初始值是0 不需要求距离，只需判负环
	for (int i = 1; i <= n; ++i)
		if (!sign[i] && dfs(i)) return true;
	return false;
}
int main() {
	scanf("%d%d", &n, &m);
	int a = 0, b = 0;
	double w = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%lf", &a, &b, &w);
		insert(a, b, w);
		if (w < L) L = w;
		if (w > R) R = w;
	}
	a = 0;
	while (R - L > eps) {
		mid = (L + R) / 2.0;
		if (check()) R = mid;
		else L = mid;
	}
	printf("%.8lf", L);
	return 0;
}