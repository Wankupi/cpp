#include <cstdio>
int n = 0, m = 0, t = 0;
char a[1010], b[210];
int f[2][201][201], g[2][201][201];
const int mod = 1000000007;
int main() {
	scanf("%d%d%d", &n, &m, &t);
	scanf("%s%s", a + 1, b + 1);
	g[0][0][0] = 1;
	for (int i = 1, c = 1; i <= n; ++i, c ^= 1) {
		g[c][0][0] = 1;
		for (int j = 1; j <= m; ++j) {
			for (int k = 1; k <= t; ++k) {
				f[c][j][k] = (a[i] == b[j] ? ((f[c ^ 1][j - 1][k] + g[c ^ 1][j - 1][k - 1]) % mod
					+ f[c ^ 1][j - 1][k - 1]) % mod : 0);
				g[c][j][k] = (f[c ^ 1][j][k] + g[c ^ 1][j][k]) % mod;
			}
		}
	}
	printf("%d", (f[n & 1][m][t] + g[n & 1][m][t]) % mod);
	return 0;
}