#include <cstdio>
void read(int &x) {
	x = 0; int c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	x *= f;
}
inline int max(int a, int b) { return a < b ? b : a; }
const int maxn = 100001, maxZ = 100001;
int n = 0, m = 0;
int head[maxn], nxt[200003], to[200003], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int fa[maxn];
namespace TreeChain {
	int siz[maxn], dep[maxn], son[maxn], top[maxn];
	void dfs1(int x, int f) {
		fa[x] = f;
		siz[x] = 1;
		dep[x] = dep[f] + 1;
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != f) {
				dfs1(to[i], x);
				siz[x] += siz[to[i]];
				if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
			}
	}
	void dfs2(int x, int t) {
		top[x] = t;
		if (son[x]) dfs2(son[x], t);
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != fa[x] && to[i] != son[x])
				dfs2(to[i], to[i]);
	}
	inline int lca(int x, int y) {
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) x ^= y ^= x ^= y;
			x = fa[top[x]];
		}
		return dep[x] < dep[y] ? x : y;
	}
}
namespace SegTr {
	int root[maxn];
	struct Node {
		int mV, mP;
		int lc, rc;
	};
	Node tr[50 * maxZ];
	int cnt = 0;
	inline int NewNode() { return ++cnt; }
	inline void pushUp(int p) {
		if (tr[tr[p].lc].mV < tr[tr[p].rc].mV) {
			tr[p].mV = tr[tr[p].rc].mV;
			tr[p].mP = tr[tr[p].rc].mP;
		}
		else {
			tr[p].mV = tr[tr[p].lc].mV;
			tr[p].mP = tr[tr[p].lc].mP;
		}
	}
	int Combine(int p1, int p2, int L, int R) {
		if (p1 == 0) return p2;
		if (p2 == 0) return p1;
		if (L == R) {
			tr[p1].mV += tr[p2].mV;
			tr[p1].mP = L;
			return p1;
		}
		int mid = (L + R) >> 1;
		tr[p1].lc = Combine(tr[p1].lc, tr[p2].lc, L, mid);
		tr[p1].rc = Combine(tr[p1].rc, tr[p2].rc, mid + 1, R);
		pushUp(p1);
		return p1;
	}
	inline void Combine(int A, int B) {
		root[A] = Combine(root[A], root[B], 1, maxZ);
	}
	void add(int &p, int x, int v, int L, int R) {
		if (p == 0) p = NewNode();
		if (L == R) {
			tr[p].mV += v;
			tr[p].mP = x;
			return;
		}
		int mid = (L + R) >> 1;
		if (x <= mid)	add(tr[p].lc, x, v, L, mid);
		if (x > mid)	add(tr[p].rc, x, v, mid + 1, R);
		pushUp(p);
	}
	inline int MaxKind(int A) {
		return tr[root[A]].mV ? tr[root[A]].mP : 0;
	}
}
int ans[maxn];
void dfs(int x) {
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x]) {
			dfs(to[i]);
			SegTr::Combine(x, to[i]);
		}
	ans[x] = SegTr::MaxKind(x);
}
int main() {
	read(n);
	read(m);
	int a = 0, b = 0, c = 0;
	for (int i = 1; i < n; ++i) {
		read(a); read(b);
		insert(a, b);
		insert(b, a);
	}
	TreeChain::dfs1(1, 1);
	TreeChain::dfs2(1, 1);
	for (int i = 1; i <= m; ++i) {
		read(a); read(b); read(c);
		int lca = TreeChain::lca(a, b);
		SegTr::add(SegTr::root[a], c, 1, 1, maxZ);
		SegTr::add(SegTr::root[b], c, 1, 1, maxZ);
		SegTr::add(SegTr::root[lca], c, -1, 1, maxZ);
		if (lca != 1) {
			SegTr::add(SegTr::root[fa[lca]], c, -1, 1, maxZ);
		}
	}
	dfs(1);
	for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	return 0;
}