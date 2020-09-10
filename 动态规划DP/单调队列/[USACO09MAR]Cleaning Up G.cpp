#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
int const N = 40003, M = 210;
int n = 0, m = 0;
int a[N];
int t[M][N], cnt[M], l[M];
int f[N];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	int c = ceil(sqrt(n));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= c; ++j) {
			if (++t[j][a[i]] == 1) {
				if (++cnt[j] > j) {
					while (--t[j][a[++l[j]]] != 0)
						;
					--cnt[j];
				}
			}
		}
		for (int j = 1; j <= c; ++j)
			f[i] = std::min(f[i], f[l[j]] + j * j);
	}
	printf("%d", f[n]);
	return 0;
}