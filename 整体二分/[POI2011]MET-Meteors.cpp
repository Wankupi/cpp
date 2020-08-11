#include <cstdio>
#include <vector>
const int maxn = 300003;
using namespace std;
int n = 0, m = 0, k = 0;
int o[maxn], p[maxn];
vector<int> places[maxn];
struct Query {
	Query() {}
	Query(int L, int R, int A, int Id, int Type) { l = L, r = R, a = A, id = Id, type = Type; }
	int l, r, a, id, type;
};
Query opt[maxn << 1], qL[maxn << 1], qR[maxn << 1];
int tr[maxn];
inline int lowbit(int x) { return x & -x; }
inline void add(int p, int v) { while (p <= m) { tr[p] += v; p += lowbit(p); } }
inline int query(int p) { int sum = 0; while (p) { sum += tr[p]; p -= lowbit(p); } return sum; }
inline void add(int l, int r, int v) { if (l <= r) { add(l, v); add(r + 1, -v); } else { add(1, v); add(r + 1, -v); add(l, v); } }
int ans[maxn];
int change[maxn];
void solve(int ql, int qr, int L, int R) { // 操作处理到[l,r]，二分范围到[L,R]
	if (ql > qr) return;
	if (L == R) {
		for (int i = ql; i <= qr; ++i)
			if (opt[i].type == 2)
				ans[opt[i].id] = L;
		return;
	}
	int mid = (L + R) >> 1;
	int cL = 0, cR = 0, AdCnt = 0;
	for (int i = ql; i <= qr; ++i) {
		if (opt[i].type == 1) {
			if (opt[i].id <= mid) {
				add(opt[i].l, opt[i].r, opt[i].a);
				change[++AdCnt] = i;
				qL[++cL] = opt[i];
			}
			else qR[++cR] = opt[i];
		}
		else {
			int cn = 0;
			for (unsigned int j = 0; j < places[opt[i].id].size() && cn < opt[i].a; ++j)
				cn += query(places[opt[i].id][j]);
			if (cn >= opt[i].a) qL[++cL] = opt[i];
			else {
				opt[i].a -= cn;
				qR[++cR] = opt[i];
			}
		}
	}
	for (int i = 1; i <= AdCnt; ++i)
		add(opt[change[i]].l, opt[change[i]].r, -opt[change[i]].a);
	for (int i = 1; i <= cL; ++i) opt[ql + i - 1] = qL[i];
	for (int i = 1; i <= cR; ++i) opt[ql + cL + i - 1] = qR[i];
	solve(ql, ql + cL - 1, L, mid);
	solve(ql + cL, qr, mid + 1, R);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", o + i);
		places[o[i]].push_back(i);
	}
	for (int i = 1; i <= n; ++i)
		scanf("%d", p + i);
	scanf("%d", &k);
	int l = 0, r = 0, a = 0;
	for (int i = 1; i <= k; ++i) {
		scanf("%d%d%d", &l, &r, &a);
		opt[i] = Query(l, r, a, i, 1);
	}
	for (int i = 1; i <= n; ++i)
		opt[i + k] = Query(0, 0, p[i], i, 2);
	solve(1, n + k, 1, k + 1);
	for (int i = 1; i <= n; ++i)
		if (ans[i] <= k) printf("%d\n", ans[i]);
		else puts("NIE");
	return 0;
}