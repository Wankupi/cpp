#include <cstdio>
#include <cctype>

int const maxn = 4000003;
inline int max(int a, int b) { return a < b ? b : a; }
inline int min(int a, int b) { return a < b ? a : b; }

inline int read() {
	int x = 0, c = getchar();
	while (!isdigit(c))
		c = getchar();
	while (isdigit(c))
		x = 10 * x + c - '0', c = getchar();
	return x;
}

int n = 0, m = 0, q = 0;

inline int o(int p, int x) { return p * m + x; }

int a[maxn << 2];

int len[maxn << 2];
int lmx[maxn << 2], rmx[maxn << 2], val[maxn << 2];

int q1[maxn], q2[maxn];
void merge(int res, int p1, int p2) {
	int h1 = 1, h2 = 1, t1 = 0, t2 = 0;
	for (int l = 1, r = 1; r <= m; ++r) {
		while (h1 <= t1 && rmx[o(p1, q1[t1])] > rmx[o(p1, r)]) --t1;
		q1[++t1] = r;
		while (h2 <= t2 && lmx[o(p2, q2[t2])] > lmx[o(p2, r)]) --t2;
		q2[++t2] = r;
		while (h1 <= t1 && h2 <= t2 && rmx[o(p1, q1[h1])] + lmx[o(p2, q2[h2])] < r - l + 1) {
			if (q1[h1] == l) ++h1;
			if (q2[h2] == l) ++h2;
			++l;
		}
		val[o(res, r)] = max(max(val[o(p1, r)], val[o(p2, r)]), r - l + 1);
	}
	for (int i = 1; i <= m; ++i) lmx[o(res, i)] = (lmx[o(p1, i)] == len[p1] ? len[p1] + lmx[o(p2, i)] : lmx[o(p1, i)]);
	for (int i = 1; i <= m; ++i) rmx[o(res, i)] = (rmx[o(p2, i)] == len[p2] ? rmx[o(p1, i)] + len[p2] : rmx[o(p2, i)]);
}


void build(int p, int L, int R) {
	len[p] = R - L + 1;
	if (L == R) {
		for (int i = 1; i <= m; ++i) {
			int j = o(p, i);
			lmx[j] = rmx[j] = val[j] = a[o(L, i)];
		}
		return;
	}
	int mid = (L + R) >> 1;
	build(p << 1, L, mid);
	build(p << 1 | 1, mid + 1, R);
	merge(p, p << 1, p << 1 | 1);
}

void modify(int p, int L, int R, int x, int y) {
	if (L == R) {
		lmx[o(p, y)] = rmx[o(p, y)] = val[o(p, y)] ^= 1;
		return;
	}
	int mid = (L + R) >> 1;
	if (x <= mid) modify(p << 1, L, mid, x, y);
	else modify(p << 1 | 1, mid + 1, R, x, y);
	merge(p, p << 1, p << 1 | 1);
}

void query(int p, int L, int R, int l, int r) {
	if (l <= L && R <= r) {
		merge(0, 0, p);
		return;
	}
	int mid = (L + R) >> 1;
	if (l <= mid) query(p << 1, L, mid, l, r);
	if (r > mid) query(p << 1 | 1, mid + 1, R, l, r);
}

int main() {
	n = read(); m = read(); q = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			a[o(i, j)] = read();
	build(1, 1, n);
	int opt = 0, l = 0, s = 0, r = 0, t = 0;
	for (int _t = 1; _t <= q; ++_t) {
		opt = read(); l = read(); s = read();
		if (opt == 0) {
			modify(1, 1, n, l, s);
		}
		else {
			r = read(); t = read();
			for (int i = 1; i <= m; ++i) {
				int j = o(0, i);
				lmx[j] = rmx[j] = val[j] = 0;
			}
			query(1, 1, n, l, r);
			int ans = 0;
			for (int i = s; i <= t; ++i)
				ans = max(ans, min(i - s + 1, val[o(0, i)]));
			printf("%d\n", ans);
		}
	}
	return 0;
}