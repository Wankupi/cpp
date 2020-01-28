#include <cstdio>
double f[100001], o1[100001], o2[100001];
int main() {
	int n = 0;
	scanf("%d", &n);
	double p = 0.0;
	for (int i = 1; i <= n; ++i) {
		scanf("%lf", &p);
		o1[i] = (o1[i - 1] + 1) * p;
		o2[i] = (o2[i - 1] + o1[i - 1] * 2.0 + 1.0) * p;
		f[i] = f[i - 1] + (3 * o2[i - 1] + 3 * o1[i - 1] + 1) * p;
	}
	printf("%.1lf", f[n]);
	return 0;
}