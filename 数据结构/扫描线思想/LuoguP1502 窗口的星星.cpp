#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long ll;
int const maxn = 10000 << 2;
struct Op {
	int x, y, Y;
	ll val;
};
inline bool operator<(const Op &lhs, const Op &rhs) {
	if (lhs.x == rhs.x)
		return lhs.val < rhs.val;
	return lhs.x < rhs.x;
}
int n = 0, W = 0, H = 0, cnt = 0;
int ys[maxn], cY = 0;
Op a[maxn];
ll mx[maxn << 2], lazy[maxn << 2];
inline void pushDown(int p) {
	if (lazy[p] != 0) {
		mx[p << 1] += lazy[p];
		mx[p << 1 | 1] += lazy[p];
		lazy[p << 1] += lazy[p];
		lazy[p << 1 | 1] += lazy[p];
		lazy[p] = 0;
	}
}
void add(int p, int L, int R, int l, int r, ll v) {
	if (l <= L && R <= r) {
		lazy[p] += v;
		mx[p] += v;
		return;
	}
	pushDown(p);
	int mid = (L + R) >> 1;
	if (l <= mid) add(p << 1, L, mid, l, r, v);
	if (r > mid) add(p << 1 | 1, mid + 1, R, l, r, v);
	mx[p] = std::max(mx[p << 1], mx[p << 1 | 1]);
}
void clear() {
	cnt = cY = 0;
}
int main() {
	int T = 0;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		scanf("%d %d %d", &n, &W, &H);
		int x = 0, y = 0;
		ll l = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d %d %lld", &x, &y, &l);
			a[++cnt] = Op{x, y, y + H - 1, +l};
			a[++cnt] = Op{x + W, y, y + H - 1, -l};
			ys[++cY] = y;
			ys[++cY] = y + H - 1;
		}
		std::sort(ys + 1, ys + cY + 1);
		cY = std::unique(ys + 1, ys + cY + 1) - ys - 1;
		for (int i = 1; i <= cnt; ++i) {
			a[i].y = std::lower_bound(ys + 1, ys + cY + 1, a[i].y) - ys;
			if (a[i].Y) a[i].Y = std::lower_bound(ys + 1, ys + cY + 1, a[i].Y) - ys;
		}
		std::sort(a + 1, a + cnt + 1);
		ll ans = 0;
		for (int i = 1; i <= cnt; ++i) {
			add(1, 1, cY, a[i].y, a[i].Y, a[i].val);
			ans = std::max(ans, mx[1]);
		}
		printf("%lld\n", ans);
		clear();
	}
	return 0;
}