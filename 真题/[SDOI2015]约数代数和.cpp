#include <cstdio>
const int maxn = 50000;
bool h[maxn + 3];
int prime[maxn], c = 0, mu[maxn + 3];
void ouler() {
	h[1] = true;
	mu[1] = 1;
	for (int i = 2; i <= maxn; ++i) {
		if (!h[i]) {
			prime[c++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < c && prime[j] * i <= maxn; ++j) {
			h[prime[j] * i] = true;
			if (i % prime[j])
				mu[prime[j] * i] = -mu[i];
			else {
				mu[prime[j] * i] = 0;
				break;
			}
		}
	}
}
long long s[maxn + 3], g[maxn + 3];
void init() {
	ouler();
	for (int n = 1; n <= maxn; ++n) {
		for (int l = 1, r = 0; l <= n; l = r + 1) {
			r = n / (n / l);
			g[n] += (long long)(r - l + 1) * (n / l);
		}
		s[n] = s[n - 1] + mu[n];
	}
}
inline int min(int a, int b) { return a < b ? a : b; }
int main() {
	init();
	int T = 0;
	scanf("%d", &T);
	int n = 0, m = 0;
	for (int t = 1; t <= T; ++t) {
		scanf("%d%d", &n, &m);
		if (n > m) n ^= m ^= n ^= m;
		long long ans = 0;
		for (int l = 1, r = 0; l <= n; l = r + 1) {
			r = min(n / (n / l), m / (m / l));
			ans += (s[r] - s[l - 1]) * g[int(n / l)] * g[int(m / l)];
		}
		printf("%lld\n", ans);
	}
	return 0;
}