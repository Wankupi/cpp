#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
int const maxn = 503, maxm = 250003;
double const eps = 1e-10;
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' && c < '9')
		c = getchar();
	while ('0' <= c && c <= '9')
		x = 10 * x + c - '0', c = getchar();
	return x;
}
int n = 0, m = 0;
int A[maxm], B[maxm];
int d[maxn];
double a[maxn][maxn], b[maxn];
void Gauss(int N) {
	for (int i = 1; i <= N; ++i) {
		int p = i;
		for (; p <= N && fabs(a[p][i]) < eps; ++p)
			;
		if (p != i) {
			swap(a[p], a[i]);
			swap(b[p], b[i]);
		}
		for (int j = 1; j <= N; ++j) {
			if (j == i || fabs(a[j][i]) < eps) continue;
			double k = a[j][i] / a[i][i];
			for (int p = i; p <= N; ++p)
				a[j][p] -= a[i][p] * k;
			b[j] -= b[i] * k;
		}
	}
	for (int i = 1; i <= N; ++i) {
		b[i] /= a[i][i];
		a[i][i] = 1.0;
	}
}
double f[maxm];
int main() {
	n = read();
	m = read();
	for (int i = 1; i <= m; ++i) {
		A[i] = read();
		B[i] = read();
		// insert(A[i], B[i]);
		// insert(B[i], A[i]);
		++d[A[i]];
		++d[B[i]];
	}
	for (int i = 1; i < n; ++i)
		a[i][i] = 1.0;
	for (int i = 1; i <= m; ++i) {
		if (B[i] != n) a[A[i]][B[i]] -= 1.0 / d[B[i]];
		if (A[i] != n) a[B[i]][A[i]] -= 1.0 / d[A[i]];
	}
	b[1] = 1.0;
	Gauss(n - 1);
	for (int i = 1; i <= m; ++i) {
		if (A[i] != n) f[i] += b[A[i]] / d[A[i]];
		if (B[i] != n) f[i] += b[B[i]] / d[B[i]];
	}
	sort(f + 1, f + m + 1);
	double ans = 0;
	for (int i = 1; i <= m; ++i)
		ans += (m - i + 1) * f[i];
	printf("%.3lf", ans);
	return 0;
}