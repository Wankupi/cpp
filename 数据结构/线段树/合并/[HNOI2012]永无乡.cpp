#include <cstdio>
const int maxn = 100003;
int n = 0, m = 0, q = 0;
int rank[maxn];
int fa[maxn];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int root[maxn];
struct Node {
	int lc, rc;
	int sum;
	int id;
};
Node tr[maxn << 6];
int cT = 0;
void add(int &p, int L, int R, int x) {
	if (p == 0) p = ++cT;
	++tr[p].sum;
	if (L == R) {
		tr[p].id = x;
		return;
	}
	int mid = (L + R) >> 1;
	if (rank[x] <= mid)
		add(tr[p].lc, L, mid, x);
	else
		add(tr[p].rc, mid + 1, R, x);
}
int Combine(int p1, int p2) {
	if (p1 == 0 || p2 == 0) return p1 | p2;
	tr[p1].lc = Combine(tr[p1].lc, tr[p2].lc);
	tr[p1].rc = Combine(tr[p1].rc, tr[p2].rc);
	tr[p1].sum = tr[tr[p1].lc].sum + tr[tr[p1].rc].sum;
	return p1;
}
int Query(int p, int L, int R, int k) {
	if (k > tr[p].sum) return -1;
	if (L == R) return tr[p].id;
	int mid = (L + R) >> 1;
	if (tr[tr[p].lc].sum >= k)
		return Query(tr[p].lc, L, mid, k);
	else
		return Query(tr[p].rc, mid + 1, R, k - tr[tr[p].lc].sum);
}
void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y) return;
	root[y] = Combine(root[y], root[x]);
	fa[x] = y;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", rank + i);
		fa[i] = i;
		add(root[i], 1, n, i);
	}
	int opt = 0, x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		merge(x, y);
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i) {
		do
			opt = getchar();
		while (opt != 'Q' && opt != 'B');
		scanf("%d%d", &x, &y);
		if (opt == 'Q')
			printf("%d\n", Query(root[find(x)], 1, n, y));
		else
			merge(x, y);
	}
	return 0;
}