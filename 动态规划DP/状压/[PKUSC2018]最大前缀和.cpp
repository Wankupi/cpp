#include <cstdio>
typedef long long ll;
const ll mod = 998244353;
int n = 0;
int a[21];
ll f[1048576], g[1048576];
ll sum[1048576];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	f[0] = 1;
	g[0] = 1;
	for (int st = 1; st < (1 << n); ++st) {
		for (int i = 0; i < n; ++i) {
			if (((st >> i) & 1) == 0) continue;
			sum[st] += a[i];
			int fr = st ^ (1 << i);
			if (sum[fr] >= 0) f[st] = (f[st] + f[fr]) % mod;
			g[st] = (g[st] + g[fr]) % mod;
		}
		if (sum[st] >= 0) g[st] = 0;
	}
	ll ans = 0;
	for (int st = 1; st < (1 << n); ++st)
		ans = (ans + sum[st] % mod * f[st] % mod * g[((1 << n) - 1) ^ st] % mod) % mod;
	if(ans < 0) ans += mod;
	printf("%lld", ans);
	return 0;
}