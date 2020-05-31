#include <cstdio>
typedef long long ll;
const ll mod = 1000000007;
int n = 0, m = 0;
ll a[100003], t1[100003], t2[100003];
inline int lowbit(int x) { return x & -x; }
inline void add(ll *tr, int p, ll val) {
	while (p <= n) {
		tr[p] = (tr[p] + val) % mod;
		p += lowbit(p);
	}
}
inline ll query(ll *tr, int p) {
	ll sum = 0;
	while (p) {
		sum = (sum + tr[p]) % mod;
		p -= lowbit(p);
	}
	return sum;
}
ll pow(ll x, ll a) {
	ll ret = 1;
	while (a) {
		if (a & 1) ret = ret * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return ret;
}
ll query(ll *tr, int l, int r) {
	return (query(tr, r) - query(tr, l - 1) + mod) % mod;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", a + i);
		t1[i] = (t1[i - 1] + a[i]) % mod;
		t2[i] = (t2[i - 1] + a[i] * a[i]) % mod;
	}
	for (int i = n; i; --i) {
		t1[i] = (t1[i] - t1[i - lowbit(i)] + mod) % mod;
		t2[i] = (t2[i] - t2[i - lowbit(i)] + mod) % mod;
	}
	int opt = 0, x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &opt, &x, &y);
		if (opt == 1) {
			add(t1, x, (y - a[x] + mod) % mod);
			add(t2, x, ((long long)y * y % mod - a[x] * a[x] % mod + mod) % mod);
			a[x] = y;
		}
		else {
			ll invlen = pow(y - x + 1, mod - 2);
			ll s1 = query(t1, x, y), s2 = query(t2, x, y);
			ll avg = s1 * invlen % mod;
			ll ans = (s2 - 2 * s1 % mod * avg % mod + mod) % mod;
			ans = (ans * invlen % mod + avg * avg % mod) % mod;
			printf("%lld\n", ans);
		}
	}
	return 0;
}