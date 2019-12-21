#include <iostream>
using namespace std;
using ll = long long;
ll mod = 1000000;
ll a[100001] = { 0 };
struct ST {
	int l = 0;
	int r = 0;
	ll sum = 0;
	ll lazyP = 0;
	ll lazyM = 1;
};
ST tree[100000 * 4 + 5];
void SumUp(int p) {
	tree[p].sum = (tree[p * 2].sum + tree[p * 2 + 1].sum) % mod;
}
inline int length(int p) {
	return tree[p].r - tree[p].l + 1;
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

void lazyDown(int p) {
	if (tree[p].lazyM != 1) {
		tree[2 * p].sum *= tree[p].lazyM;
		tree[2 * p].lazyM *= tree[p].lazyM;
		tree[2 * p].lazyP *= tree[p].lazyM;
		tree[2 * p + 1].sum *= tree[p].lazyM;
		tree[2 * p + 1].lazyM *= tree[p].lazyM;
		tree[2 * p + 1].lazyP *= tree[p].lazyM;
		//
		tree[2 * p].sum %= mod;
		tree[2 * p].lazyM %= mod;
		tree[2 * p].lazyP %= mod;
		tree[2 * p + 1].sum %= mod;
		tree[2 * p + 1].lazyM %= mod;
		tree[2 * p + 1].lazyP %= mod;
		tree[p].lazyM = 1;
	}
	if (tree[p].lazyP) {
		tree[p * 2].sum += tree[p].lazyP * length(2 * p) % mod;
		tree[p * 2].lazyP += tree[p].lazyP;
		tree[p * 2 + 1].sum += tree[p].lazyP * length(2 * p + 1) % mod;
		tree[p * 2 + 1].lazyP += tree[p].lazyP;
		//
		tree[2 * p].sum %= mod;
		tree[2 * p].lazyP %= mod;
		tree[2 * p + 1].sum %= mod;
		tree[2 * p + 1].lazyP %= mod;
		tree[p].lazyP = 0;
	}
}

void AreaPlus(int p, int l, int r, ll v) {
	auto &d = tree[p];
	if (l <= d.l && r >= d.r) {
		d.sum = (length(p) * v + d.sum) % mod;
		d.lazyP = (v + d.lazyP) % mod;
		return;
	}
	lazyDown(p);
	int mid = (d.l + d.r) / 2;
	if (l <= mid) AreaPlus(p * 2, l, r, v);
	if (r > mid) AreaPlus(p * 2 + 1, l, r, v);
	SumUp(p);
}

void AreaMult(int p, int l, int r, ll v) {
	auto &d = tree[p];
	if (l <= d.l && r >= d.r) {
		d.sum = d.sum * v % mod;
		d.lazyM = d.lazyM * v % mod;
		d.lazyP = d.lazyP * v % mod;
		return;
	}
	lazyDown(p);
	int mid = (d.l + d.r) / 2;
	if (l <= mid) AreaMult(p * 2, l, r, v);
	if (r > mid) AreaMult(p * 2 + 1, l, r, v);
	SumUp(p);
}

ll query(int p, int l, int r) {
	if (l <= tree[p].l && r >= tree[p].r)
		return tree[p].sum;
	lazyDown(p);
	int mid = (tree[p].l + tree[p].r) / 2;
	ll ans = 0;
	if (l <= mid) ans += query(p * 2, l, r);
	if (r > mid) ans += query(p * 2 + 1, l, r);
	return ans % mod;
}

int main() {
	int n = 0, m = 0;
	cin >> n >> m >> mod;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n);
	int mode = 0, x = 0, y = 0;
	ll k = 0;
	while (m--) {
		cin >> mode;
		if (mode == 1) {
			cin >> x >> y >> k;
			AreaMult(1, x, y, k);
		}
		else if (mode == 2) {
			cin >> x >> y >> k;
			AreaPlus(1, x, y, k);
		}
		else {
			cin >> x >> y;
			cout << query(1, x, y) << endl;
		}
	}
	return 0;
}