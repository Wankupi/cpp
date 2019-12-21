#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
int n = 0;
double k[101][101], b[101];
bool Gauss() {
	for (int i = 1; i <= n; ++i) {
		int ex = i;
		for (int j = i + 1; j <= n; ++j)
			if (fabs(k[j][i]) > fabs(k[ex][i]))
				ex = j;
		if (fabs(k[ex][i]) < 1e-8) return false;
		if (ex != i) {
			for (int p = 1; p <= n; ++p)
				swap(k[i][p], k[ex][p]);
			swap(b[i], b[ex]);
		}
		for (int j = 1; j <= n; ++j) {
			if (j == i || fabs(k[j][i]) < 1e-8)
				continue;
			double c = k[j][i] / k[i][i];
			for (int p = 1; p <= n; ++p)
				k[j][p] -= k[i][p] * c;
			b[j] -= b[i] * c;
		}
	}
	return true;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			scanf("%lf", &k[i][j]);
		scanf("%lf", &b[i]);
	}
	if(Gauss())
		for (int i = 1; i <= n;++i)
			printf("%.2lf\n", b[i] / k[i][i]);
	else
		printf("No Solution");
	return 0;
}