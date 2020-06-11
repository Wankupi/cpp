// 分块 区间加 区间统计

#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
typedef long long ll;
int n = 0, m = 0;
int block = 0;
int L[1000003], R[1000003];
ll a[1000003], b[1000003];
ll t[1007];
inline int p(int x) { return (L[x] - 1) / block + 1; }
inline void CopyAndSort(int x) {
	for (int i = L[x]; i <= R[x]; ++i) b[i] = a[i];
	sort(b + L[x], b + R[x] + 1);
}
void add(int l, int r, ll val) {
	if (L[l] == L[r]) {
		if (L[l] == l && R[l] == r) t[p(l)] += val;
		else {
			for (int i = l; i <= r; ++i) a[i] += val;
			CopyAndSort(l);
		}
	}
	else {
		if (l == L[l]) t[p(l)] += val;
		else {
			for (int i = l; i <= R[l]; ++i) a[i] += val;
			CopyAndSort(l);
		}
		for (int i = R[l] + 1; L[i] != L[r]; i = R[i] + 1)
			t[p(i)] += val;
		if (r == R[r]) t[p(r)] += val;
		else {
			for (int i = L[r]; i <= r; ++i) a[i] += val;
			CopyAndSort(r);
		}
	}
}
int cnt(int l, int r, ll val) {
	int ret = 0;
	if (L[l] == L[r]) {
		if (L[l] == l && R[l] == r) ret += (b + R[l] + 1) - lower_bound(b + l, b + R[l] + 1, val - t[p(l)]);
		else for (int i = l; i <= r; ++i) if (a[i] + t[p(l)] >= val) ++ret;
	}
	else {
		if (l == L[l]) ret += (b + R[l] + 1) - lower_bound(b + l, b + R[l] + 1, val - t[p(l)]);
		else for (int i = l; i <= R[l]; ++i) if (a[i] + t[p(l)] >= val) ++ret;
		for (int i = R[l] + 1; L[i] != L[r]; i = R[i] + 1)
			ret += (b + R[i] + 1) - lower_bound(b + i, b + R[i] + 1, val - t[p(i)]);
		if (r == R[r]) ret += (b + R[r] + 1) - lower_bound(b + L[r], b + R[r] + 1, val - t[p(r)]);
		else for (int i = L[r]; i <= r; ++i) if (a[i] + t[p(r)] >= val) ++ret;
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	block = sqrt(n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", a + i);
		b[i] = a[i];
		L[i] = ((i - 1) / block) * block + 1;
		R[i] = L[i] + block - 1;
		if (R[i] > n) R[i] = n;
	}
	for (int i = 1; i <= n; i = R[i] + 1)
		sort(b + i, b + R[i] + 1);
	int opt = 0;
	ll x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		do
			opt = getchar();
		while (opt != 'A' && opt != 'M');
		scanf("%lld%lld%lld", &x, &y, &z);
		if (opt == 'M')
			add(x, y, z);
		else
			printf("%d\n", cnt(x, y, z));
	}
	return 0;
}