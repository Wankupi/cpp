#include <cstdio>
int const maxn = 5033, delta = 1000000;
typedef long long ll;
int n = 0, q = 0;
int a[maxn], t[2000303];
ll f[maxn][maxn];
int main() {
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int l = 1; l < n; ++l) {
		for (int r = l + 1; r <= n; ++r) {
			if (-1000000 <= a[l] + a[r] && a[l] + a[r] <= 1000000) 
				f[l][r] = t[-(a[l] + a[r]) + delta];
			++t[a[r] + delta];
		}
		for (int r = l + 1; r <= n; ++r) --t[a[r] + delta];
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			f[i][j] = f[i][j] + f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
	int l = 0, r = 0;
	for (int i = 1; i <= q; ++i) {
		scanf("%d %d", &l, &r);
		printf("%lld\n", f[r][r] + f[l - 1][l - 1] - f[l - 1][r] - f[r][l - 1]);
	}
	return 0;
}
