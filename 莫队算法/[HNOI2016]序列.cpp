#include <cstdio>
#include <cmath>
#include <memory>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 100003;
int n = 0, m = 0;
ll a[maxn], f[maxn], g[maxn];
int pre[maxn], nxt[maxn];
int st[maxn], up = 0;
int mx[18][maxn], lg2[maxn];
int block = 0;
struct Query {
	int l, r, id;
} q[maxn];
inline bool operator<(const Query &lhs, const Query &rhs) { return (lhs.l / block) == (rhs.l / block) ? lhs.r < rhs.r : lhs.l < rhs.l; }
void init() {
	st[up = 0] = 0;
	for (int i = 1; i <= n; ++i) {
		while (a[st[up]] >= a[i]) --up;
		pre[i] = st[up];
		st[++up] = i;
		f[i] = f[pre[i]] + (i - pre[i]) * a[i];
	}
	st[up = 0] = n + 1;
	for (int i = n; i >= 1; --i) {
		while (a[st[up]] >= a[i]) --up;
		nxt[i] = st[up];
		st[++up] = i;
		g[i] = g[nxt[i]] + (nxt[i] - i) * a[i];
	}
	for (int i = 1; i <= n; ++i) mx[0][i] = i;
	for (int j = 1; j <= 17; ++j)
		for (int i = 1; i <= n - (1 << j) + 1; ++i)
			mx[j][i] = (a[mx[j - 1][i]] <= a[mx[j - 1][i + (1 << (j - 1))]] ? mx[j - 1][i] : mx[j - 1][i + (1 << (j - 1))]);
	lg2[1] = 0;
	for (int i = 2; i <= n; ++i) lg2[i] = lg2[i / 2] + 1;
}
inline int min_pos(int l, int r) {
	int j = lg2[r - l + 1];
	return a[mx[j][l]] <= a[mx[j][r - (1 << j) + 1]] ? mx[j][l] : mx[j][r - (1 << j) + 1];
}

inline ll L_value(int l, int r) {
	int p = min_pos(l, r);
	return g[l] - g[p] + a[p] * (r - p + 1);
}
inline ll R_value(int l, int r) {
	int p = min_pos(l, r);
	return a[p] * (p - l + 1) + f[r] - f[p];
}
ll ans[maxn], res = 0;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
	a[0] = a[n + 1] = -0x3f3f3f3f3f3f3f3f;
	init();
	block = sqrt(n) + 1;
	for (int i = 1; i <= m; ++i)
		scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i) {
		while (r < q[i].r) res += R_value(l, ++r);
		while (q[i].r < r) res -= R_value(l, r--);
		while (q[i].l < l) res += L_value(--l, r);
		while (l < q[i].l) res -= L_value(l++, r);
		ans[q[i].id] = res;
	}
	for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
	return 0;
}