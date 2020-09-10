#include <cstdio>
#include <cctype>
long long a = 0, b = 0, m = 0;
long long phi(long long x) {
	long long p = 1;
	for (long long i = 2; i * i <= x; ++i)
		if (x % i == 0) {
			x /= i; p *= i - 1;
			while (x % i == 0) p *= i, x /= i;
		}
	if (x != 1) p *= x - 1;
	return p;
}
long long row(long long x, long long a) {
	long long ans = 1;
	while (a) {
		if (a & 1) ans = (ans * x) % m;
		x = (x * x) % m; a >>= 1;
	}
	return ans;
}
int main() {
	scanf("%lld%lld", &a, &m);
	a %= m;
	long long pm = phi(m);
	bool sign = false;
	int c = getchar();
	while (!isalnum(c)) c = getchar();
	while (isalnum(c)) {
		b = b * 10 + c - '0';
		if (b > pm) sign = true, b %= pm;
		c = getchar();
	}
	printf("%lld", row(a, b + (sign ? pm : 0)));
	return 0;
}