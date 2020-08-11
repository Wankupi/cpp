#include <cstdio>
int a[8], s = 0;
int main() {
	for (int i = 1; i <= 7; ++i) {
		scanf("%d", a + i);
		s += a[i];
	}
	double ans = 5040;
	for (int i = 1; i <= 6; ++i)
		ans *= double(a[i]) / double(s - i + 1);
	ans *= a[7];
	printf("%.3lf", ans);
	return 0;
}