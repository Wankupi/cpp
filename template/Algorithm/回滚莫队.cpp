#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
int const maxn = 200003;
int n = 0, m = 0, block = 0;
int a[maxn], A[maxn], cA = 0;

struct Query {
	int l, r, id;
};
inline bool operator<(Query const &lhs, Query const &rhs) {
	return lhs.l / block == rhs.l / block ? lhs.r < rhs.r : lhs.l < rhs.l;
}
Query q[maxn];
int mL[maxn], mR[maxn];
int ans[maxn];
int main() {
	scanf("%d", &n);
	block = int(sqrt(n));
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		A[i] = a[i];
	}
	sort(A + 1, A + n + 1);
	cA = unique(A + 1, A + n + 1) - A - 1;
	for (int i = 1; i <= n; ++i)
		a[i] = lower_bound(A + 1, A + cA + 1, a[i]) - A;
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	sort(q + 1, q + m + 1);
	int Ans = 0;
	for (int i = 1; i <= m;) {
		memset(mL, 0, sizeof mL);
		memset(mR, 0, sizeof mR);
		int id = q[i].l / block;
		int R = id * block + block + 1;
		while (q[i].l / block == id && q[i].r <= R) {
			Ans = 0;
			for (int j = q[i].l; j <= q[i].r; ++j) {
				if (mL[a[j]] == 0) mL[a[j]] = j;
				Ans = std::max(Ans, j - mL[a[j]]);
			}
			ans[q[i].id] = Ans;
			for (int j = q[i].l; j <= q[i].r; ++j)
				mL[a[j]] = 0;
			++i;
		}
		Ans = 0;
		int qr = R;
		while (q[i].l / block == id) {
			while (qr < q[i].r) {
				++qr;
				if (mL[a[qr]] == 0) mL[a[qr]] = qr;
				mR[a[qr]] = qr;
				Ans = std::max(Ans, qr - mL[a[qr]]);
			}
			int before = Ans;
			for (int j = R; j >= q[i].l; --j) {
				if (mR[a[j]] == 0) mR[a[j]] = j;
				Ans = std::max(Ans, mR[a[j]] - j);
			}
			ans[q[i].id] = Ans;
			for (int j = R; j >= q[i].l; --j)
				if (mR[a[j]] == j) mR[a[j]] = 0;
			Ans = before;
			++i;
		}
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}