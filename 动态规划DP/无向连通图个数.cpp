#include <cstdio>
const long long mod = 1000000009;
int n = 0;
long long f[1005], fact[1005], mi[1005], inv[1005];
long long row(long long x, long long a) {
	long long ret = 1;
	while (a) {
		if (a & 1) ret = ret * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return ret;
}
inline long long binom(long long a, long long b) { return fact[a] * inv[b] % mod * inv[a - b] % mod; }
int main() {
	scanf("%d", &n);
	f[1] = f[2] = 1;
	if (n > 2) {
		fact[0] = mi[0] = 1;
		for (int i = 1; i <= n; ++i) {
			fact[i] = fact[i - 1] * i % mod;
			mi[i] = mi[i - 1] * 2 % mod;
		}
		inv[n] = row(fact[n], mod - 2);
		for (int i = n - 1; i >= 0; --i)
			inv[i] = inv[i + 1] * (i + 1) % mod;
		for (int i = 3; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {
				f[i] = f[i] + f[j] * f[i - j] % mod * binom(i - 2, j - 1) % mod * ((mi[j] - 1 + mod) % mod) % mod;
				f[i] %= mod;
			}
		}
	}
	printf("%lld", f[n]);
	return 0;
}