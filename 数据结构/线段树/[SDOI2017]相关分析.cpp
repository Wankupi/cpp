#include <cstdio>

int const maxn = 400003;
typedef long long ll;
typedef double ld;

int n = 0, m = 0;
int X[maxn], Y[maxn];
ld s[maxn], s2[maxn];

struct Node {
	ld x, y, xy, x2;
	ld lazyS, lazyT;
	unsigned char lazyO;
	long double getA(int len) const {
		return (xy - x * y / len) / (x2 - x * x / len);
	}

	void clearLazy() {
		lazyS = lazyT = 0;
		lazyO = 0;
	}
	void set1(ll S, ll T, int l, int r) {
		ld len = r - l + 1;
		xy = xy + S * y + T * x + len * S * T;
		x2 = x2 + 2.0 * S * x + len * S * S;
		x = x + len * S;
		y = y + len * T;
		if (lazyO <= 1) lazyO = 1;
		lazyS += S;
		lazyT += T;
	}
	void set2(ll S, ll T, int l, int r) {
		ld len = r - l + 1;
		xy = len * S * T + ld(S + T) * (s[r] - s[l - 1]) + (s2[r] - s2[l - 1]);
		x2 = len * S * S + 2.0 * S * (s[r] - s[l - 1]) + (s2[r] - s2[l - 1]);
		x = len * S + (s[r] - s[l - 1]);
		y = len * T + (s[r] - s[l - 1]);
		lazyO = 2;
		lazyS = S; lazyT = T;
	}
};
inline Node operator+(Node const &lhs, Node const &rhs) {
	return Node{lhs.x + rhs.x, lhs.y + rhs.y, lhs.xy + rhs.xy, lhs.x2 + rhs.x2, 0, 0, 0};
}
Node tr[maxn];

void build(int p, int L, int R) {
	if (L == R) {
		tr[p].x = X[L];
		tr[p].y = Y[L];
		tr[p].xy = ld(X[L]) * Y[L];
		tr[p].x2 = ld(X[L]) * X[L];
		return;
	}
	int mid = (L + R) >> 1;
	build(p << 1, L, mid);
	build(p << 1 | 1, mid + 1, R);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}

inline void pushdown(int p, int L, int R) {
	if (L == R || tr[p].lazyO == 0) return;
	int mid = (L + R) >> 1;
	if (tr[p].lazyO == 1) {
		tr[p << 1].set1(tr[p].lazyS, tr[p].lazyT, L, mid);
		tr[p << 1 | 1].set1(tr[p].lazyS, tr[p].lazyT, mid + 1, R);
	}
	else {
		tr[p << 1].set2(tr[p].lazyS, tr[p].lazyT, L, mid);
		tr[p << 1 | 1].set2(tr[p].lazyS, tr[p].lazyT, mid + 1, R);
	}
	tr[p].clearLazy();
}

int opt = 0, l = 0, r = 0, _s = 0, _t = 0;

Node query(int p, int L, int R) {
	if (l <= L && R <= r) return tr[p];
	pushdown(p, L, R);
	int mid = (L + R) >> 1;
	if (r <= mid)
		return query(p << 1, L, mid);
	else if (l > mid)
		return query(p << 1 | 1, mid + 1, R);
	else
		return query(p << 1, L, mid) + query(p << 1 | 1, mid + 1, R);
}

void modify(int p, int L, int R) {
	if (l <= L && R <= r) {
		if (opt == 2) tr[p].set1(_s, _t, L, R);
		else tr[p].set2(_s, _t, L, R);
		return;
	}
	pushdown(p, L, R);
	int mid = (L + R) >> 1;
	if (l <= mid) modify(p << 1, L, mid);
	if (r > mid) modify(p << 1 | 1, mid + 1, R);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", X + i);
	for (int i = 1; i <= n; ++i)
		scanf("%d", Y + i);
	build(1, 1, n);
	for (int i = 1; i <= n; ++i) {
		s[i] = s[i - 1] + i;
		s2[i] = s2[i - 1] + ld(i) * i;
	}

	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &opt, &l, &r);
		if (opt == 1) {
			Node res = query(1, 1, n);
			printf("%.6Lf\n", res.getA(r - l + 1));
		}
		else {
			scanf("%d %d\n", &_s, &_t);
			modify(1, 1, n);
		}
	}
	return 0;
}