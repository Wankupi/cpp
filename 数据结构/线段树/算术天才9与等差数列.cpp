#include <cstdio>
#include <algorithm>
using namespace std;

int const maxn = 300003;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

struct Node {
	int mi, mx;
	int pre, last;
	int d;
	void set(int x) {
		mi = mx = pre = last = x;
		d = 0;
	}
};

Node operator+(Node const &lhs, Node const &rhs) {
	Node r;
	r.mi = min(lhs.mi, rhs.mi);
	r.mx = max(lhs.mx, rhs.mx);
	r.pre = lhs.pre;
	r.last = rhs.last;
	r.d = gcd(gcd(lhs.d, rhs.d), abs(lhs.last - rhs.pre));
	return r;
}

Node tr[maxn << 2];

void modify(int p, int L, int R, int x, int v) {
	if (L == R) {
		tr[p].set(v);
		return;
	}
	int mid = (L + R) >> 1;
	if (x <= mid) modify(p << 1, L, mid, x, v);
	else modify(p << 1 | 1, mid + 1, R, x, v);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}

Node query(int p, int L, int R, int l, int r) {
	if (l <= L && R <= r) return tr[p];
	int mid = (L + R) >> 1;
	if (r <= mid) return query(p << 1, L, mid, l, r);
	else if (l > mid) return query(p << 1 | 1, mid + 1, R, l, r);
	else return query(p << 1, L, mid, l, r) + query(p << 1 | 1, mid + 1, R, l, r);
}

int a[maxn];

void build(int p, int L, int R) {
	if (L == R) {
		tr[p].set(a[L]);
		return;
	}
	int mid = (L + R) >> 1;
	build(p << 1, L, mid);
	build(p << 1 | 1, mid + 1, R);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}

inline bool check(Node const d, int k, int N) {
	if (d.mi + k * (N - 1) != d.mx) return false;
	if (N != 1 && d.d != k) return false;
	return true;
}

int main() {
	int n = 0, m = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	build(1, 1, n);
	int opt = 0, x = 0, y = 0, z = 0;
	int cntYes = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &opt, &x, &y);
		x ^= cntYes; y ^= cntYes;
		if (opt == 1) {
			modify(1, 1, n, x, y);
		}
		else {
			scanf("%d", &z);
			z ^= cntYes;
			Node r = query(1, 1, n, x, y);
			bool right = check(r, z, y - x + 1);
			cntYes += right;
			printf(right ? "Yes\n" : "No\n");
		}
	}
	return 0;
}
