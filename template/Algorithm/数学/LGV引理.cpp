#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
ll const mod = 998244353;
ll fac[2000003], ifac[2000003];
int n = 0, m = 0;
ll a[101][101];
inline ll C(ll n, ll m) { if (n < m) return 0; return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
inline ll pow(ll x, ll b) { ll r = 1; while (b) { if (b & 1) r = r * x % mod; x = x * x % mod; b >>= 1; } return r; }
ll gauss() {
	ll det = 1;
	for (int i = 1; i <= m; ++i) {
		if (a[i][i] == 0) {
			int j = i + 1;
			for (; j <= m && a[j][i] == 0; ++j)
				;
			if (j > m) return 0;
			std::swap(a[i], a[j]);
			det = -det;
		}
		ll inv = pow(a[i][i], mod - 2);
		for (int j = i + 1; j <= m; ++j) {
			if (a[j][i] == 0) continue;
			ll k = inv * a[j][i] % mod;
			for (int p = i; p <= m; ++p)
				a[j][p] = (a[j][p] - a[i][p] * k % mod) % mod;
		}
	}
	for (int i = 1; i <= m; ++i)
		det = det * a[i][i] % mod;
	det = (det + mod) % mod;
	return det;
}
int A[103], B[103];
int main() {
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= 2000000; ++i) {
		fac[i] = fac[i - 1] * i % mod;
		ifac[i] = (mod - mod / i) * ifac[mod % i] % mod;
	}
	for (int i = 2; i <= 2000000; ++i)
		ifac[i] = ifac[i] * ifac[i - 1] % mod;
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= m; ++i)
			scanf("%d %d", A + i, B + i);
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= m; ++j)
				a[i][j] = C(n - 1 + B[j] - A[i], n - 1);
		ll ans = gauss();
		printf("%lld\n", ans);
		memset(a, 0, sizeof a);
	}
	return 0;
}