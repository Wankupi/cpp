#include <cstdio>
int n = 0, N = 50000;
int prime[50000], mu[50001], c = 0;
bool h[50001];
int sum[50001];
void euler() {
	sum[1] = mu[1] = 1;
	h[1] = true;
	for (int i = 2; i <= N; ++i) {
		if (!h[i]) {
			prime[c++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < c && prime[j] * i <= N; ++j) {
			h[prime[j] * i] = true;
			if (i % prime[j])
				mu[prime[j] * i] = -mu[i];
			else {
				mu[prime[j] * i] = 0;
				break;
			}
		}
		sum[i] = sum[i - 1] + mu[i];
	}
}
inline int min(int a, int b) { return a < b ? a : b; }
int main() {
	scanf("%d", &n);
	euler();
	int a = 0, b = 0, d = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &a, &b, &d);
		a /= d;
		b /= d;
		if (a > b) a ^= b ^= a ^= b;
		int ans = 0;
		for (int l = 1, r = 0; l <= a; l = r + 1) {
			r = min(a / (a / l), b / (b / l));
			ans += (sum[r] - sum[l - 1]) * (a / l) * (b / l);
		}
		printf("%d\n", ans);
	}
	return 0;
}