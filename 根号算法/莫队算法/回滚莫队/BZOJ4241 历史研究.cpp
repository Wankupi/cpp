#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
int const maxn = 100003;
int n = 0, m = 0, block = 0;
int x[maxn], cX = 0;
ll X[maxn];
struct Query {
	int l, r;
	int id;
};
inline bool operator<(Query const &lhs, Query const &rhs) {
	return lhs.l / block == rhs.l / block ? lhs.r < rhs.r : lhs.l < rhs.l;
}
Query q[maxn];
inline int belong(int i) { return (i - 1) / block + 1; }
long long res = 0;
int cnt[maxn];
inline void add(int v) {
	++cnt[v];
	if (cnt[v] * X[v] > res) res = cnt[v] * X[v];
}
long long ans[maxn];
int main() {
	scanf("%d %d", &n, &m);
	block = int(ceil(sqrt(n)));
	for (int i = 1; i <= n; ++i)
		scanf("%d", x + i), X[i] = x[i];
	sort(X + 1, X + n + 1);
	cX = unique(X + 1, X + n + 1) - X - 1;
	for (int i = 1; i <= n; ++i)
		x[i] = lower_bound(X + 1, X + cX + 1, x[i]) - X;
	for (int i = 1; i <= m; ++i)
		scanf("%d %d", &q[i].l, &q[i].r), q[i].id = i;
	sort(q + 1, q + m + 1);
	for (int A = 1; A <= m;) {
		res = 0;
		memset(cnt, 0, sizeof cnt);
		int id = q[A].l / block;
		int R = id * block + block - 1;
		while (A <= m && q[A].r <= R) {
			for (int i = q[A].l; i <= q[A].r; ++i)
				add(x[i]);
			ans[q[A].id] = res;
			for (int i = q[A].l; i <= q[A].r; ++i)
				--cnt[x[i]];
			res = 0;
			++A;
		}
		int cur = R;
		while (A <= m && q[A].l / block == id) {
			while (cur < q[A].r)
				add(x[++cur]);
			ll before = res;
			for (int i = q[A].l; i <= R; ++i)
				add(x[i]);
			ans[q[A].id] = res;
			for (int i = q[A].l; i <= R; ++i)
				--cnt[x[i]];
			res = before;
			++A;
		}
	}
	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}