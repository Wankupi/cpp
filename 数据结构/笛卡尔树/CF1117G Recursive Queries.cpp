#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
int const maxn = 1000003;
int n = 0, m = 0;
int a[maxn];
struct Query {
	int l, r, id;
};
inline bool cmp1ofQuery(Query const &lhs, Query const &rhs) { return lhs.l < rhs.l; }
inline bool cmp2ofQuery(Query const &lhs, Query const &rhs) { return lhs.r > rhs.r; }
Query q[maxn];
int cl[maxn], cr[maxn];
int st[maxn], top = 0;
void getControl() {
	cl[1] = 1;
	st[top = 1] = 1;
	for (int i = 2; i <= n; ++i) {
		while (top && a[i] > a[st[top]]) cr[st[top--]] = i - 1;
		cl[i] = st[top] + 1;
		st[++top] = i;
	}
	while (top) cr[st[top--]] = n;
}
int nod[maxn];
inline bool cmp1ofNode(int a, int b) { return cl[a] < cl[b]; }
inline bool cmp2ofNode(int a, int b) { return cr[a] > cr[b]; }
ll tri[maxn], tr0[maxn];
inline int lowbit(int x) { return x & -x; }
inline void add(ll *ar, int p, int v) { while (p <= n) { ar[p] += v; p += lowbit(p); } }
inline ll query(ll *ar, int p) { ll sum = 0; while (p > 0) { sum += ar[p]; p -= lowbit(p); } return sum; }
inline ll query(ll *ar, int l, int r) { return query(ar, r) - query(ar, l - 1); }
ll ans[maxn];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= m; ++i) scanf("%d", &q[i].l);
	for (int i = 1; i <= m; ++i) scanf("%d", &q[i].r);
	for (int i = 1; i <= m; ++i) q[i].id = i;
	getControl();
	for (int i = 1; i <= n; ++i) nod[i] = i;

	sort(nod + 1, nod + n + 1, cmp1ofNode);
	sort(q + 1, q + m + 1, cmp1ofQuery);
	int cur = 1;
	for (int i = 1; i <= n; ++i) tri[i] = tri[i - 1] + cl[i], tr0[i] = 0;
	for (int i = n; i >= 1; --i) tri[i] -= tri[i - lowbit(i)];
	for (int i = 1; i <= m; ++i) {
		while (cur <= n && cl[nod[cur]] <= q[i].l) {
			int x = nod[cur++];
			add(tri, x, -cl[x]);
			add(tr0, x, +1);
		}
		ll v = query(tri, q[i].l, q[i].r) + query(tr0, q[i].l, q[i].r) * q[i].l;
		ans[q[i].id] -= v;
	}

	sort(nod + 1, nod + n + 1, cmp2ofNode);
	sort(q + 1, q + m + 1, cmp2ofQuery);
	cur = 1;
	for (int i = 1; i <= n; ++i) tri[i] = tri[i - 1] + cr[i], tr0[i] = 0;
	for (int i = n; i >= 1; --i) tri[i] -= tri[i - lowbit(i)];
	for (int i = 1; i <= m; ++i) {
		while (cur <= n && cr[nod[cur]] >= q[i].r) {
			int x = nod[cur++];
			add(tri, x, -cr[x]);
			add(tr0, x, +1);
		}
		ll v = query(tri, q[i].l, q[i].r) + query(tr0, q[i].l, q[i].r) * q[i].r;
		ans[q[i].id] += v;
	}

	for (int i = 1; i <= m; ++i) ans[q[i].id] += q[i].r - q[i].l + 1;
	for (int i = 1; i <= m; ++i)
		printf("%lld ", ans[i]);
	return 0;
}