#include <cstdio>
int n, m, a[51][51];
int f[52][52][1300], ans = -1;
inline int max(int a, int b) { return a < b ? b : a; }
int main() {
	scanf("%d%d", &n, &m);
	for (int i = n; i >= 1; i--)
		for (int j = 1; j <= i; j++)
			scanf("%d", &a[n + 1 - j][n + 1 - i]);
	for (int i = 1; i <= n; i++)
		for (int j = 2; j <= i; j++)
			a[i][j] += a[i][j - 1];
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= i; j++)
			for (int k = j * (j + 1) / 2; k <= i * (i - 1) / 2 + j; k++)
				for (int l = j - 1; l < i; l++)
					f[i][j][k] = max(f[i][j][k], f[i - 1][l][k - j] + a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			ans = max(ans, f[i][j][m]);
	printf("%d", ans);
	return 0;
}