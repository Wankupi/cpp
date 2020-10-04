#include <cmath>
#include <cstdio>
int const maxn = 103;
int n = 0;
int a[maxn], x[maxn];
int s[maxn], t[maxn], ds[maxn], dt[maxn];
bool zero[maxn];
int calc(int v) { return (1 + sqrt(8 * v + 1)) / 2; }
int main() {
	scanf("%d", &n);
	scanf("%d %d", t, s);
	printf("+ 2\n");
	printf("+ 1\n");
	printf("+ 3\n");
	printf("+ 1\n");
	fflush(stdout);
	for (int i = 1; i <= 4; ++i) {
		scanf("%d %d", t + i, s + i);
		dt[i] = t[i] - t[i - 1];
		ds[i] = s[i] - s[i - 1];
	}
	a[1] = (dt[4] == 0 ? 0 : (dt[2] == 0 ? 1 : calc(dt[2])));
	a[2] = ds[4] - ds[2] - 1;
	a[3] = ds[2] / (a[2] + 1);
	x[1] = a[1] + 2;
	x[2] = a[2] + 1;
	x[3] = a[3] + 1;
	zero[4] = (ds[3] - (a[1] + 1) * (a[2] + 1) == 0);
	for (int i = 4; i < n; ++i) {
		printf("+ %d\n", i);
		fflush(stdout);
		scanf("%d %d", t + i + 1, s + i + 1);
		dt[i + 1] = t[i + 1] - t[i];
		ds[i + 1] = s[i + 1] - s[i];
		if (zero[i]) {
			a[i] = 0;
			x[i] = 1;
		} else {
			a[i] = (dt[i + 1] == 0 ? 1 : calc(dt[i + 1]));
			x[i] = a[i] + 1;
		}
		zero[i + 1] = (ds[i + 1] - x[i - 1] * x[i - 2] == 0);
	}
	if (n == 4) {
		a[4] = (ds[3] - (a[1] + 1) * (a[2] + 1)) / (a[2] + 1);
	} else
		a[n] = (ds[n] - x[n - 3] * x[n - 2]) / x[n - 2];
	printf("!");
	for (int i = 1; i <= n; ++i)
		printf(" %d", a[i]);
	return 0;
}