#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
const double eps = 1e-8;
int n = 0, m = 0;
double x[20], y[20];
int line[1000], cnt = 0;
int f[300000];
inline int min(int a, int b) { return a < b ? a : b; }
inline double GetA(int i, int j) { return (y[i] - y[j] * x[i] / x[j]) / x[i] / (x[i] - x[j]); }
inline double GetB(int i, int j) { return (y[i] * x[j] * x[j] / x[i] / x[i] - y[j]) / (x[j] * x[j] / x[i] - x[j]); }
void seekLines() {
	memset(line, 0, sizeof line);
	cnt = 0;
	for (int i = 1; i <= n; ++i) {
		line[cnt++] = (1 << (i - 1));
		for (int j = 1, tag = 1 << (i - 1); j <= n; ++j) {
			if (((tag >> (j - 1)) & 1) == 1 || fabs(x[i] - x[j]) < eps) continue;
			double a = GetA(i, j);
			double b = GetB(i, j);
			if (a > -eps) continue;
			for (int k = 1; k <= n; ++k)
				if (fabs(a * x[k] * x[k] + b * x[k] - y[k]) < eps) {
					line[cnt] |= (1 << (k - 1));
					tag |= (1 << (k - 1));
				}
			++cnt;
		}
	}
}

int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			scanf("%lf %lf", x + i, y + i);
		seekLines();
		sort(line, line + cnt);
		cnt = unique(line, line + cnt) - line;
		memset(f, 0x3f, sizeof f);
		f[0] = 0;
		for (int i = 0; i < (1 << n); ++i) {
			for (int k = 0; k != cnt; ++k) {
				f[i | line[k]] = min(f[i | line[k]], f[i] + 1);
			}
		}
		printf("%d\n", f[(1 << n) - 1]);
	}
	return 0;
}