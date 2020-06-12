#include <cstdio>
typedef long long ll;
ll mod = 19940417;
inline ll min(ll a, ll b) { return a < b ? a : b; }
inline ll f(ll x) { return ((x * x % mod * x % mod * 6646806 % mod) + (x * x % mod * 9970209) + x * 3323403 % mod) % mod; }
int main() {
	ll n = 0, m = 0;
	scanf("%lld%lld", &n, &m);
	if (n > m)
		n ^= m ^= n ^= m;

	ll sumN = 0, sumM = 0;

	for (ll l = 1, r = 0, s = 0; l <= n; l = r + 1) {
		s = n / l;
		r = n / s;
		sumN = (sumN + (r + l) * (r - l + 1) % mod * 9970209 % mod * s % mod) % mod;
	}

	for (ll l = 1, r = 0, s = 0; l <= m; l = r + 1) {
		s = m / l;
		r = m / s;
		sumM = (sumM + (r + l) * (r - l + 1) % mod * 9970209 % mod * s % mod) % mod;
	}

	ll Zong = (n * n % mod - sumN + mod) % mod * (m * m % mod - sumM + mod) % mod;

	ll jn = sumN * m % mod, jm = 0, jmn = 0;

	for (ll l = 1, r = 0, s = 0; l <= n; l = r + 1) {
		s = m / l;
		r = min(m / s, n);
		jm = (jm + (r + l) * (r - l + 1) % mod * 9970209 % mod * s % mod) % mod;
	}
	jm = jm * n % mod;

	for (ll l = 1, r = 0, s1 = 0, s2 = 0; l <= n; l = r + 1) {
		s1 = n / l;
		s2 = m / l;
		r = min(n / s1, m / s2);
		jmn = (jmn + s1 * s2 % mod * ((f(r) - f(l - 1)) % mod + mod) % mod) % mod;
	}
	ll jian = ((((n * n % mod) * m % mod) - jn - jm + jmn) % mod + mod) % mod;
	ll ans = (Zong - jian + mod) % mod;
	if (ans < 0)
		ans += mod;
	printf("%lld", ans);
	return 0;
}