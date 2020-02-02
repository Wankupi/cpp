#include <cstdio>
int main() {
	int n = 0;
	double score = 0.0, o1 = 0.0;
	double p = 0;
	scanf("%d",&n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf", &p);
		score += (2 * o1 + 1) * p;
		o1 = (o1 + 1) * p;
	}
	printf("%9lf", score);
	return 0;
}