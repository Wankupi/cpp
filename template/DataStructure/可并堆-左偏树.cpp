#include <cstdio>
const int maxn = 100010;
int n = 0, m = 0;
int fa[maxn], son[maxn][2], dis[maxn];
int val[maxn];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
int merge(int x, int y) {
	if (x == 0 || y == 0) return x + y;
	if (val[x] == val[y] ? x > y : val[x] > val[y]) swap(x, y);
	son[x][1] = merge(son[x][1], y);
	fa[son[x][1]] = x;
	if (dis[son[x][0]] < dis[son[x][1]]) swap(son[x][0], son[x][1]);
	dis[x] = son[x][1] ? dis[son[x][1]] + 1 : 0;
	return x;
}
inline void pop(int x) {
	fa[son[x][0]] = son[x][0];
	fa[son[x][1]] = son[x][1];
	val[x] = -1;
	fa[x] = merge(son[x][0], son[x][1]);
	son[x][0] = son[x][1] = 0;
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", val + i);
	for (int i = 1; i <= n; ++i) fa[i] = i;
	int opt = 0, x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &opt, &x);
		if (opt == 1) {
			scanf("%d", &y);
			if (val[x] == -1 || val[y] == -1) continue;
			x = find(x); y = find(y);
			if (x == y) continue;
			merge(x, y);
		} 
		else {
			if (val[x] == -1) { printf("-1\n"); continue; }
			x = find(x);
			printf("%d\n", val[x]);
			pop(x);
		}
	}
	return 0;
}