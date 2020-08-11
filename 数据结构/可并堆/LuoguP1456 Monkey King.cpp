#include <algorithm>
#include <cstdio>
const int maxn = 100003;
int n = 0, m = 0;
int a[maxn];
int ls[maxn], rs[maxn], dis[maxn];
void node(int k) {
	ls[k] = rs[k] = 0;
	dis[k] = 0;
}
int combine(int x, int y) {
	if (x == 0 || y == 0) return x | y;
	if (a[x] < a[y]) std::swap(x, y);
	rs[x] = combine(rs[x], y);
	if (dis[rs[x]] > dis[ls[x]]) std::swap(ls[x], rs[x]);
	dis[x] = rs[x] ? dis[rs[x]] + 1 : 1;
	return x;
}
int fa[maxn], root[maxn];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) {
			node(i);
			root[i] = fa[i] = i;
		}
		scanf("%d", &m);
		int x = 0, y = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &x, &y);
			x = find(x);
			y = find(y);
			if (x == y) {
				printf("-1\n");
				continue;
			}
			int Ta = root[x], Tb = root[y];
			root[x] = combine(ls[Ta], rs[Ta]);
			a[Ta] /= 2;
			node(Ta);
			root[x] = combine(root[x], Ta);
			root[y] = combine(ls[Tb], rs[Tb]);
			a[Tb] /= 2;
			node(Tb);
			root[y] = combine(root[y], Tb);
			root[x] = combine(root[x], root[y]);
			fa[y] = x;
			printf("%d\n", a[root[x]]);
		}
	}
	return 0;
}