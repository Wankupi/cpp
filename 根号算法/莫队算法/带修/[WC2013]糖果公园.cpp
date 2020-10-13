#include <cstdio>
#include <algorithm>
#include <cmath>
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || '9' < c) c = getchar();
	while ('0' <= c && c <= '9') x = 10 * x + c - '0', c = getchar();
	return x;
}
int const maxn = 100003;
int n = 0, m = 0, q = 0, BLOCK = 0;
int V[maxn], W[maxn], color[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }

int in[maxn], out[maxn], fa[maxn], siz[maxn], son[maxn], top[maxn], dep[maxn], cdfn = 0;
int id[maxn << 1];
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
	id[in[x] = ++cdfn] = x;
	top[x] = t;
	for (int i = head[x]; i; i = nxt[i]) if (to[i] != fa[x] && to[i] != son[x]) dfs2(to[i], to[i]);
	if (son[x]) dfs2(son[x], t);
	id[out[x] = ++cdfn] = x;
}
inline int lca(int x, int y) {
	while (top[x] != top[y]) dep[top[x]] > dep[top[y]] ? (x = fa[top[x]]) : (y = fa[top[y]]);
	return dep[x] < dep[y] ? x : y;
}
struct Query {
	int l, r, lca, time, id; // id is time
};
inline bool operator<(Query const &lhs, Query const &rhs) {
	if (lhs.l / BLOCK == rhs.l / BLOCK) return lhs.r / BLOCK == rhs.r / BLOCK ? lhs.id < rhs.id : lhs.r < rhs.r;
	return lhs.l < rhs.l;
}
struct Change {
	int pos, from, to, id;
};
Query qs[maxn]; int cntQuery = 0;
Change ch[maxn]; int cntChanges = 0;
long long Ans = 0;
int t[maxn], st[maxn];
inline void add(int x) { Ans += (long long)W[++t[x]] * V[x]; }
inline void rmv(int x) { Ans -= (long long)W[t[x]--] * V[x]; }
inline void addTime(int x) {
	if (st[ch[x].pos]) {
		rmv(color[ch[x].pos]);
		add(ch[x].to);
	}
	color[ch[x].pos] = ch[x].to;
}
inline void rmvTime(int x) {
	if (st[ch[x].pos]) {
		rmv(color[ch[x].pos]);
		add(ch[x].from);
	}
	color[ch[x].pos] = ch[x].from;
}
long long ans[maxn];
void solve() {
	BLOCK = 2000;
	std::sort(qs + 1, qs + cntQuery + 1);
	for (int i = cntChanges; i >= 1; --i) color[ch[i].pos] = ch[i].from;
	int l = 1, r = 0, Time = 0;
	for (int i = 1; i <= cntQuery; ++i) {
		while (ch[Time + 1].id < qs[i].time) addTime(++Time);
		while (ch[Time].id > qs[i].time) rmvTime(Time--);
		while (r < qs[i].r) { ++r; (st[id[r]] ^= 1) ? add(color[id[r]]) : rmv(color[id[r]]); }
		while (qs[i].l < l) { --l; (st[id[l]] ^= 1) ? add(color[id[l]]) : rmv(color[id[l]]); }
		while (qs[i].r < r) { (st[id[r]] ^= 1) ? add(color[id[r]]) : rmv(color[id[r]]); --r; }
		while (l < qs[i].l) { (st[id[l]] ^= 1) ? add(color[id[l]]) : rmv(color[id[l]]); ++l; }
		if (!st[qs[i].lca]) add(color[qs[i].lca]);
		ans[qs[i].id] = Ans;
		if (!st[qs[i].lca]) rmv(color[qs[i].lca]);
	}
}
int main() {
	// scanf("%d %d %d", &n, &m, &q);
	n = read(); m = read(); q = read();
	for (int i = 1; i <= m; ++i)
		// scanf("%d", V + i);
		V[i] = read();
	for (int i = 1; i <= n; ++i)
		// scanf("%d", W + i);
		W[i] = read();
	int x = 0, y = 0, opt = 0;
	for (int i = 1; i < n; ++i) {
		// scanf("%d %d", &x, &y);
		x = read(); y = read();
		insert(x, y); insert(y, x);
	}
	dfs1(1, 1);
	dfs2(1, 1);
	for (int i = 1; i <= n; ++i)
		// scanf("%d", color + i);
		color[i] = read();

	for (int i = 1; i <= q; ++i) {
		// scanf("%d %d %d", &opt, &x, &y);
		opt = read(); x = read(); y = read();
		if (opt == 0) {
			++cntChanges;
			ch[cntChanges] = Change{x, color[x], y, i};
			color[x] = y;
		}
		else {
			if (in[x] > in[y]) std::swap(x, y);
			int LCA = lca(x, y);
			++cntQuery;
			qs[cntQuery] = Query{LCA == x ? in[x] : out[x], in[y], LCA, i, cntQuery};
		}
	}
	ch[cntChanges + 1].id = q + 1; // prevent from "out of bound".
	solve();
	for (int i = 1; i <= cntQuery; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}