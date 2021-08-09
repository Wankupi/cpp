#include <cstdio>
typedef long long ll;
int const maxn = 100003;
inline int max(int a, int b) { return a < b ? b : a; }
inline int lowbit(int x) { return x & -x; }

int n = 0;
ll m = 0;
int a[maxn], r[maxn];

int tr[maxn];
inline void add(int p, int v) {
	while (p <= n) {
		tr[p] += v;
		p += lowbit(p);
	}
}
inline int query(int p) {
	int sum = 0;
	while (p > 0) {
		sum += tr[p];
		p -= lowbit(p);
	}
	return sum;
}
inline int get(int v) {
	int L = 1, R = n, mid = 0;
	while (L <= R) {
		mid = (L + R) >> 1;
		if (query(mid) >= v)
			R = mid - 1;
		else
			L = mid + 1;
	}
	return R + 1;
}
int main() {
	scanf("%d%lld", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = n; i >= 1; --i) {
		r[i] = query(a[i]);
		add(a[i], 1);
	}

	for (int i = 1; i < n; ++i) {
		m += r[n - i];
		r[n - i] = m % (i + 1ll);
		m /= i + 1ll;
	}

	for (int i = 1; i <= n; ++i)
		tr[i] = lowbit(i);
	for (int i = 1; i <= n; ++i) {
		a[i] = get(r[i] + 1);
		add(a[i], -1);
	}
	for (int i = 1; i <= n; ++i)
		printf("%d ", a[i]);
	return 0;
}