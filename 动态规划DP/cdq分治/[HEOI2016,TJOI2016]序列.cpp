#include <cstdio>
#include <algorithm>
using namespace std;
int const maxn = 100003, N = 100000;

int n = 0, m = 0;

int a[maxn], mx[maxn], mi[maxn], f[maxn];

inline int lowbit(int x) { return x & -x; }
int tr[maxn];
inline void set(int p, int v) {
	for (; p <= N; p += lowbit(p))
		if (v > tr[p]) tr[p] = v;
		else break;
}
inline void unset(int p) { for (; p <= N && tr[p]; p += lowbit(p)) tr[p] = 0; }
inline int query(int p) {
	int r = 0;
	for (; p > 0; p -= lowbit(p)) if (tr[p] > r) r = tr[p];
	return r;
}

int p[maxn];

void cdq(int l, int r) {
	if (l == r) {
		f[l] += 1;
		return;
	}
	int mid = (l + r) >> 1;
	cdq(l, mid);

	for (int i = l; i <= r; ++i) p[i] = i;
	sort(p + l, p + mid + 1, [](int i, int j) { return mx[i] < mx[j]; });
	sort(p + mid + 1, p + r + 1, [](int i, int j) { return a[i] < a[j]; });

	for (int p1 = l, p2 = mid + 1; p2 <= r; ++p2) {
		while (p1 <= mid && mx[p[p1]] <= a[p[p2]]) {
			set(a[p[p1]], f[p[p1]]);
			++p1;
		}
		f[p[p2]] = max(f[p[p2]], query(mi[p[p2]]));
	}
	for (int i = l; i <= mid; ++i) unset(a[i]);
	cdq(mid + 1, r);
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		mx[i] = mi[i] = a[i];
	}
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		mx[x] = max(mx[x], y);
		mi[x] = min(mi[x], y);
	}	
	cdq(1, n);
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = max(ans, f[i]);
	printf("%d", ans);
	return 0;
}