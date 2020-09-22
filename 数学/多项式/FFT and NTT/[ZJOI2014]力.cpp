#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const double pi = 3.14159265358979323846;
int limit = 1, bit = 0, invlimit;
int rev[1 << 18];

struct Complex {
	Complex(double Reality = 0.0, double Imagine = 0.0) : real(Reality), imag(Imagine) {}
	double real, imag;
};
inline Complex operator+(Complex const &lhs, Complex const &rhs) { return Complex(lhs.real + rhs.real, lhs.imag + rhs.imag); }
inline Complex operator-(Complex const &lhs, Complex const &rhs) { return Complex(lhs.real - rhs.real, lhs.imag - rhs.imag); }
inline Complex operator*(Complex const &lhs, Complex const &rhs) { return Complex(lhs.real * rhs.real - lhs.imag * rhs.imag, lhs.real * rhs.imag + lhs.imag * rhs.real); }
inline Complex operator/(Complex const &lhs, Complex const &rhs) { return lhs * Complex(rhs.real, -rhs.imag); }

class Polynomial {
public:
	Polynomial() {}
	Polynomial(int) { f[0] = 1; }
	Complex& operator[](int x) { return f[x]; }
	void DFT(int op) {
		for (int i = 0; i < limit; ++i)
			if (rev[i] > i) std::swap(f[rev[i]], f[i]);
		for (int len = 1; len < limit; len <<= 1) {
			Complex W1(cos(pi / len), (op == 1 ? 1 : -1) * sin(pi / len));
			for (int l = 0; l < limit; l += 2 * len) {
				Complex o(1.0, 0.0);
				for (int i = 0; i < len; ++i) {
					Complex x = f[l + i], y = f[l + len + i];
					f[l + i] = x + o * y;
					f[l + len + i] = x - o * y;
					o = o * W1;
				}
			}
		}
	}
private:
	Complex f[1 << 18];
};
int n = 0;
Polynomial q, qt, g;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf", &q[i].real);
		qt[n - i] = q[i];
		g[i].real = (1.0 / i) / i;
	}
	g[0].real = 0.0;
	while (limit < n + n) limit <<= 1, ++bit;
	for (int i = 1; i < limit; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
	q.DFT(+1);
	qt.DFT(+1);
	g.DFT(+1);
	for (int i = 0; i < limit; ++i) {
		q[i] = q[i] * g[i];
		qt[i] = qt[i] * g[i];
	}
	q.DFT(-1);
	qt.DFT(-1);
	for (int i = 0; i < limit; ++i) {
		q[i].real /= limit;
		qt[i].real /= limit;
	}
	for (int i = 1; i <= n; ++i)
		printf("%.3lf\n", q[i].real - qt[n - i].real);
	return 0;
}