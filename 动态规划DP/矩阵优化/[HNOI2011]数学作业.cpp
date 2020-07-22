#include <cstdio>
typedef long long ll;
ll n = 0, mod = 1;
struct Matrix {
	Matrix() : a{{0}} {}
	Matrix(int) : a{{0}} { a[0][0] = a[1][1] = a[2][2] = 1; }
	const ll *operator[](int x) const { return a[x]; }
	ll *operator[](int x) { return a[x]; }
	ll a[3][3];
};
Matrix operator*(const Matrix &A, const Matrix &B) {
	Matrix ret;
	for (int k = 0; k < 3; ++k)
		for (int i = 0; i < 3; ++i) {
			if (A[i][k] == 0) continue;
			for (int j = 0; j < 3; ++j)
				ret[i][j] = (ret[i][j] + A[i][k] * B[k][j] % mod) % mod;
		}
	return ret;
}
Matrix pow(Matrix x, ll a) {
	Matrix ret(1);
	while (a) {
		if (a & 1) ret = ret * x;
		x = x * x;
		a >>= 1;
	}
	return ret;
}
int main() {
	scanf("%lld%lld", &n, &mod);
	ll mi = 1;
	Matrix N, B;
	N[0][2] = 1;
	B[1][0] = B[1][1] = B[2][0] = B[2][1] = B[2][2] = 1;
	while (true) {
		B[0][0] = mi * 10 % mod;
		if (n >= mi * 10)
			N = N * pow(B, mi * 9);
		else {
			N = N * pow(B, n - mi + 1);
			break;
		}
		mi *= 10;
	}
	printf("%lld", N[0][0]);
	return 0;
}