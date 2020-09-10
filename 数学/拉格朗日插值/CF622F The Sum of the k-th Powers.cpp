#include <cstdio>
typedef long long ll;
ll const mod = 1000000007;
int const maxk = 1000007;
ll n = 0, k = 0;
ll y[maxk], inv[maxk], infact[maxk];
ll pow(ll x, ll b) {
	ll r = 1;
	while (b) {
		if (b & 1) r = r * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return r;
}
ll sL[maxk], sR[maxk];
inline ll sign(ll x) { return x & 1 ? -1 : +1; }
ll ell[maxk];
int main() {
	scanf("%lld %lld", &n, &k);
	for (int i = 1; i <= k + 2; ++i) {
		y[i] = pow(i, k);
		y[i] = (y[i] + y[i - 1]) % mod;
	}
	infact[0] = infact[1] = inv[0] = inv[1] = 1;
	for (int i = 2; i <= k + 2; ++i)
		inv[i] = (-inv[mod % i] * (mod / i) % mod + mod) % mod;
	for (int i = 1; i <= k + 2; ++i)
		infact[i] = infact[i - 1] * inv[i] % mod;
	sL[0] = 1;
	sR[k + 3] = 1;
	for (int i = 1; i <= k + 2; ++i)
		sL[i] = sL[i - 1] * (n - i) % mod;
	for (int i = k + 2; i >= 0; --i)
		sR[i] = sR[i + 1] * (n - i) % mod;
	for (int i = 1; i <= k + 2; ++i) {
		ell[i] = sL[i - 1] * sR[i + 1] % mod * infact[i - 1] % mod * infact[k + 2 - i] % mod * sign(k + 2 - i) % mod;
	}
	ll ans = 0;
	for (int i = 1; i <= k + 2; ++i) ans = (ans + y[i] * ell[i] % mod) % mod;
	ans = (ans + mod) % mod;
	printf("%lld", ans);
	return 0;
}