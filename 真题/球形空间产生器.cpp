#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
int n = 0;
double a[15][15];
double k[15][15], b[15];
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
	for (int i = 1; i <= n + 1; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%lf", &a[i][j]);
	for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
			k[i][j] = 2 * (a[i][j] - a[i + 1][j]);
			b[i] += a[i][j] * a[i][j] - a[i + 1][j] * a[i + 1][j];
		}
	Gauss();
	for (int i = 1; i < n; ++i)
		printf("%.3lf ", b[i] / k[i][i]);
	printf("%0.3lf", b[n] / k[n][n]);
	return 0;
}