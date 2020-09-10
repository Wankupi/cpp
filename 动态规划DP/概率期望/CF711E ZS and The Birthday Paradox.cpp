#include <cstdio>
typedef long long ll;
ll const mod = 1000003;
ll pow(ll x, ll b) {
//	b %= mod - 1;
	ll r = 1;
	while (b) {
		if (b & 1) r = r * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return r;
}
inline ll count2(ll x) {
	ll r = 0;
	while (x % 2 == 0) {
		++r;
		x /= 2;
	}
	return r;
}
int main() {
	ll n = 0, k = 0;
	scanf("%lld %lld", &n, &k);
	ll tem = 1;
	while ((1ll << tem) < k) tem += 1;
	if (tem > n) {
		printf("1 1");
		return 0;
	}
	tem = 0;
	for (ll i = k - 1; i >= 1; i >>= 1)
		tem += (i >> 1);
	ll d = pow(2, n), z = 1;
	for (int i = 1; i < k; ++i) {
		z = z * (d - i + mod) % mod;
		if (z == 0) break;
	}
	ll m = pow(d, k - 1);
	ll inv = pow(pow(2, tem), mod - 2);
	z = z * inv % mod;
	m = m * inv % mod;
	z = (m - z + mod) % mod;
	printf("%lld %lld", z, m);
	return 0;
}