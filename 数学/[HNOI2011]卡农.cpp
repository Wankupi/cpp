#include <cstdio>
typedef long long ll;
const ll mod = 100000007;
int n = 0, m = 0;
ll pow(ll x, int b) {
	ll ret = 1;
	while (b) {
		if (b & 1) ret = ret * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return ret;
}
ll mi = 0, fact = 1, A[1000003], f[1000003];

int main() {
	scanf("%d%d", &n, &m);
	mi = pow(2, n);
	A[0] = 1;
	for (int i = 1; i <= m; ++i) {
		A[i] = A[i - 1] * (mi - 1 - i + 1) % mod;
		fact = fact * i % mod;
	}
	f[0] = 1;
	for (int i = 2; i <= m; ++i) {
		f[i] = A[i - 1] - f[i - 1] -
			   f[i - 2] * (i - 1) % mod * (mi - i + 1) % mod;
		f[i] = (f[i] % mod + mod) % mod;
	}
	printf("%lld", f[m] * pow(fact, mod - 2) % mod);
	return 0;
}