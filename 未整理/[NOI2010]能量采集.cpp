#include <cstdio>

typedef long long ll;
ll n = 0, m = 0, f[100007];

int main() {
	scanf("%lld%lld", &n, &m);
	if (n > m) n ^= m ^= n ^= m;
	for (int i = n; i > 0; --i) {
		f[i] = (n / i) * (m / i);
		for (int j = i << 1; j <= n; j += i)
			f[i] -= f[j];
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i)
		ans += f[i] * (2 * i - 1);
	printf("%lld", ans);
	return 0;
}