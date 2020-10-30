#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
double const eps = 1e-8;
int n = 0, m = 0, K = 0, N = 0;
int black[501], id[503], cId = 0;
struct Matrix {
	Matrix() { memset(a, 0, sizeof a); }
	Matrix(int) { memset(a, 0, sizeof a); for (int i = 0; i < N; ++i) a[i][i] = 1; }
	double *operator[](int x) { return a[x]; }
	double const *operator[](int x) const { return a[x]; }
	double a[103][103];
};
Matrix operator*(const Matrix &A, const Matrix &B) {
	Matrix ret;
	for (int k = 1; k <= N; ++k)
		for (int i = 0; i <= N; ++i)
				for (int j = 1; j <= N; ++j)
					ret[i][j] += A[i][k] * B[k][j];
	return ret;
}
int G[503][503], d[503];
double f[503][1003];
void Gauss() {
	for (int i = 1; i <= n; ++i) {
		int j = -1;
		for (int hang = i; hang <= n; ++hang) {
			if (fabs(f[hang][i]) > eps) {
				j = hang; break;
			}
		}
		for (int hang = 1; hang <= n; ++hang) {
			if (hang == j)	continue;
			double k = f[hang][i] / f[j][i];
			for (int p = 1; p <= N; ++p) f[hang][p] -= k * f[j][p];
		}
		swap(f[i], f[j]);
		for (int p = i + 1; p <= N; ++p) f[i][p] /= f[i][i];
		f[i][i] = 1;
	}
}
Matrix Ans, B;

void solve() {
	f[1][n + 1] = 1;
	for (int i = 1; i <= n; ++i) {
		f[i][i] = 1;
		for (int j = 1; j <= n; ++j) {
			if (i == j)
				continue;
			if (black[j])
				f[i][n + j] = double(G[j][i]) / double(d[j]);
			else
				f[i][j] = -double(G[j][i]) / double(d[j]);
		}
	}
	N = 2 * n;
	Gauss();
	N = cId;
	for (int i = 1; i <= cId; ++i)
		Ans[1][i] = f[id[i]][n + 1];
	for (int i = 1; i <= cId; ++i) for (int j = 1; j <= cId; ++j)
			B[i][j] = f[id[j]][n + id[i]];
	K -= 2;
	while (K) {
		if (K & 1) Ans = Ans * B;
		B = B * B; K >>= 1;
	}
	printf("%.10lf", Ans[1][cId]);
}
int main() {
	scanf("%d %d %d", &n, &m, &K);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", black + i);
		if (black[i]) id[++cId] = i;
	}
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		++G[x][y]; ++G[y][x]; ++d[x]; ++d[y];
	}
	solve();
	return 0;
}