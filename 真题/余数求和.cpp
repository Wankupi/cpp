#include <cstdio>
long long n = 0, k = 0;
long long l = 0, r = 0, t = 0;
inline long long min(long long a, long long b) { return a < b ? a : b; }
int main() {
	scanf("%lld%lld", &n, &k);
	long long ans = n * k;
	for (l = 1; l <= n; l = r + 1) {
		t = k / l;
		if (t != 0) r = min(k / t, n);
		else r = n;
		ans -= (long long)t * (r + l) * (r - l + 1) / 2;
	}
	printf("%lld", ans);
	return 0;
}