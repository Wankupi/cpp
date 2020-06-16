#include <cstdio>
#include <cstring>
int n = 0, c = 0;
int p[60], a[60], sum[60];
int f[60][60], g[60][60];
inline int min(int a, int b) { return a < b ? a : b; }
int main() {
	scanf("%d%d", &n, &c);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", p + i, a + i);
		sum[i] = sum[i - 1] + a[i];
	}
	memset(f, 0x3f, sizeof f);
	memset(g, 0x3f, sizeof g);
	f[c][c] = g[c][c] = 0;
	for (int len = 2; len <= n; ++len) {
		for (int l = 1; l <= n - len + 1; ++l) {
			int r = l + len - 1;
			f[l][r] = min(
				g[l + 1][r] + (p[r] - p[l]) * (sum[n] - sum[r] + sum[l]),
				f[l + 1][r] + (p[l + 1] - p[l]) * (sum[n] - sum[r] + sum[l]));
			g[l][r] = min(
				g[l][r - 1] + (p[r] - p[r - 1]) * (sum[n] - sum[r - 1] + sum[l - 1]),
				f[l][r - 1] + (p[r] - p[l]) * (sum[n] - sum[r - 1] + sum[l - 1]));
		}
	}
	printf("%d", min(f[1][n], g[1][n]));
	return 0;
}