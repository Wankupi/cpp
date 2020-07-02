#include <cstdio>
typedef long long ll;
const ll mod = 20101009;
bool h[10000001];
int prime[10000000], c = 0;
int mu[10000001];
int sum[10000001];
int s[10000001];
void init(int n) {
	mu[1] = h[1] = true;
	for (int i = 2; i <= n; ++i) {
		if (!h[i]) {
			prime[c++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < c && prime[j] * i <= n; ++j) {
			h[prime[j] * i] = true;
			if (i % prime[j])
				mu[prime[j] * i] = -mu[i];
			else {
				mu[prime[j] * i] = 0;
				break;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (mu[i])
			for (int j = 1; i * j <= n; ++j)
				sum[i * j] = (sum[i * j] + (long long)mu[i] * i % mod) % mod;
		if (sum[i] < 0) sum[i] += mod;
		sum[i] = (long long) sum[i] * i % mod;
		sum[i] = (sum[i] + sum[i - 1]) % mod;
	}
}
inline int min(int a, int b) { return a < b ? a : b; }
int main() {
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	if (n > m) n ^= m ^= n ^= m;
	init(n);
	for (int i = 1; i <= m; ++i)
		s[i] = (s[i - 1] + i) % mod;
	ll ans = 0;
	for (int l = 1, r = 0; l <= n; l = r + 1) {
		r = min(n / (n / l), m / (m / l));
		ans = (ans + (long long)(sum[r] - sum[l - 1] + mod) % mod * s[n / l] % mod * s[m / l] % mod) % mod;
	}
	printf("%lld", ans);
	return 0;
}