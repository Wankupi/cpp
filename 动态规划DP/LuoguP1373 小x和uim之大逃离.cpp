#include <cstdio>
int n = 0, m = 0, mod = 0;
int a[801][801];
int f[801][801][16], //第一个人
	g[801][801][16]; //第二个人
int main() {
	scanf("%d%d%d", &n, &m, &mod);
	mod += 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			scanf("%d", &a[i][j]);
	long long ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			for (int v = 0; v < mod; ++v) {
				f[i][j][v] = (g[i][j - 1][((v - a[i][j]) % mod + mod) % mod] +
							g[i - 1][j][((v - a[i][j]) % mod + mod) % mod]) % 1000000007;
				g[i][j][v] = (f[i][j - 1][(v + a[i][j]) % mod] + f[i - 1][j][(v + a[i][j]) % mod]) % 1000000007;
			}
			ans = (ans + g[i][j][0]) % 1000000007;
			f[i][j][a[i][j]] += 1;
		}
	printf("%lld", ans);
	return 0;
}