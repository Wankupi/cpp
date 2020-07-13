#include <cstdio>
int n = 0, N = 0;
double p[130][130];
double f[10][130];
int main() {
	while (true) {
		scanf("%d", &n);
		if (n == -1) break;
		N = 1 << n;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				scanf("%lf", &p[i][j]);
		for (int i = 0; i < N; ++i)
			f[0][i] = 1.0;
		for (int j = 1; j <= n; ++j) {
			int len = (1 << (j - 1));
			for (int l = 0; l < N; l += len * 2) {
				for (int x = 0; x < len; ++x) {
					f[j][l + x] = f[j][l + x + len] = 0.0;
					for (int y = 0; y < len; ++y) {
						f[j][l + x] += f[j - 1][l + x] * f[j - 1][l + len + y] * p[l + x][l + len + y];
						f[j][l + x + len] += f[j - 1][l + x + len] * f[j - 1][l + y] * p[l + len + x][l + y];
					}
				}
			}
		}
		int p = 0;
		double Max = 0;
		for (int i = 0; i < N; ++i) {
			if (f[n][i] > Max) {
				Max = f[n][i];
				p = i;
			}
		}
		printf("%d\n", p + 1);
	}
	return 0;
}