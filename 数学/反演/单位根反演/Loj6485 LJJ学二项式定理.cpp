#include <cstdio>
typedef long long ll;
ll const mod = 998244353;
inline ll pow(ll x, ll b) { b %= mod - 1; ll r = 1; while (b) { if (b & 1) r = r * x % mod; x = x * x % mod; b >>= 1; } return r; }
ll g[4], inv4 = pow(4, mod - 2);
int main() {
	g[0] = 1; g[1] = pow(3, (mod - 1) / 4); g[2] = g[1] * g[1] % mod; g[3] = g[2] * g[1] % mod;
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		ll n = 0, s = 0, a[4];
		scanf("%lld %lld", &n, &s); for (int i = 0; i < 4; ++i) scanf("%lld", a + i);
		ll ans = 0;
		for (int i = 0; i < 4; ++i) {
			ll sum = 0;
			for (int k = 0; k < 4; ++k) {
				sum = (sum + g[((4 - i) * k) & 3] * pow(s * g[k] % mod + 1, n) % mod) % mod;
			}
			ans = (ans + sum * a[i] % mod) % mod;
		}
		ans = ans * inv4 % mod;
		printf("%lld\n", ans);
	}
	return 0;
}