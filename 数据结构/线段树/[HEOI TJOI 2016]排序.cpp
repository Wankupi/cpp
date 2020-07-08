#include <cstdio>
const int maxn = 100003;
int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int n = 0, m = 0, q = 0;
int a[maxn];
int opt[maxn], qL[maxn], qR[maxn];
namespace Seg {
	int Cut = 0;
	int cnt[maxn << 2], lazy[maxn << 2];
	inline void pushUP(int p) {
		cnt[p] = cnt[p << 1] + cnt[p << 1 | 1];
	}
	inline void pushDown(int p, int L, int R, int mid) {
		if (lazy[p] == 0) return;
		lazy[p << 1] = lazy[p << 1 | 1] = lazy[p];
		if (lazy[p] == 1) {
			cnt[p << 1] = mid - L + 1;
			cnt[p << 1 | 1] = R - mid;
		}
		else cnt[p << 1] = cnt[p << 1 | 1] = 0;
		lazy[p] = 0;
	}
	void Create(int p, int L, int R) {
		if (L == R) {
			cnt[p] = (a[L] > Cut);
			lazy[p] = 0;
			return;
		}
		int mid = (L + R) >> 1;
		Create(p << 1, L, mid);
		Create(p << 1 | 1, mid + 1, R);
		lazy[p] = 0;
		pushUP(p);
	}
	int queryCount1(int p, int L, int R, int l, int r) {
		if (l <= L && R <= r)
			return cnt[p];
		int mid = (L + R) >> 1;
		pushDown(p, L, R, mid);
		int sum = 0;
		if (l <= mid) sum += queryCount1(p << 1, L, mid, l, r);
		if (r > mid) sum += queryCount1(p << 1 | 1, mid + 1, R, l, r);
		return sum;
	}
	void set1(int p, int L, int R, int l, int r) {
		if (l <= L && R <= r) {
			cnt[p] = R - L + 1;
			lazy[p] = 1;
			return;
		}
		int mid = (L + R) >> 1;
		pushDown(p, L, R, mid);
		if (l <= mid) set1(p << 1, L, mid, l, r);
		if (r > mid) set1(p << 1 | 1, mid + 1, R, l, r);
		pushUP(p);
	}
	void set0(int p, int L, int R, int l, int r) {
		if (l <= L && R <= r) {
			cnt[p] = 0;
			lazy[p] = -1;
			return;
		}
		int mid = (L + R) >> 1;
		pushDown(p, L, R, mid);
		if (l <= mid) set0(p << 1, L, mid, l, r);
		if (r > mid) set0(p << 1 | 1, mid + 1, R, l, r);
		pushUP(p);
	}
	inline void sortSheng(int L, int R) {
		int c = queryCount1(1, 1, n, L, R);
		if (L <= R - c) set0(1, 1, n, L, R - c);
		if (R - c + 1 <= R) set1(1, 1, n, R - c + 1, R);
	}
	inline void sortJiang(int L, int R) {
		int c = queryCount1(1, 1, n, L, R);
		if (L <= L + c - 1) set1(1, 1, n, L, L + c - 1);
		if (L + c <= R) set0(1, 1, n, L + c, R);
	}
}
bool check(int val) {
	Seg::Cut = val;
	Seg::Create(1, 1, n);
	for (int i = 1; i <= m; ++i) {
		if (opt[i] == 0) Seg::sortSheng(qL[i], qR[i]);
		else Seg::sortJiang(qL[i], qR[i]);
	}
	return Seg::queryCount1(1, 1, n, q, q) == 0;
}
int main() {
	n = read(); m = read(); for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= m; ++i) {
		opt[i] = read(); qL[i] = read(); qR[i] = read();
	}
	q = read();
	int L = 1, R = n, mid = 0;
	while (L <= R) {
		mid = (L + R) >> 1;
		if (check(mid)) R = mid - 1;
		else L = mid + 1;
	}
	printf("%d", R + 1);
	return 0;
}