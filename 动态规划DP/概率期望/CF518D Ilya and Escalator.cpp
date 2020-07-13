#include <cstdio>
int n = 0, t = 0;
double p = 0;
double f[2003];
// f [i] 表述处于某种状态时的概率 并不表示具体人数
int main() {
	scanf("%d%lf%d", &n, &p, &t);
	f[0] = 1.0;
	for (int i = 1; i <= t; ++i) {
		f[n] = f[n] + f[n - 1] * p;
		for (int x = n - 1; x >= 1; --x)
			f[x] = f[x] * (1 - p) + f[x - 1] * p;
		f[0] *= (1 - p);
	}
	double qw = 0.0;
	for (int x = 1; x <= n; ++x)
		qw += x * f[x];
	printf("%.6lf", qw);
	return 0;
}