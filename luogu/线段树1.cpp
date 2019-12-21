#include <iostream>
using namespace std;
using ll = long long;
ll a[100001] = { 0 };
struct ST {
	int l = 0;
	int r = 0;
	ll sum = 0;
	ll lazy = 0;
};
ST tree[100000 * 4 + 5];
inline void SumUp(int p) {
	tree[p].sum = tree[p * 2].sum + tree[p * 2 + 1].sum;
}
inline int length(int p) {
	return tree[p].r - tree[p].l + 1;
}
inline void lazyDown(int p) {
	if (tree[p].lazy) {
		tree[p * 2].sum += tree[p].lazy * length(2 * p);
		tree[p * 2].lazy += tree[p].lazy;
		tree[p * 2 + 1].sum += tree[p].lazy * length(2 * p + 1);
		tree[p * 2 + 1].lazy += tree[p].lazy;
		tree[p].lazy = 0;
	}
}
void build(int p, int l, int r) {
	auto &d = tree[p];
	d.l = l; d.r = r;
	if (l == r) {
		d.sum = a[l];
		return;
	}
	int mid = (l + r) / 2;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
	SumUp(p);
}

void plusA(int p, int l, int r, ll v) {
	auto &d = tree[p];
	if (l <= d.l && r >= d.r) {
		d.sum += length(p) * v;
		d.lazy += v;
		return;
	}
	lazyDown(p);
	int mid = (d.l + d.r) / 2;
	if (l <= mid) plusA(p * 2, l, r, v);
	if (r > mid) plusA(p * 2 + 1, l, r, v);
	SumUp(p);
}

ll query(int p, int l, int r) {
	if (l <= tree[p].l && r >= tree[p].r)
		return tree[p].sum;
	lazyDown(p);
	int mid = (tree[p].l + tree[p].r) / 2;
	ll ans = 0;
	if (l <= mid) ans += query(p * 2, l, r);
	if (r > mid)ans += query(p * 2 + 1, l, r);
	return ans;
}

int main() {
	int n = 0, m = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n);
	ll mode = 0, x = 0, y = 0, k = 0;
	while (m--) {
		cin >> mode;
		if (mode & 1) {
			cin >> x >> y >> k;
			plusA(1, x, y, k);
		}
		else {
			cin >> x >> y;
			cout << query(1, x, y) << endl;
		}
	}
	return 0;
}