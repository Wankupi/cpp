#include <cstdio>
typedef long long ll;
inline ll binom3(ll x) {
	return x * (x - 1) / 2 * (x - 2) / 3;
}
inline ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	ll n = 0, m = 0;
	scanf("%lld%lld", &n, &m);
	ll ans = binom3((n + 1) * (m + 1)) - (m + 1) * binom3(n + 1) - (n + 1) * binom3(m + 1);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			ans -= 2 * (gcd(i, j) - 1) * (n - i + 1) * (m - j + 1);
	printf("%lld", ans);
	return 0;
}