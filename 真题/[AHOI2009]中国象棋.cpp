#include <cstdio>
const int mod = 9999973;
int n = 0, m = 0;
long long f[107][107][107];
inline long long Choose(int s) { return s * (s - 1) / 2 % mod; }
int main() {
	scanf("%d%d", &n, &m);
	f[0][0][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
			for (int k = 0; k <= m - j; ++k) {
				f[i][j][k] = f[i - 1][j][k];
				if (j >= 1) f[i][j][k] += f[i - 1][j - 1][k] * (m - j - k + 1);
				if (k >= 1) f[i][j][k] += f[i - 1][j + 1][k - 1] * (j + 1);
				if (j >= 2) f[i][j][k] += f[i - 1][j - 2][k] * Choose(m - j - k + 2);
				if (k >= 2) f[i][j][k] += f[i - 1][j + 2][k - 2] * Choose(j + 2);
				if (k >= 1) f[i][j][k] += f[i - 1][j][k - 1] * j * (m - j - k + 1);
				f[i][j][k] %= mod;
			}
	long long ans = 0;
	for (int i = 0; i <= m; ++i)
		for (int k = 0; k <= m - i; ++k)
			ans = (ans + f[n][i][k]) % mod;
	printf("%lld", ans);
	return 0;
}