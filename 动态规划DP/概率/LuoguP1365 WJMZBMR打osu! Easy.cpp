#include <cstdio>
const int maxn = 300010;
int n = 0;
char str[maxn];
double f[maxn], g[maxn];
int main() {
	scanf("%d\n%s", &n, str + 1);
	for (int i = 1; i <= n; ++i) {
		if (str[i] == 'o') {
			f[i] = f[i - 1] + 2.0 * g[i - 1] + 1.0;
			g[i] = g[i - 1] + 1.0;
		}
		else if (str[i] == 'x') {
			g[i] = 0.0;
			f[i] = f[i - 1];
		}
		else {
			f[i] = f[i - 1] + 1.0 * g[i - 1] + 0.5;
			g[i] = (g[i - 1] + 1.0) / 2.0;
		}
	}
	printf("%.4lf", f[n]);
	return 0;
}