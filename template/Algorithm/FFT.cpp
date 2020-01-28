#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
int read() {
	int x = 0, c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x;
}
const int maxn = 4000010;
const double pi = 3.1415926535;
struct Complex {
	double real, ima;
	Complex() : real(0.0), ima(0.0) {}
	Complex(double r, double im) : real(r), ima(im) {}
	friend Complex operator+(const Complex &lhs, const Complex &rhs) { return Complex(lhs.real + rhs.real, lhs.ima + rhs.ima); }
	friend Complex operator-(const Complex &lhs, const Complex &rhs) { return Complex(lhs.real - rhs.real, lhs.ima - rhs.ima); }
	friend Complex operator*(const Complex &lhs, const Complex &rhs) { return Complex(lhs.real * rhs.real - lhs.ima * rhs.ima, lhs.real * rhs.ima + lhs.ima * rhs.real); }
};
inline int max(int a, int b) { return a < b ? b : a; }
int n = 0, m = 0;
Complex f[maxn], W[maxn];
int limit = 1, bit = 0;
int rev[maxn]; // 表示反转后的位置
void FFT(Complex *a, int op) {
	for (int i = 0; i != limit; ++i)
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int len = 1; len < limit; len <<= 1) {
		for (int L = 0; L < limit; L += (len << 1)) {
			for (int i = 0; i < len; ++i) {
				Complex omega = W[i * (limit / (2 * len))];
				if (op == -1) omega.ima = -omega.ima;
				Complex x = a[L + i], y = a[L + i + len];
				a[L + i] = x + omega * y;
				a[L + i + len] = x - omega * y;
			}
		}
	}
}
int main() {
	n = read();	m = read();
	for (int i = 0; i <= n; ++i)
		f[i].real = read();
	for (int i = 0; i <= m; ++i)
		f[i].ima = read();
	while (limit <= n + m) {
		limit <<= 1;
		++bit;
	}
	for (int i = 0; i != limit; ++i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
	for (int i = 0; i != limit; ++i)
		W[i] = Complex(cos(2 * pi * i / limit), sin(2 * pi * i / limit));
	FFT(f, 1);
	for (int i = 0; i != limit; ++i)
		f[i] = f[i] * f[i];
	FFT(f, -1);
	for (int i = 0; i <= n + m; ++i)
		printf("%d ", (int)(f[i].ima / (2.0 * limit) + 0.5));
	return 0;
}