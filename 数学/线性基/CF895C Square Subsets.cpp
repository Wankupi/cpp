#include <cstdio>

int const maxn = 100003, mod = 1000000007;
int const p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
int n = 0;

int base[19], cnt = 0;
inline void add(int x) {
	for (int j = 18; j >= 0 && x; --j)
		if ((x >> j) & 1) {
			if (base[j])
				x ^= base[j];
			else {
				base[j] = x;
				++cnt;
				break;
			}
		}
}

inline int pow(int b) {
	int x = 2, r = 1;
	while (b) {
		if (b & 1) r = (long long)(r) * x % mod;
		x = (long long)(x) * x % mod;
		b >>= 1;
	}
	return r;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int x = 0, y = 0;
		scanf("%d", &x);
		for (int j = 0; j < 19; ++j)
			if (x % p[j] == 0) {
				while (x % p[j] == 0) {
					x /= p[j];
					y ^= (1 << j);
				}
			}
		add(y);
	}
	int ans = pow(n - cnt) - 1;
	printf("%d", ans);
	return 0;
}