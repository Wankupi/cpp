#include <cstdio>
#include <cctype>
template<typename T>
void read(T &x) {
	char c = getchar(); bool f = false; x = 0;
	while (!isdigit(c)) { if (c == '-') f = true; c = getchar(); }
	while (isdigit(c)) { x = (x << 1) + (x << 3) + c - '0'; c = getchar(); }
	if (f) x = -x;
}
const int maxN = 100001;
int n = 0, m = 0, root = 0;
int mod = 0;	//模数
int a[maxN];	//每个节点【初始】的值
				//建立dfs序与原序的映射
int dfn[maxN], cc = 0, yvan[maxN];
int head[maxN], nxt[2 * maxN], to[2 * maxN], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; to[cnt] = e; head[u] = cnt; }
class SegmentTree {
public:
	void create(int p, int l, int r);
	void add(int p, int l, int r, int v);
	int query(int p, int l, int r);
private:
	struct Node { int l, r, sum, lazy; };
	Node tree[4 * maxN];
private:
	int length(int p) { return tree[p].r - tree[p].l + 1; }
	void UP(int p) { (tree[p].sum = tree[p << 1].sum + tree[p << 1 | 1].sum) %= mod; }
	void down(int p) {
		(tree[p << 1].sum += tree[p].lazy * length(p << 1)) %= mod;
		(tree[p << 1].lazy += tree[p].lazy) %= mod;
		(tree[(p << 1) | 1].sum += tree[p].lazy * length((p << 1) | 1)) %= mod;
		(tree[(p << 1) | 1].lazy += tree[p].lazy) %= mod;
		tree[p].lazy = 0;
	}
	int MID(int p) { return (tree[p].l + tree[p].r) >> 1; }
} st;
int fa[maxN], siz[maxN], son[maxN], deep[maxN], top[maxN];
void dfs1(int x, int f) {
	siz[x] = 1; fa[x] = f;
	deep[x] = deep[f] + 1;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs1(to[i], x);
			siz[x] += siz[to[i]];
			if (siz[son[x]] < siz[to[i]])
				son[x] = to[i];
		}
}
void dfs2(int x, int f) {
	dfn[x] = ++cc; yvan[cc] = x; top[x] = f;
	if (son[x]) dfs2(son[x], f);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x] && to[i] != son[x])
			dfs2(to[i], to[i]);
}

void do1(int x, int y, int z) {
	while (top[x] != top[y]) {
		if (deep[top[y]] > deep[top[x]])
			x ^= y ^= x ^= y;
		st.add(1, dfn[top[x]], dfn[top[x]] + deep[x] - deep[top[x]], z);
		x = fa[top[x]];
	}
	if (deep[y] > deep[x])
		x ^= y ^= x ^= y;
	st.add(1, dfn[y], dfn[x], z);
}
int do2(int x, int y) {
	int ans = 0;
	while (top[x] != top[y]) {
		if (deep[top[y]] > deep[top[x]])
			x ^= y ^= x ^= y;
		(ans += st.query(1, dfn[top[x]], dfn[top[x]] + deep[x] - deep[top[x]])) %= mod;
		x = fa[top[x]];
	}
	if (deep[y] > deep[x])
		x ^= y ^= x ^= y;
	ans += st.query(1, dfn[y], dfn[x]);
	return ans % mod;
}
inline void do3(int x, int z) {
	st.add(1, dfn[x], dfn[x] + siz[x] - 1, z);
}
inline int do4(int x) {
	return st.query(1, dfn[x], dfn[x] + siz[x] - 1);
}

int main() {
	read(n); read(m); read(root); read(mod);
	for (int i = 1; i <= n; ++i)
		read(a[i]);
	int u = 0, v = 0;
	for (int i = 1; i != n; ++i) {
		read(u); read(v);
		insert(u, v);
		insert(v, u);
	}
	dfs1(root, root); dfs2(root, root);
	st.create(1, 1, cc);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		read(u);
		if (u == 1) {
			read(x); read(y); read(z);
			do1(x, y, z);
		}
		else if (u == 2) {
			read(x); read(y);
			printf("%d\n", do2(x, y));
		}
		else if (u == 3) {
			read(x); read(y);
			do3(x, y);
		}
		else if (u == 4) {
			read(x);
			printf("%d\n", do4(x));
		}
	}
	return 0;
}
void SegmentTree::create(int p, int l, int r) {
	tree[p].l = l;
	tree[p].r = r;
	tree[p].lazy = 0;
	if (l == r) {
		tree[p].sum = a[yvan[l]];
		return;
	}
	int mid = (l + r) >> 1;
	create(p << 1, l, mid);
	create(p << 1 | 1, mid + 1, r);
	UP(p);
}
void SegmentTree::add(int p, int l, int r, int v) {
	if (tree[p].l >= l && tree[p].r <= r) {
		(tree[p].sum += length(p) * v) %= mod;
		(tree[p].lazy += v) %= mod;
		return;
	}
	down(p);
	if (MID(p) >= l)	add(p << 1, l, r, v);
	if (MID(p) < r)		add(p << 1 | 1, l, r, v);
	UP(p);
}
int SegmentTree::query(int p, int l, int r) {
	if (tree[p].l >= l && tree[p].r <= r)
		return tree[p].sum;
	down(p);
	if (MID(p) < l)		return query(p << 1 | 1, l, r);
	if (MID(p) >= r)	return query(p << 1, l, r);
	return (query(p << 1 | 1, l, r) + query(p << 1, l, r)) % mod;
}