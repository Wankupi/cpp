#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long ll;
const int prime[8] = {2, 3, 5, 7, 11, 13, 17, 19};
int n = 0;
ll mod = 0;
struct Sushi {
	int mp, s;
};
inline bool operator<(const Sushi &lhs, const Sushi &rhs) { return lhs.mp < rhs.mp; }
Sushi make_Sushi(int x) {
	Sushi su;
	su.s = 0;
	su.mp = 0;
	for (int i = 0; i < 8; ++i)
		if (x % prime[i] == 0) {
			su.s |= (1 << i);
			while (x % prime[i] == 0) x /= prime[i];
		}
	if (x != 1) su.mp = x;
	return su;
}
inline ll muti(ll a, ll b) {
	ll r = 0;
	while (b) {
		if (b & 1) r = (r + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return r;
}
Sushi a[501];
ll dp[256][256], f[256][256], g[256][256];
int main() {
	scanf("%d%lld", &n, &mod);
	for (int i = 1; i < n; ++i)
		a[i] = make_Sushi(i + 1);
	std::sort(a + 1, a + n);
	dp[0][0] = 1;
	for (int i = 1; i < n; ++i) {
		if (a[i].mp != a[i - 1].mp || a[i].mp == 0) {
			memcpy(f, dp, sizeof dp);
			memcpy(g, dp, sizeof dp);
		}
		for (int j = 255; ~j; --j)
			for (int k = 255; ~k; --k) {
				if (j & k) continue;
				if ((k & a[i].s) == 0) f[j | a[i].s][k] = (f[j | a[i].s][k] + f[j][k]) % mod;
				if ((j & a[i].s) == 0) g[j][k | a[i].s] = (g[j][k | a[i].s] + g[j][k]) % mod;
			}
		if (i == n - 1 || a[i].mp != a[i + 1].mp || a[i].mp == 0) {
			for (int j = 0; j < 256; ++j)
				for (int k = 0; k < 256; ++k) {
					if (j & k) continue;
					dp[j][k] = (f[j][k] + g[j][k] + mod - dp[j][k]) % mod;
				}
		}
	}
	ll ans = 0;
	for (int j = 0; j < 256; ++j)
		for (int k = 0; k < 256; ++k) {
			if (j & k) continue;
			ans = (ans + dp[j][k]) % mod;
		}
	printf("%lld", ans);
	return 0;
}