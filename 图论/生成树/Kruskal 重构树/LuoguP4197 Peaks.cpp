/*
Kruskal 重构树
： 加新点，点权为边的权
树上倍增
找最大的father， 其权小于等于x
子树中 主席树
按dfs序插入
单点加
区间差分二分查询
查找第k大 -> 高度需离散化
*/
#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	int x = 0, c = getchar();
	while (c < '0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x;
}
const int maxn = 100003, maxP = maxn << 1;
int n = 0, m = 0, q = 0;
int h[maxn], H[maxn], mH = 0;
int head[maxP], nxt[maxP << 1], to[maxP << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int val[maxP], cP = 0;//点权（由边权化得）
inline int newPoint(int V) { val[++cP] = V; return cP; }
int zx[20][maxP]; //祖先
inline void Discretize() {
	sort(H + 1, H + n + 1);
	mH = unique(H + 1, H + n + 1) - H - 1;
	for (int i = 1; i <= n; ++i) h[i] = lower_bound(H + 1, H + mH + 1, h[i]) - H;
}
namespace Kruskal {
	struct Line {
		int u, e, w;
	};
	inline bool operator<(const Line &lhs, const Line &rhs) {
		return lhs.w < rhs.w;
	}
	Line li[maxn * 5];
	int fa[maxP];
	int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
	inline void merge(int x, int y) {
		fa[find(x)] = find(y);
	}
	inline void InPut() {
		for (int i = 1; i <= m; ++i) {
			li[i].u = read();
			li[i].e = read();
			li[i].w = read();
		}
	}
	void Kruskal() {
		InPut();
		sort(li + 1, li + m + 1);
		for (int i = 1; i <= n * 2; ++i) fa[i] = i;
		for (int i = 1; i <= m; ++i) {
			if (find(li[i].u) == find(li[i].e)) continue;
			int P = ::newPoint(li[i].w);
			::insert(P, find(li[i].u));
			::insert(P, find(li[i].e));
			//::zx[0][find(li[i].u)] = P;
			//::zx[0][find(li[i].e)] = P;
			merge(li[i].u, P);
			merge(li[i].e, P);
		}
	}
}
namespace SegTree {
	struct Node {
		int lc, rc;
		int s;
	};
	Node tr[maxP << 6];
	int cT = 0;
	void build(int &p, int L, int R) {
		if (p == 0) p = ++cT;
		if (L == R) return;
		int mid = (L + R) >> 1;
		build(tr[p].lc, L, mid);
		build(tr[p].rc, mid + 1, R);
	}
	void add(int &p, int L, int R, int x) { // +1
		tr[++cT] = tr[p];
		p = cT;
		if (L == R) { ++tr[p].s; return; }
		int mid = (L + R) >> 1;
		if (x <= mid) add(tr[p].lc, L, mid, x);
		else add(tr[p].rc, mid + 1, R, x);
		++tr[p].s;
	}
	int query(int p1, int p2, int L, int R, int k) { //第k大 p1-p2 不一定有解
		if (tr[p1].s - tr[p2].s < k) return -1;
		if (L == R) return L;
		int mid = (L + R) >> 1;
		if (tr[tr[p1].rc].s - tr[tr[p2].rc].s >= k) return query(tr[p1].rc, tr[p2].rc, mid + 1, R, k);
		else return query(tr[p1].lc, tr[p2].lc, L, mid, k - tr[tr[p1].rc].s + tr[tr[p2].rc].s);
	}
}
int dfn[maxP],siz[maxP], root[maxP], cdfn = 0;
void dfs(int x, int f) {
	dfn[x] = ++cdfn;
	siz[x] = 1;
	root[dfn[x]] = root[dfn[x] - 1];
	if (x <= n) SegTree::add(root[dfn[x]], 1, mH, h[x]);
	zx[0][x] = f;
	for (int j = 1; j <= 18; ++j) zx[j][x] = zx[j - 1][zx[j - 1][x]];
	for (int i = head[x]; i; i = nxt[i]) {
		dfs(to[i], x);
		siz[x] += siz[to[i]];
	}
}
inline int getTop(int x,int v) {
	for (int j = 18; ~j; --j)
		if (val[zx[j][x]] <= v) x = zx[j][x];
	return x;
}
inline int Query(int x, int v, int k) {
	int t = getTop(x, v);
	int r = SegTree::query(root[dfn[t] + siz[t] - 1], root[dfn[t] - 1], 1, mH, k);
	return r == -1 ? -1 : H[r];
}
int main() {
	cP = n = read(); m = read(); q = read();
	for (int i = 1; i <= n; ++i) H[i] = h[i] = read();
	Discretize();
	Kruskal::Kruskal();
	SegTree::build(root[0], 1, mH);
	dfs(cP, cP);
	int a = 0, b = 0, c = 0;
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		printf("%d\n", Query(a, b, c));
	}
	return 0;
}