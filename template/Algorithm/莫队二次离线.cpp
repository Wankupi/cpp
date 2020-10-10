#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
int const maxn = 100003;
int n = 0, k = 0, m = 0, block = 0;
int a[maxn];
ll ans[maxn], pre[maxn];
vector<int> eqK;
int t[16384];
inline int count(int x) { int r = 0; while (x) { r += (x & 1); x >>= 1; } return r; }
struct Query {
	int l, r, id, op;
};
inline bool operator<(Query const &lhs, Query const &rhs) { return lhs.l / block == rhs.l / block ? lhs.r < rhs.r : lhs.l < rhs.l; }
Query q[maxn];
vector<Query> q2[maxn];
void solve_first() {
	sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i) {
		if (r < q[i].r) {
			ans[q[i].id] += pre[q[i].r] - pre[r];
			q2[l - 1].push_back(Query{r + 1, q[i].r, q[i].id, -1});
			r = q[i].r;
		}
		if (l > q[i].l) {
			ans[q[i].id] -= pre[l - 1] - pre[q[i].l - 1];
			q2[r].push_back(Query{q[i].l, l - 1, q[i].id, + 1});
			if (k == 0) ans[q[i].id] += l - q[i].l;
			l = q[i].l;
		}
		if (r > q[i].r) {
			ans[q[i].id] -= pre[r] - pre[q[i].r];
			q2[l - 1].push_back(Query{q[i].r + 1, r, q[i].id, +1});
			r = q[i].r;
		}
		if (l < q[i].l) {
			ans[q[i].id] += pre[q[i].l - 1] - pre[l - 1];
			q2[r].push_back(Query{l, q[i].l - 1, q[i].id, -1});
			if (k == 0) ans[q[i].id] -= q[i].l - l;
			l = q[i].l;
		}
	}
}
int main() {
	scanf("%d %d %d", &n, &m, &k); block = int(sqrt(n));
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	for (int i = 0; i < 16384; ++i) if (count(i) == k) eqK.push_back(i);
	for (int i = 1; i <= n; ++i) {
		for (auto v : eqK) ++t[a[i] ^ v];
		pre[i] = pre[i - 1] + t[a[i]];
	}
	solve_first();
	memset(t, 0, sizeof t);
	for (int i = 1; i <= n; ++i) {
		for (int v : eqK) t[a[i] ^ v]++;
		for (auto j : q2[i])
			for (int p = j.l; p <= j.r; ++p)
				ans[j.id] += j.op * t[a[p]];
	}
	for (int i = 1; i <= m; ++i) ans[q[i].id] += ans[q[i - 1].id];
	for (int i = 1; i <= m; ++i) if (k == 0) ans[q[i].id] -= q[i].r - q[i].l + 1;
	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}