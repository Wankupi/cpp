#include <cstdio>
typedef long long ll;
inline ll max(ll a, ll b) { return a < b ? b : a; }
inline ll min(ll a, ll b) { return a < b ? a : b; }
int n = 0;
int a[10005];
ll sum[10005];
struct Value { ll sum, mx, lmx, rmx; };
Value tree[40005];
Value Combine(const Value &a, const Value &b) {
	Value ret;
	ret.sum = a.sum + b.sum;
	ret.mx = max(a.rmx + b.lmx, max(a.mx, b.mx));
	ret.lmx = max(a.lmx, a.sum + b.lmx);
	ret.rmx = max(b.rmx, a.rmx + b.sum);
	return ret;
}
void create(int p, int L, int R) {
	if (L == R) {
		Value &t = tree[p];
		t.sum = t.lmx = t.rmx = t.mx = a[L];
		return;
	}
	int mid = (L + R) >> 1;
	create(p << 1, L, mid);
	create(p << 1 | 1, mid + 1, R);
	tree[p] = Combine(tree[p << 1], tree[p << 1 | 1]);
}
int ql = 0, qr = 0;
Value Query(int p, int L, int R) {
	if (ql <= L && R <= qr) return tree[p];
	int mid = (L + R) >> 1;
	if (qr <= mid) return Query(p << 1, L, mid);
	else if (ql > mid) return Query(p << 1 | 1, mid + 1, R);
	else return Combine(Query(p << 1, L, mid), Query(p << 1 | 1, mid + 1, R));
}
inline Value query(int l, int r) {
	ql = l; qr = r;
	return Query(1, 1, n);
}
int main() {
	int T = 0;
	scanf("%d", &T);
	for (int _T = 1; _T <= T; ++_T) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			sum[i] = sum[i - 1] + a[i];
		}
		create(1, 1, n);
		int m = 0;
		scanf("%d", &m);
		int l1 = 0, r1 = 0, l2 = 0, r2 = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
			ll ans = -0x7fffffffffffffff;
			if (r1 < l2) {
				ans = query(l1, r1).rmx + sum[l2 - 1] - sum[r1] + query(l2, r2).lmx;
			}
			else {
				ans = query(l2, r1).mx;
				if (l1 < l2)
					ans = max(ans, query(l1, l2 - 1).rmx + query(l2, r2).lmx);
				if (r1 < r2)
					ans = max(ans, query(l1, r1).rmx + query(r1 + 1, r2).lmx);
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}