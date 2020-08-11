#include <cstdio>
const int maxn = 100003;
inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
inline long long max(long long a, long long b) { return a < b ? b : a; }
int n = 0;
long long m = 0;
int head[maxn], nxt[maxn], to[maxn], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int ls[maxn], rs[maxn], dis[maxn], siz[maxn];
long long c[maxn], l[maxn], sum[maxn];
int root[maxn];
int merge(int x, int y) {
	if (x == 0 || y == 0) return x | y;
	if (c[x] < c[y]) swap(x, y);
	rs[x] = merge(rs[x], y);
	if (dis[ls[x]] < dis[rs[x]]) swap(ls[x], rs[x]);
	dis[x] = rs[x] ? dis[rs[x]] + 1 : 0;
	sum[x] = sum[ls[x]] + sum[rs[x]] + c[x];
	siz[x] = siz[ls[x]] + siz[rs[x]] + 1;
	return x;
}
int pop(int x) { return merge(ls[x], rs[x]); }
long long ans = 0;
void dfs(int x) {
	for (int i = head[x]; i; i = nxt[i]) {
		dfs(to[i]);
		root[x] = merge(root[x], root[to[i]]);
		while (root[x] && sum[root[x]] > m) root[x] = pop(root[x]);
	}
	while (root[x] && sum[root[x]] > m) root[x] = pop(root[x]);
	ans = max(ans, siz[root[x]] * l[x]);
}
int main() {
	scanf("%d%lld", &n, &m);
	int f = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%lld%lld", &f, c + i, l + i);
		sum[i] = c[i];
		if (f != 0) insert(f, i);
		dis[i] = 0;
		siz[i] = 1;
		root[i] = i;
	}
	dfs(1);
	printf("%lld", ans);
	return 0;
}