#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 300003;
int n = 0, m = 0;
int a[maxn], b[maxn], tot = 0;
struct Que {
	Que() {}
	Que(int L, int R, int K, int ID, int TYPE) { l = L, r = R, k = K, id = ID, type = TYPE; }
	int l, r, k, id, type;
};
Que q[maxn + 50000];
int tr[maxn];
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
int ans[50003];
Que q1[maxn + 50000], q2[maxn + 50000];
int change[maxn];
void solve(int L, int R, int ql, int qr) {
	if (ql > qr) return;
	if (L == R) {
		for (int i = ql; i <= qr; ++i)
			if (q[i].type == 1)
				ans[q[i].id] = L;
		return;
	}
	int mid = (L + R) >> 1;
	int cntL = 0, cntR = 0, addcnt = 0;
	for (int i = ql; i <= qr; ++i) {
		if (q[i].type == 0) {
			if (q[i].k <= mid) {
				add(q[i].id, 1);
				change[++addcnt] = q[i].id;
				q1[++cntL] = q[i];
			}
			else
				q2[++cntR] = q[i];
		}
		else {
			int cn = sum(q[i].l, q[i].r);
			if (q[i].k <= cn)
				q1[++cntL] = q[i];
			else {
				q[i].k -= cn;
				q2[++cntR] = q[i];
			}
		}
	}
	for (int i = 1; i <= addcnt; ++i) add(change[i], -1);
	for (int i = 1; i <= cntL; ++i) q[ql + i - 1] = q1[i];
	for (int i = 1; i <= cntR; ++i) q[ql + cntL + i - 1] = q2[i];
	solve(L, mid, ql, ql + cntL - 1);
	solve(mid + 1, R, ql + cntL, qr);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	tot = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; ++i) {
		a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
		q[i] = Que(i, i, a[i], i, 0);
	}
	int l = 0, r = 0, k = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &l, &r, &k);
		q[i + n] = Que(l, r, k, i, 1);
	}
	solve(1, tot, 1, n + m);
	for (int i = 1; i <= m; ++i)
		printf("%d\n", b[ans[i]]);
	return 0;
}