#include <cstdio>
typedef long long ll;
ll fac[100010];
ll pow(ll x, ll a, ll mod) {
	ll ret = 1;
	while (a) {
		if (a & 1) ret = ret * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return ret;
}
inline ll inv(ll a, ll p) { return pow(a, p - 2, p); }
inline ll binom(ll n, ll m, ll p) {
	if (m > n) return 0;
	return fac[n] * inv(fac[m], p) % p * inv(fac[n - m], p) % p;
}
ll Lucas(ll n, ll m, ll p) {
	if (m == 0) return 1;
	return Lucas(n / p, m / p, p) * binom(n % p, m % p, p) % p;
}
int main() {
	int T = 0;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		int n = 0, m = 0, p = 0;
		scanf("%d%d%d", &n, &m, &p);
		fac[0] = 1;
		for (int i = 1; i <= p; ++i)
			fac[i] = fac[i - 1] * i % p;
		printf("%lld\n", Lucas(n + m, n, p));
	}
	return 0;
}