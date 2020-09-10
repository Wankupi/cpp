#include <cstdio>
int const maxn = 300003;
int n = 0, a[maxn];
int stMx[maxn], tMx = 0, stMi[maxn], tMi = 0;

struct Data {
	Data(int MinValue = 0, int times = 0) : mv(MinValue), t(times) {}
	int mv, t;
};
Data tr[maxn << 2];
inline Data operator|(Data const &lhs, Data const &rhs) {
	if (lhs.mv == rhs.mv)
		return Data(lhs.mv, lhs.t + rhs.t);
	else
		return lhs.mv < rhs.mv ? lhs : rhs;
}
int lazy[maxn << 2];
void Create(int p, int L, int R) {
	if (L == R) {
		tr[p] = Data(L, 1);
		return;
	}
	int mid = (L + R) >> 1;
	Create(p << 1, L, mid);
	Create(p << 1 | 1, mid + 1, R);
	tr[p] = tr[p << 1] | tr[p << 1 | 1];
}
void pushDown(int p) {
	tr[p << 1].mv += lazy[p];
	tr[p << 1 | 1].mv += lazy[p];
	lazy[p << 1] += lazy[p];
	lazy[p << 1 | 1] += lazy[p];
	lazy[p] = 0;
}
void modify(int p, int L, int R, int l, int r, int v) {
	if (l <= L && R <= r) {
		tr[p].mv += v;
		lazy[p] += v;
		return;
	}
	pushDown(p);
	int mid = (L + R) >> 1;
	if (l <= mid) modify(p << 1, L, mid, l, r, v);
	if (r > mid) modify(p << 1 | 1, mid + 1, R, l, r, v);
	tr[p] = tr[p << 1] | tr[p << 1 | 1];
}
Data query(int p, int L, int R, int l, int r) {
	if (l <= L && R <= r) return tr[p];
	pushDown(p);
	int mid = (L + R) >> 1;
	if (r <= mid)
		return query(p << 1, L, mid, l, r);
	else if (l > mid)
		return query(p << 1 | 1, mid + 1, R, l, r);
	else
		return query(p << 1, L, mid, l, r) | query(p << 1 | 1, mid + 1, R, l, r);
}
int main() {
	scanf("%d", &n);
	int x = 0, y = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &x, &y);
		a[x] = y;
	}
	Create(1, 1, n);
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		while (tMx > 0 && a[stMx[tMx]] < a[i]) {
			modify(1, 1, n, stMx[tMx - 1] + 1, stMx[tMx], a[i] - a[stMx[tMx]]);
			--tMx;
		}
		stMx[++tMx] = i;
		while (tMi > 0 && a[stMi[tMi]] > a[i]) {
			modify(1, 1, n, stMi[tMi - 1] + 1, stMi[tMi], -(a[i] - a[stMi[tMi]]));
			--tMi;
		}
		stMi[++tMi] = i;
		Data res = query(1, 1, n, 1, i);
		if (res.mv == i) ans += res.t;
	}
	printf("%lld", ans);
	return 0;
}