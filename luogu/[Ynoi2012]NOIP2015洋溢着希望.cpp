#include <cctype>
#include <cmath>
#include <cstdio>
typedef long long ll;
const int maxn = 200001;
inline int read() {
	int x = 0, c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return x;
}
int n = 0, a[maxn];
struct Node {
	double si, co;
	ll lazy;
};
Node tree[maxn * 4 + 50];
inline void pushUp(int p) {
	tree[p].si = tree[p << 1].si + tree[p << 1 | 1].si;
	tree[p].co = tree[p << 1].co + tree[p << 1 | 1].co;
}
inline void pushDown(int p) {
	double s = sin(tree[p].lazy), c = cos(tree[p].lazy);
	Node &lt = tree[p << 1], &rt = tree[p << 1 | 1];

	double ls = lt.si, lc = lt.co;
	lt.si = ls * c + lc * s;
	lt.co = lc * c - ls * s;

	double rs = rt.si, rc = rt.co;
	rt.si = rs * c + rc * s;
	rt.co = rc * c - rs * s;

	lt.lazy += tree[p].lazy;
	rt.lazy += tree[p].lazy;
	tree[p].lazy = 0;
}
void create(int p, int L, int R) {
	if (L == R) {
		tree[p].si = sin(a[L]);
		tree[p].co = cos(a[L]);
		return;
	}
	int mid = (L + R) >> 1;
	create(p << 1, L, mid);
	create(p << 1 | 1, mid + 1, R);
	pushUp(p);
}
int opt = 0, l = 0, r = 0, v = 0;
double sv = 0, cv = 0; // sin v  cos v
void add(int p, int L, int R) {
	if (l <= L && R <= r) {
		tree[p].lazy += v;
		double s = tree[p].si, c = tree[p].co;
		tree[p].si = s * cv + c * sv;
		tree[p].co = c * cv - s * sv;
		return;
	}
	if (tree[p].lazy) pushDown(p);
	int mid = (L + R) >> 1;
	if (l <= mid) add(p << 1, L, mid);
	if (r > mid) add(p << 1 | 1, mid + 1, R);
	pushUp(p);
}
double query(int p, int L, int R) {
	if (l <= L && R <= r)
		return tree[p].si;
	if (tree[p].lazy) pushDown(p);
	int mid = (L + R) >> 1;
	double ans = 0.0;
	if (l <= mid) ans += query(p << 1, L, mid);
	if (r > mid) ans += query(p << 1 | 1, mid + 1, R);
	return ans;
}
int main() {
	n = read();
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	create(1, 1, n);
	int m = read();
	for (int i = 1; i <= m; ++i) {
		opt = read(); l = read(); r = read();
		if (opt == 1) {
			v = read();
			sv = sin(v); cv = cos(v);
			add(1, 1, n);
		}
		else
			printf("%.1lf\n", query(1, 1, n));
	}
	return 0;
}