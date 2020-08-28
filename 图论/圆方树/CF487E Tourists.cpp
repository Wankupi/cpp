#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
const int maxn = 100003, maxP = maxn << 1;
const int inf = 0x7fffffff;
inline int min(int a, int b) { return a < b ? a : b; }
int n = 0, m = 0, q = 0;
int w[maxP];
namespace CirSqTr {
	int cPoint = 0;
	void insert(int u, int e);
	void dfs1(int x, int f);
	void dfs2(int x, int t);
	void Modify(int x, int v);
	int query(int x, int y);
}
namespace Graph {
	void insert(int u, int e);
	void tarjan(int x, int fr);
}
namespace SegTr {
	int val[maxP << 2];
	void Create(int p, int L, int R);
	void Modify(int p, int L, int R, int x);
	int Query(int p, int L, int R, int l, int r);
}

int main() {
	freopen("tou.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &q);
	memset(w, 0x3f, sizeof w);
	for (int i = 1; i <= n; ++i) scanf("%d", w + i);
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		Graph::insert(x, y);
		Graph::insert(y, x);
	}
	CirSqTr::cPoint = n;
	Graph::tarjan(1, 0);
	CirSqTr::dfs1(1, 0);
	CirSqTr::dfs2(1, 1);
	SegTr::Create(1, 1, CirSqTr::cPoint);
	char opt = 0;
	for (int i = 1; i <= q; ++i) {
		do opt = getchar(); while (opt != 'C' && opt != 'A');
		scanf("%d %d", &x, &y);
		if (opt == 'C') CirSqTr::Modify(x, y);
		else printf("%d\n", CirSqTr::query(x, y));
	}
	return 0;
}

namespace Graph {
	int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
	inline void insert(int u, int e) {
		nxt[++cnt] = head[u];
		head[u] = cnt;
		to[cnt] = e;
	}
	int dfn[maxn], low[maxn], cDfn = 0;
	int stack[maxn], top = 0;
	void tarjan(int x, int fr) {
		dfn[x] = low[x] = ++cDfn;
		stack[++top] = x;
		for (int i = head[x]; i; i = nxt[i])
			if (!dfn[to[i]]) {
				tarjan(to[i], x);
				low[x] = std::min(low[x], low[to[i]]);
				if (low[to[i]] >= dfn[x]) {
					int k = ++CirSqTr::cPoint, y = 0;
					do {
						y = stack[top--];
						CirSqTr::insert(k, y);
						CirSqTr::insert(y, k);
					} while (y != to[i]);
					CirSqTr::insert(k, x);
					CirSqTr::insert(x, k);
				}
			}
			else
				low[x] = min(low[x], dfn[to[i]]);
	}
}

namespace CirSqTr {
	int head[maxP], nxt[maxP << 1], to[maxP << 1], cnt = 0;
	inline void insert(int u, int e) {
		nxt[++cnt] = head[u];
		head[u] = cnt;
		to[cnt] = e;
	}
	std::multiset<int> ms[maxP];
	std::multiset<int>::iterator it[maxP];
	int fa[maxP], top[maxP], son[maxP], siz[maxP], dep[maxP];
	int dfn[maxP], idfn[maxP], cDfn = 0;
	void dfs1(int x, int f) {
		fa[x] = f;
		siz[x] = 1;
		dep[x] = dep[f] + 1;
		if (x <= n) {
			it[x] = ms[f].insert(w[x]);
			w[f] = min(w[f], w[x]);
		}
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != f) {
				dfs1(to[i], x);
				siz[x] += siz[to[i]];
				if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
			}
	}
	void dfs2(int x, int t) {
		top[x] = t;
		dfn[x] = ++cDfn;
		idfn[cDfn] = x;
		if (son[x]) dfs2(son[x], t);
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != fa[x] && to[i] != son[x])
				dfs2(to[i], to[i]);
	}
	void Modify(int x, int v) {
		ms[fa[x]].erase(it[x]);
		w[x] = v;
		it[x] = ms[fa[x]].insert(w[x]);
		int y = w[fa[x]];
		w[fa[x]] = *ms[fa[x]].begin();
		SegTr::Modify(1, 1, cPoint, dfn[x]);
		if (fa[x] && y != w[fa[x]]) SegTr::Modify(1, 1, cPoint, dfn[fa[x]]);
	}
	int query(int x, int y) {
		int ans = inf;
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
			ans = std::min(ans, SegTr::Query(1, 1, cPoint, dfn[top[x]], dfn[x]));
			x = fa[top[x]];
		}
		if (dep[x] < dep[y]) std::swap(x, y);
		ans = min(ans, SegTr::Query(1, 1, cPoint, dfn[y], dfn[x]));
		if (y > n) ans = min(ans, w[fa[y]]);
		return ans;
	}
}

namespace SegTr {
	void Create(int p, int L, int R) {
		if (L == R) { val[p] = w[CirSqTr::idfn[L]]; return; }
		int mid = (L + R) >> 1;
		Create(p << 1, L, mid);
		Create(p << 1 | 1, mid + 1, R);
		val[p] = std::min(val[p << 1], val[p << 1 | 1]);
	}
	void Modify(int p, int L, int R, int x) {
		if (L == R) {
			val[p] = w[CirSqTr::idfn[L]];
			return;
		}
		int mid = (L + R) >> 1;
		if (x <= mid) Modify(p << 1, L, mid, x);
		else Modify(p << 1 | 1, mid + 1, R, x);
		val[p] = std::min(val[p << 1], val[p << 1 | 1]);
	}
	int Query(int p, int L, int R, int l, int r) {
		if (l <= L && R <= r) return val[p];
		int mid = (L + R) >> 1;
		if (r <= mid) return Query(p << 1, L, mid, l, r);
		else if (l > mid) return Query(p << 1 | 1, mid + 1, R, l, r);
		else return std::min(Query(p << 1, L, mid, l, r), Query(p << 1 | 1, mid + 1, R, l, r));
	}
}
