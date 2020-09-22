#include <algorithm>
#include <cstdio>
typedef long long ll;
int const maxn = 1000003;
int const mod = 1000000007;

ll pow(ll x, ll b) {
	b %= mod - 1;
	ll r = 1;
	while (b) {
		if (b & 1) r = (ll)r * x % mod;
		x = (ll)x * x % mod;
		b >>= 1;
	}
	return r;
}
int prime[maxn], cPrime = 0;
int mu[maxn], h[maxn];
void euler() {
	mu[1] = h[1] = 1;
	for (int i = 2; i <= 1000000; ++i) {
		if (!h[i]) {
			prime[cPrime++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < cPrime && prime[j] * i <= 1000000; ++j) {
			h[prime[j] * i] = true;
			if (i % prime[j])
				mu[prime[j] * i] = -mu[i];
			else
				break;
		}
	}
}
int f[maxn], g[maxn], ig[maxn];
void init() {
	euler();
	for (int i = 0; i <= 1000000; ++i)
		g[i] = ig[i] = 1;
	f[0] = 0;
	f[1] = 1;
	for (int i = 2; i <= 1000000; ++i) {
		f[i] = ((ll)f[i - 1] + f[i - 2]) % mod;
		int inv = pow((ll)f[i], mod - 2ll);
		for (int k = i; k <= 1000000; k += i) {
			g[k] = (ll)g[k] * (mu[k / i] == 1 ? f[i] : (mu[k / i] == 0 ? 1 : inv)) % mod;
			ig[k] = (ll)ig[k] * (mu[k / i] == 1 ? inv : (mu[k / i] == 0 ? 1 : f[i])) % mod;
		}
	}
	for (int i = 2; i <= 1000000; ++i) {
		g[i] = (ll)g[i] * g[i - 1] % mod;
		ig[i] = (ll)ig[i] * ig[i - 1] % mod;
	}
}
int main() {
	init();
	int T = 0, n = 0, m = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		if (n > m) std::swap(n, m);
		int ans = 1;
		for (int l = 1, r = 0; l <= n; l = r + 1) {
			r = std::min(n / (n / l), m / (m / l));
			ans = (ll)ans * pow((ll)g[r] * ig[l - 1] % mod, (ll)(n / l) * (m / l)) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}