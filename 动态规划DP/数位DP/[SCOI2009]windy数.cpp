#include <cstdio>
typedef long long ll;
ll a = 0, b = 0;
ll f[15][15];
int devide(int *ar, ll x) {
	int *t = ar;
	while (x) {
		*t++ = x % 10;
		x /= 10;
	}
	return t - ar;
}
inline int abs(int x) { return x < 0 ? -x : x; }
int n[15], len = 0;
ll calc(ll x) {
	if (x == 0) return 0;
	len = 0;
	while (x) {
		n[++len] = x % 10;
		x /= 10;
	}
	ll sum = 0;
	// 有前导 0
	for (int i = len - 1; i; --i)
		for (int v = 1; v <= 9; ++v)
			sum += f[i][v];
	// 无前导 0
	for (int v = 1; v < n[len]; ++v) sum += f[len][v]; //最高位不能为0
	for (int i = len - 1; i; --i) {
		//if(abs(n[i+1] - n[i]) < 2)
		for (int v = 0; v < n[i]; ++v)
			if (abs(v - n[i + 1]) >= 2)
				sum += f[i][v];
		if (abs(n[i + 1] - n[i]) < 2) break;
	}
	return sum;
}
int main() {
	scanf("%lld%lld", &a, &b);
	for (int j = 0; j <= 9; ++j)
		f[1][j] = 1;
	for (int i = 2; i <= 10; ++i)
		for (int j = 0; j <= 9; ++j)
			for (int k = 0; k <= 9; ++k)
				if (abs(j - k) >= 2) f[i][j] += f[i - 1][k];
	printf("%lld", calc(b + 1) - calc(a));
	return 0;
}