#include <cstdio>
int n = 0, m = 0;
int a[100003];
struct Query {
	Query() {}
	Query(int L, int R, int K, int ID, int Type) { l = L, r = R, k = K, id = ID, type = Type; }
	int l, r, k, id, type;
};
Query opt[300000];
int cnt = 0;
int tr[100003];
inline int lowbit(int x) { return x & -x; }
inline void add(int p, int v) {
	while (p <= n) {
		tr[p] += v;
		p += lowbit(p);
	}
}
inline int query(int p) {
	int sum = 0;
	while (p) {
		sum += tr[p];
		p -= lowbit(p);
	}
	return sum;
}
inline int sum(int l, int r) { return query(r) - query(l - 1); }
int ans[100003], queryCnt = 0;
Query q1[300000], q2[300000];
int change[200000];
void solve(int L, int R, int ql, int qr) {
	if (ql > qr) return;
	if (L == R) {
		for (int i = ql; i <= qr; ++i) {
			if (opt[i].type == 2)
				ans[opt[i].id] = L;
		}
		return;
	}
	int mid = (L + R) >> 1;
	int cL = 0, cR = 0, addcnt = 0;
	for (int i = ql; i <= qr; ++i) {
		if (opt[i].type == 1) {
			if (opt[i].k <= mid) {
				add(opt[i].id, opt[i].r);
				change[++addcnt] = i;
				q1[++cL] = opt[i];
			}
			else
				q2[++cR] = opt[i];
		}
		else {
			int cn = sum(opt[i].l, opt[i].r);
			if (cn >= opt[i].k) {
				q1[++cL] = opt[i];
			}
			else {
				opt[i].k -= cn;
				q2[++cR] = opt[i];
			}
		}
	}
	for (int i = 1; i <= addcnt; ++i)
		add(opt[change[i]].id, -opt[change[i]].r);
	for (int i = 1; i <= cL; ++i)
		opt[ql + i - 1] = q1[i];
	for (int i = 1; i <= cR; ++i)
		opt[ql + cL + i - 1] = q2[i];
	solve(L, mid, ql, ql + cL - 1);
	solve(mid + 1, R, ql + cL, qr);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		opt[++cnt] = Query(0, +1, a[i], i, 1);
	}
	int o = 0, l = 0, r = 0, k = 0;
	for (int i = 1; i <= m; ++i) {
		do
			o = getchar();
		while (o != 'Q' && o != 'C');
		if (o == 'Q') {
			scanf("%d%d%d", &l, &r, &k);
			opt[++cnt] = Query(l, r, k, ++queryCnt, 2);
		}
		else {
			scanf("%d%d", &l, &k);
			opt[++cnt] = Query(0, -1, a[l], l, 1);
			a[l] = k;
			opt[++cnt] = Query(0, +1, a[l], l, 1);
		}
	}
	solve(1, 1000000000, 1, cnt);
	for (int i = 1; i <= queryCnt; ++i)
		printf("%d\n", ans[i]);
	return 0;
}