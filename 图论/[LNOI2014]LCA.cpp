#include <cstdio>
#include <cstring>
const int mod = 201314, maxn = 50003;
int n = 0, q = 0;
int head[maxn], nxt[maxn], to[maxn], cnt = 0;
void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int fa[maxn], top[maxn], dep[maxn], siz[maxn], dfn[maxn], son[maxn], c = 0;
void dfs1(int x) {
	dep[x] = dep[fa[x]] + 1;
	siz[x] = 1;
	for (int i = head[x]; i; i = nxt[i]) {
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (son[x] == -1 || siz[son[x]] < siz[to[i]]) son[x] = to[i];
	}
}
void dfs2(int x, int t) {
	dfn[x] = ++c;
	top[x] = t;
	if (~son[x]) dfs2(son[x], t);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != son[x])
			dfs2(to[i], to[i]);
}
inline int lowbit(int x) { return x & -x; }
class TreeArrey {
public:
	void add(int p, int x) {
		while (p <= n) {
			(tree[p] += x) %= mod;
			p += lowbit(p);
		}
	}
	int query(int p) {
		int ret = 0;
		while (p) {
			(ret += tree[p]) %= mod;
			p -= lowbit(p);
		}
		return ret;
	}
	int query(int l, int r) { return (query(r) - query(l - 1) + mod) % mod; }
	int tree[maxn];
};
TreeArrey b, bi;
inline void add(int l, int r, int x) {
	b.add(l, x);
	b.add(r + 1, -x);
	bi.add(l, x * l);
	bi.add(r + 1, -x * (r + 1));
}
inline int query(int p) { return ((p + 1) * b.query(p) % mod - bi.query(p) + mod) % mod; }
inline int query(int l, int r) { return (query(r) - query(l - 1) + mod) % mod; }
void tagToRoot(int x) {
	while (~x) {
		add(dfn[top[x]], dfn[x], 1);
		x = fa[top[x]];
	}
}
int SumToRoot(int x) {
	int sum = 0;
	while (~x) {
		(sum += query(dfn[top[x]], dfn[x])) %= mod;
		x = fa[top[x]];
	}
	return sum;
}
int Querys[maxn], id[maxn << 1], val[maxn << 1], nxtQ[maxn << 1], cntQ = 0;
int Z[maxn << 1];
void addQuery(int Pos, int iden, int z, int opt) {
	nxtQ[++cntQ] = Querys[Pos];
	Querys[Pos] = cntQ;
	id[cntQ] = iden;
	val[cntQ] = opt;
	Z[cntQ] = z;
}
int ans[maxn];
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i < n; ++i) {
		scanf("%d", fa + i);
		insert(fa[i], i);
	}
	int l = 0, r = 0, z = 0;
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d%d", &l, &r, &z);
		if (l >= 1) addQuery(l - 1, i, z, -1);
		addQuery(r, i, z, +1);
	}
	memset(son, 0xff, sizeof son);
	dfs1(0);
	dfs2(0, 0);
	fa[0] = -1;
	for (int x = 0; x < n; ++x) {
		tagToRoot(x);
		for (int i = Querys[x]; i; i = nxtQ[i]) {
			(ans[id[i]] += val[i] * SumToRoot(Z[i])) %= mod;
			if (ans[id[i]] < 0) ans[id[i]] += mod;
		}
	}
	for (int i = 1; i <= q; ++i)
		printf("%d\n", ans[i]);
	return 0;
}