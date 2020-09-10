#include <cstdio>
#include <algorithm>
int const maxn = 80003;
int n = 0, q = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int fa[maxn], son[maxn], dep[maxn], siz[maxn], top[maxn], dfn[maxn];
void dfs1(int x, int f) {
	siz[x] = 1;
	dep[x] = dep[f] + 1;
	fa[x] = f;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs1(to[i], x);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
		}
}
void dfs2(int x, int t) {
	dfn[x] = ++dfn[0];
	top[x] = t;
	if (son[x]) dfs2(son[x], t);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x] && to[i] != son[x])
			dfs2(to[i], to[i]);
}
inline int lca(int x, int y) {
	while (top[x] != top[y]) dep[top[x]] > dep[top[y]] ? (x = fa[top[x]]) : (y = fa[top[y]]);
	return dep[x] < dep[y] ? x : y;
}
inline int countPoint(int x, int y) {
	int LCA = lca(x, y);
	return dep[x] + dep[y] - dep[LCA] - dep[fa[LCA]];
}
int tr[maxn];
inline int lowbit(int x) { return x & -x; }
inline void add(int p, int v) { while (p <= n) { tr[p] += v; p += lowbit(p); } }
inline int query(int p) { int sum = 0; while (p > 0) { sum += tr[p]; p -= lowbit(p); } return sum; }
inline int query(int L, int R) { return query(R) - query(L - 1); }
int querySum(int x, int y) {
	int sum = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		sum += query(dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
	if (dep[x] < dep[y]) std::swap(x, y);
	sum += query(dfn[y], dfn[x]);
	return sum;
}
int t[maxn];
struct Query {
	Query() {}
	Query(int X, int Y, int K, int Iden, int Type) : x(X), y(Y), k(K), id(Iden), type(Type) {}
	int x, y, k, id, type; // Type : +1 add Value, -1 remove Value, 0 query Value
};
Query opt[maxn << 2], qL[maxn << 2], qR[maxn << 2];
int ans[maxn], cQuery = 0, copt = 0;

void solve(int L, int R, int ql, int qr) {
	if (ql > qr) return;
	if (L == R) {
		for (int i = ql; i <= qr; ++i)
			if (opt[i].type == 0)
				ans[opt[i].id] = L;
		return;
	}
	int mid = (L + R) >> 1, cL = 0, cR = 0;
	for (int i = ql; i <= qr; ++i) {
		if (opt[i].type == -1 || opt[i].type == +1) {
			if (opt[i].k > mid) {
				add(dfn[opt[i].x], opt[i].type);
				qR[++cR] = opt[i];
			}
			else qL[++cL] = opt[i];
		}
		else if (opt[i].type == 0) {
			int cn = querySum(opt[i].x, opt[i].y);
			if (cn >= opt[i].k) {
				qR[++cR] = opt[i];
			}
			else {
				opt[i].k -= cn;
				qL[++cL] = opt[i];
			}
		}
	}
	for (int i = 1; i <= cR; ++i) if (qR[i].type == -1 || qR[i].type == +1) add(dfn[qR[i].x], -qR[i].type);
	for (int i = 1; i <= cL; ++i) opt[ql + i - 1] = qL[i];
	for (int i = 1; i <= cR; ++i) opt[ql + cL + i - 1] = qR[i];
	solve(L, mid, ql, ql + cL - 1);
	solve(mid + 1, R, ql + cL, qr);
}

int main() {
	int mxT = 0, miT = 100000000;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", t + i);
		opt[++copt] = Query(i, 0, t[i], 0, +1);
		if (t[i] > mxT) mxT = t[i];
		if (t[i] < miT) miT = t[i];
	}
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	int k = 0;
	for (int i = 1; i <= q; ++i) {
		scanf("%d %d %d", &k, &x, &y);
		if (k == 0) {
			opt[++copt] = Query(x, 0, t[x], 0, -1);
			t[x] = y;
			opt[++copt] = Query(x, 0, t[x], 0, +1);
			if (y > mxT) mxT = y;
			if (y < miT) miT = y;
		}
		else {
			++cQuery;
			if (countPoint(x, y) < k) ans[cQuery] = -1;
			else opt[++copt] = Query(x, y, k, cQuery, 0);
		}
	}
	solve(miT, mxT, 1, copt);
	for (int i = 1; i <= cQuery; ++i) {
		if (ans[i] == -1) puts("invalid request!");
		else printf("%d\n", ans[i]);
	}
	return 0;
}
