#include <cstdio>
typedef long long ll;
inline ll max(ll a, ll b) { return a < b ? b : a; }
inline ll min(ll a, ll b) { return a < b ? a : b; }
int a[50005];
struct Value { ll sum, mx, lmx, rmx; };
Value tree[200005];
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
void Change(int p,int L,int R) {
	if(L==R) {
		tree[p].sum = tree[p].mx = tree[p].lmx = tree[p].rmx = qr;
		return;
	}
	int mid = (L+R)>>1;
	if (ql <= mid) Change(p << 1, L, mid);
	else Change(p << 1 | 1, mid + 1, R);
	tree[p] = Combine(tree[p << 1], tree[p << 1 | 1]);
}
int main() {
	int n = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	create(1, 1, n);
	int m = 0, opt = 0;
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &opt, &ql, &qr);
		if(opt == 0) Change(1,1,n);
		else printf("%lld\n", Query(1, 1, n).mx);
	}
	return 0;
}