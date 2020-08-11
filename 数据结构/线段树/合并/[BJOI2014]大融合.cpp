#include <cstdio>
const int maxn = 100003, maxP = maxn << 4;
int n = 0, q = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
struct Query {
	int type, x, y;
};
Query qu[maxn];
int dfn[maxn], siz[maxn], dep[maxn], cdfn = 0;
void dfs(int x, int f) {
	dfn[x] = ++cdfn;
	siz[x] = 1;
	dep[x] = dep[f] + 1;
 	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs(to[i], x);
			siz[x] += siz[to[i]];
		}
}
inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
int root[maxn];
int lc[maxP], rc[maxP];
int sum[maxP], cT = 0;
void add(int &p, int L, int R, int x) {
	if (p == 0) p = ++cT;
	if (L == R) { sum[p] += 1; return; }
	int mid = (L + R) >> 1;
	if (x <= mid) add(lc[p], L, mid, x);
	else add(rc[p], mid + 1, R, x);
	sum[p] = sum[lc[p]] + sum[rc[p]];
}
int query(int p, int L, int R, int l, int r) {
	if (p == 0) return 0;
	if (l <= L && R <= r) return sum[p];
	int mid = (L + R) >> 1, ret = 0;
	if (l <= mid) ret += query(lc[p], L, mid, l, r);
	if (r > mid) ret += query(rc[p], mid + 1, R, l, r);
	return ret;
}
int combine(int p1, int p2, int L, int R) {
	if (p1 == 0 || p2 == 0) return p1 | p2;
	if (L == R) { sum[p1] += sum[p2]; return p1; }
	int mid = (L + R) >> 1;
	lc[p1] = combine(lc[p1], lc[p2], L, mid);
	rc[p1] = combine(rc[p1], rc[p2], mid + 1, R);
	sum[p1] = sum[lc[p1]] + sum[rc[p1]];
	return p1;
}
int fa[maxn];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
	x = find(x); y = find(y);
	if (dep[x] < dep[y]) swap(x, y); // ensure the root is as same as on the real tree
	fa[x] = y;
	root[y] = combine(root[y], root[x], 1, n);
}
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= q; ++i) {
		do qu[i].type = getchar(); while (qu[i].type != 'A' && qu[i].type != 'Q');
		scanf("%d%d", &qu[i].x, &qu[i].y);
		if (qu[i].type == 'A') {
			insert(qu[i].x, qu[i].y);
			insert(qu[i].y, qu[i].x);
		}
	}
	for (int i = 1; i <= n; ++i) if (!dfn[i]) dfs(i, i);
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		add(root[i], 1, n, dfn[i]);
	}
	for (int i = 1; i <= q; ++i) {
		if (qu[i].type == 'A') merge(qu[i].x, qu[i].y);
		else {
			int &x = qu[i].x, &y = qu[i].y;
			if (dep[x] < dep[y]) swap(x, y);
			int top = find(y);
			int A = query(root[top], 1, n, dfn[top], dfn[top] + siz[top] - 1), B = query(root[top], 1, n, dfn[x], dfn[x] + siz[x] - 1);
			long long ans = ((long long)A - B) * B;
			printf("%lld\n", ans);
		}
	}
	return 0;
}