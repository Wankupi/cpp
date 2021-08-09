#include <cstdio>

int n = 0, m = 0, N = 0;
int a[11];

int cnt[1 << 10];

double f[1 << 10][53];

int main() {
	scanf("%d %d", &n, &m);
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		--x; --y;
		a[x] |= (1 << y);
		a[y] |= (1 << x);
	}
	N = (1 << n);
	for (int i = 1; i < N; ++i) cnt[i] = cnt[i & (i - 1)] + 1;
	for (int s = 3; s < N; s += 2) {
		for (int t = s & (s - 1); t; t = s & (t - 1)) {
			if ((t & 1) == 0) continue;
			int e = 0;
			for (int i = 0; i < n; ++i) if (t & (1 << i)) e += cnt[a[i] & (s ^ t)];
			for (int i = 0; i + e <= m; ++i)
				f[s][i] += 1.0 / (i + e + 1) - f[t][i + e];
		}
	}
	printf("%.6lf", f[N - 1][0]);
	return 0;
}
