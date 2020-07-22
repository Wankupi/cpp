#include <cstdio>
const int mod = 2009;
int n = 0, t = 0;
int m = 0;
struct Matrix {
	Matrix() : a{ {0} } {}
	Matrix(int) : a{ {0} } {
		for (int i = 1; i <= m; ++i)
			a[i][i] = 1;
	}
	const int *operator[](int x) const { return a[x]; }
	int *operator[](int x) { return a[x]; }
	int a[92][92];
};
Matrix operator*(const Matrix &A, const Matrix &B) {
	Matrix ret;
	for (int k = 0; k < m; ++k)
		for (int i = 0; i < m; ++i) {
			if (A[i][k] == 0) continue;
			for (int j = 0; j < m; ++j)
				ret[i][j] = (ret[i][j] + A[i][k] * B[k][j] % mod) % mod;
		}
	return ret;
}
Matrix Begin, Base;
Matrix ret(1);
Matrix pow(int a) {
	ret = Begin;
	while (a) {
		if (a & 1) ret = ret * Base;
		Base = Base * Base;
		a >>= 1;
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &t);
	m = 9 * n;
	int c = 0;
	for (int i = 0; i < n; ++i) {
		for (int k = 1; k <= 8; ++k)
			Base[9 * i + k][9 * i + k - 1] = 1;
		for (int j = 0; j < n; ++j) {
			do c = getchar(); while (c < '0' || c > '9');
			if (c == '0') continue;
			Base[i * 9][j * 9 + c - '0' - 1] = 1;
		}
	}
	Begin[0][0] = 1;
	pow(t);
	printf("%d", ret[0][(n - 1) * 9]);
	return 0;
}