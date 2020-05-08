#include <cstdio>

int n = 0, m = 0, k = 0;
int a[1000003], f[1000003];
int q[1000001], l = 1, r = 0;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	f[1] = 0;
	scanf("%d", &m);
	for (int t = 1; t <= m; ++t) {
		scanf("%d", &k);
		q[l = r = 1] = 1;
		for (int i = 2; i <= n; ++i) {
			while (l <= r && i - q[l] > k)
				++l;
			f[i] = f[q[l]] + (a[i] >= a[q[l]]);
			while (l <= r && (f[i] < f[q[r]] || (f[i] == f[q[r]] && a[i] >= a[q[r]])))
				--r;
			q[++r] = i;
		}
		printf("%d\n", f[n]);
	}
	return 0;
}