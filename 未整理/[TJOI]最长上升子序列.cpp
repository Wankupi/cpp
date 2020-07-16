#include <cstdio>
const int maxn = 100001;
inline int max(int a, int b) { return a < b ? b : a; }
inline int lowbit(int x) { return x & -x; }
int n = 0;
int a[maxn], p[maxn];
int tr[maxn], mx[maxn];
void add(int p, int x) { while (p <= n) { tr[p] += x; p += lowbit(p); } }
int qSum(int p) {
	int ret = 0;
	while (p) { ret += tr[p]; p -= lowbit(p); }
	return ret;
}
void set(int p, int x) {
	while (p <= n) {
		mx[p] = max(mx[p], x);
		p += lowbit(p);
	}
}
int qMax(int p) {
	int ret = -0x7fffffff;
	while (p) {
		ret = max(ret, mx[p]);
		p -= lowbit(p);
	}
	return ret;
}
int getPos(int k) {
	int l = 1, r = n, mid = 0, c = 0;
	while (l <= r) {
		mid = (l + r) >> 1;
		c = mid - qSum(mid);
		if (c < k)	l = mid + 1;
		else if (c >= k) r = mid - 1;
	}
	return r + 1;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = n; i > 0; --i) {
		p[i] = getPos(a[i] + 1);
		add(p[i], 1);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		int t = qMax(p[i]) + 1;
		ans = max(ans, t);
		printf("%d\n", ans);
		set(p[i], t);
	}
	return 0;
}