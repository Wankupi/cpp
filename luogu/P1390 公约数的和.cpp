#include <cstdio>
int n = 0;
long long f[2000030];
int main() {
	scanf("%d", &n);
	for (int i = n; i > 0; --i) {
		f[i] = (long long)(n / i) * (n / i);
		for (int j = 2 * i; j <= n; j += i)
			f[i] -= f[j];
	}
	long long ans = 0;
	for (int i = 1; i <= n; ++i)
		ans += i * f[i];
	ans = (ans - (long long)n * (n + 1) / 2) / 2;
	printf("%lld", ans);
	return 0;
}