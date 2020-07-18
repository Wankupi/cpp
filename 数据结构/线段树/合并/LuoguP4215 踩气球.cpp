/*
并查集维护区间左端点
对每个点开一棵线段树
合并
*/
#include <cstdio>
inline int read() {
	int x = 0, c = 0;
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x;
}
inline int min(int a, int b) { return a < b ? a : b; }
const int maxn = 100003, maxP = maxn * 20;
int n = 0, m = 0;
int a[maxn];
int root[maxn];
int lc[maxP], rc[maxP], sum[maxP], c = 0;
void Add(int &p, int L, int R, int x) {
	if (!p) p = ++c;
	++sum[p];
	if (L == R) return;
	int mid = (L + R) >> 1;
	if (x <= mid)
		Add(lc[p], L, mid, x);
	else
		Add(rc[p], mid + 1, R, x);
}
int query_del(int &p, int L, int R, int x) {
	if (p == 0) return 0;
	if (x <= L) {
		int tem = sum[p];
		p = 0; // delete the Node which is no use after
		return tem;
	}
	int tem = 0, mid = (L + R) >> 1;
	if (x <= mid && lc[p]) tem += query_del(lc[p], L, mid, x);
	if (rc[p]) tem += query_del(rc[p], mid + 1, R, x);
	sum[p] = (lc[p] ? sum[lc[p]] : 0) + (rc[p] ? sum[rc[p]] : 0);
	return tem;
}
int Combine(int p1, int p2, int L, int R) {
	if (p1 == 0 || p2 == 0) return p1 | p2;
	if (L == R)
		sum[p1] += sum[p2];
	else {
		int mid = (L + R) >> 1;
		lc[p1] = Combine(lc[p1], lc[p2], L, mid);
		rc[p1] = Combine(rc[p1], rc[p2], mid + 1, R);
		sum[p1] = (lc[p1] ? sum[lc[p1]] : 0) + (rc[p1] ? sum[rc[p1]] : 0);
	}
	return p1;
}
int fa[maxn], left[maxn];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { // make y the new root
	x = find(x);
	y = find(y);
	left[x] = left[y] = min(left[x], left[y]);
	fa[x] = y;
}
int main() {
	n = read();
	m = read();
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	int l = 0, r = 0;
	for (int i = 1; i <= m; ++i) {
		l = read();
		r = read();
		Add(root[r], 1, n, l);
	}
	for (int i = 1; i <= n; ++i)
		left[i] = fa[i] = i;
	int q = 0, lastAns = 0, x = 0;
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i) {
		x = (read() + lastAns - 1) % n + 1;
		if (--a[x] == 0) {
			if (x > 1 && a[x - 1] == 0) {
				root[x] = Combine(root[find(x - 1)], root[x], 1, n);
				merge(x - 1, x);
			}
			if (x < n && a[x + 1] == 0) {
				root[x] = Combine(root[x], root[find(x + 1)], 1, n);
				merge(x + 1, x);
			}
			lastAns += query_del(root[x], 1, n, left[x]);
		}
		printf("%d\n", lastAns);
	}
	return 0;
}