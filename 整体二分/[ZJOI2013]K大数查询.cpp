#include <cstdio>
typedef long long ll;
const int maxn = 50005;
struct Query {
	Query() {}
	Query(int L, int R, int val, int ID, int Type) { l = L, r = R, v = val, id = ID, type = Type; }
	int l, r, v, id, type;
};
int n = 0, m = 0;

namespace SqSum {
	inline int lowbit(int x) { return x & -x; }
	struct TrAr {
		ll tr[maxn];
		void add(int p, int v) { while (p <= n) { tr[p] += v; p += lowbit(p); } }
		ll query(int p) { ll sum = 0; while (p) { sum += tr[p]; p -= lowbit(p); } return sum; }
	};
	TrAr d, di;
	inline void add(int l, int r, ll v) {
		d.add(l, v); d.add(r + 1, -v);
		di.add(l, l * v); di.add(r + 1, -v * (r + 1));
	}
	inline ll query(int p) { return (p + 1) * d.query(p) - di.query(p); }
	inline ll query(int l, int r) { return query(r) - query(l - 1); }
}

Query opt[maxn], qL[maxn], qR[maxn];
int ans[maxn];
int change[maxn];
void solve(int L, int R, int ql, int qr) { // qiu di K da
	if (ql > qr) return;
	if (L == R) {
		for (int i = ql; i <= qr; ++i)
			if (opt[i].type == 2) ans[opt[i].id] = L;
		return;
	}
	int mid = (L + R) >> 1;
	int cL = 0, cR = 0, addCnt = 0;
	for (int i = ql; i <= qr; ++i) {
		if (opt[i].type == 1) {
			if (opt[i].v > mid) {
				SqSum::add(opt[i].l, opt[i].r, 1);
				change[++addCnt] = i;
				qR[++cR] = opt[i];
			}
			else qL[++cL] = opt[i];
		}
		else {
			ll cn = SqSum::query(opt[i].l, opt[i].r);
			if (cn >= opt[i].v) qR[++cR] = opt[i];
			else {
				opt[i].v -= cn;
				qL[++cL] = opt[i];
			}
		}
	}
	for (int i = 1; i <= addCnt; ++i)
		SqSum::add(opt[change[i]].l, opt[change[i]].r, -1);
	for (int i = 1; i <= cL; ++i)
		opt[ql + i - 1] = qL[i];
	for (int i = 1; i <= cR; ++i)
		opt[ql + cL + i - 1] = qR[i];
	solve(L, mid, ql, ql + cL - 1);
	solve(mid + 1, R, ql + cL, qr);
}
int main() {
	scanf("%d%d", &n, &m);
	int cntQuery = 0, minV = +500000, maxV = -500000;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d%d", &opt[i].type, &opt[i].l, &opt[i].r, &opt[i].v);
		if (opt[i].type == 2) opt[i].id = ++cntQuery;
		else {
			if (opt[i].v < minV) minV = opt[i].v;
			if (opt[i].v > maxV) maxV = opt[i].v;
		}
	}
	solve(minV, maxV, 1, m);
	for (int i = 1; i <= cntQuery; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
