#include <cstdio>
const int maxn = 35003;
int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
inline int max(int a, int b) { return a < b ? b : a; }
int n = 0, k = 0;
int a[maxn], last[maxn], pre[maxn];
int f[maxn];
int ma[maxn << 2], lazy[maxn << 2];

inline void pushUp(int p) {
	ma[p] = max(ma[p << 1], ma[p << 1 | 1]);
}
inline void pushDown(int p) {
	if (lazy[p] == 0) return;
	ma[p << 1] += lazy[p];
	ma[p << 1 | 1] += lazy[p];
	lazy[p << 1] += lazy[p];
	lazy[p << 1 | 1] += lazy[p];
	lazy[p] = 0;
}
void Create(int p, int L, int R) {
	lazy[p] = 0;
	if (L == R) {
		ma[p] = f[L];
		return;
	}
	int mid = (L + R) >> 1;
	Create(p << 1, L, mid);
	Create(p << 1 | 1, mid + 1, R);
	pushUp(p);
}
void add(int p, int L, int R, int l, int r) {
	if (l <= L && R <= r) {
		ma[p] += 1;
		lazy[p] += 1;
		return;
	}
	pushDown(p);
	int mid = (L + R) >> 1;
	if (l <= mid) add(p << 1, L, mid, l, r);
	if (r > mid) add(p << 1 | 1, mid + 1, R, l, r);
	pushUp(p);
}
int queryMax(int p, int L, int R, int x) { //前缀最大值
	if (R <= x) return ma[p];
	pushDown(p);
	int mid = (L + R) >> 1;
	if (x <= mid) return queryMax(p<<1, L, mid, x);
	return max(queryMax(p << 1, L, mid, x), queryMax(p << 1 | 1, mid + 1, R, x));
}
int main() {
	n = read(); k = read();
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
		pre[i] = last[a[i]];
		last[a[i]] = i;
	}
	int w = 0;
	for (int i = 1; i <= n; ++i) {
		if (pre[i] == 0) ++w;
		f[i] = w;
	}
	for (int j = 2; j <= k; ++j) {
		Create(1, 0, n);
		for (int i = 1; i <= n; ++i) {
			add(1, 0, n, pre[i], i - 1);
			f[i] = queryMax(1, 0, n, i - 1);
		}
	}
	printf("%d", f[n]);
	return 0;
}