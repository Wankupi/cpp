#include <cstdio>
int const mod = 1000000009;
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || '9' < c)
		c = getchar();
	while ('0' <= c && c <= '9')
		x = 10 * x + c - '0', c = getchar();
	return x;
}
inline int plus(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int n = 0, N = 0;
int a[21][1 << 20], b[21][1 << 20], cnt[1 << 20], c[21][1 << 20];

void FWT(int *f, int op) {
	for (int len = 1; len < N; len <<= 1) {
		for (int l = 0; l < N; l += (len << 1))
			for (int i = 0; i < len; ++i) {
				f[l + len + i] = plus(f[l + len + i], op * f[l + i]);
				if (f[l + len + i] < 0) f[l + len + i] += mod;
			}
	}
}

int main() {
	n = read();
	N = 1 << n;
	for (int i = 0; i < N; ++i) {
		cnt[i] = (i == 0 ? 0 : cnt[i - (i & -i)] + 1);
		a[cnt[i]][i] = read();
	}
	for (int i = 0; i < N; ++i)
		b[cnt[i]][i] = read();
	for (int i = 0; i <= n; ++i) {
		FWT(a[i], +1);
		FWT(b[i], +1);
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= i; ++j) {
			for (int s = 0; s < N; ++s)
				c[i][s] = plus(c[i][s], (long long)a[j][s] * b[i - j][s] % mod);
		}
	}
	for (int i = 0; i <= n; ++i)
		FWT(c[i], -1);
	for (int s = 0; s < N; ++s)
		printf("%d ", c[cnt[s]][s]);
	return 0;
}