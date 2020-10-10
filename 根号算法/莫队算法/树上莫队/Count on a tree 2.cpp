#include <cstdio>
#include <cmath>
#include <algorithm>
inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
int const maxn = 40003;
int n = 0, m = 0;
int a[maxn], A[maxn], *endA;
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int in[maxn], out[maxn], dep[maxn];
int fa[17][maxn];
int id[maxn << 1], cTP = 0;
void dfs(int x, int f) {
	in[x] = ++cTP;
	id[cTP] = x;
	dep[x] = dep[f] + 1;
	fa[0][x] = f;
	for (int j = 1; j <= 16; ++j) fa[j][x] = fa[j - 1][fa[j - 1][x]];
	for (int i = head[x]; i; i = nxt[i]) if (to[i] != f) dfs(to[i], x);
	out[x] = ++cTP;
	id[cTP] = x;
}
inline int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int j = 16; ~j; --j) if (dep[fa[j][x]] >= dep[y]) x = fa[j][x];
	if (x == y) return x;
	for (int j = 16; ~j; --j) if (fa[j][x] != fa[j][y]) x = fa[j][x], y = fa[j][y];
	return fa[0][x];
}
int block = 0;
struct Query {
	int l, r, lca, id;
};
inline bool operator<(Query const &lhs, Query const &rhs) { return lhs.l / block == rhs.l / block ? lhs.r < rhs.r : lhs.l < rhs.l; }
Query q[100003];
int t[maxn], Ans = 0, st[maxn];
inline void add(int x) { if (++t[x] == 1) ++Ans; }
inline void rmv(int x) { if (--t[x] == 0) --Ans; }
int ans[100003];
int main() {
	scanf("%d %d", &n, &m);
	block = int(sqrt(2 * n));
	for (int i = 1; i <= n; ++i) scanf("%d", a + i), A[i] = a[i];
	std::sort(A + 1, A + n + 1);
	endA = std::unique(A + 1, A + n + 1);
	for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(A + 1, endA, a[i]) - A;
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	dfs(1, 1);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		if (in[x] > in[y]) swap(x, y);
		if ((q[i].lca = lca(x, y)) == x) {
			q[i].l = in[x];
			q[i].r = in[y];
		} else {
			q[i].l = out[x];
			q[i].r = in[y];
		}
		q[i].id = i;
	}
	std::sort(q + 1, q + m + 1);
	int L = 1, R = 0;
	for (int i = 1; i <= m; ++i) {
		while (R < q[i].r) { ++R; (st[id[R]] ^= 1) ? add(a[id[R]]) : rmv(a[id[R]]); }
		while (q[i].l < L) { --L; (st[id[L]] ^= 1) ? add(a[id[L]]) : rmv(a[id[L]]); }
		while (q[i].r < R) { (st[id[R]] ^= 1) ? add(a[id[R]]) : rmv(a[id[R]]); --R; }
		while (L < q[i].l) { (st[id[L]] ^= 1) ? add(a[id[L]]) : rmv(a[id[L]]); ++L; }
		ans[q[i].id] = Ans + (t[a[q[i].lca]] == 0);
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}