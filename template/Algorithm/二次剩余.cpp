#include <cstdio>
#include <cstdlib>
#include <algorithm>
using std::swap;
typedef long long ll;
ll n = 0, p = 0;
ll pow(ll x, ll b) {
	ll ret = 1;
	while (b) {
		if (b & 1) ret = ret * x % p;
		x = x * x % p;
		b >>= 1;
	}
	return ret;
}
ll I2 = 0;
struct Complex {
	Complex(ll R, ll I) { real = R, ima = I; }
	ll real, ima;
};
Complex operator*(const Complex &A, const Complex &B) {
	return Complex((A.real * B.real % p + A.ima * B.ima % p * I2 % p) % p,
				   (A.real * B.ima % p + A.ima * B.real % p) % p);
}
Complex pow(Complex x, ll b) {
	Complex ret(1, 0);
	while (b) {
		if (b & 1) ret = ret * x;
		x = x * x;
		b >>= 1;
	}
	return ret;
}
int main() {
	int T = 0;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		scanf("%lld%lld", &n, &p);
		if (n == 0) {
			printf("0\n");
			continue;
		}
		if (pow(n, (p - 1) / 2) == p - 1) {
			printf("Hola!\n");
			continue;
		}
		ll a = 0;
		do
			a = rand();
		while (pow((a * a % p - n + p) % p, (p - 1) / 2) == 1);
		I2 = ((a * a - n) % p + p) % p;
		ll x1 = pow(Complex(a, 1), (p + 1) / 2).real;
		ll x2 = (p - x1) % p;
		if (x1 > x2) swap(x1, x2);
		printf("%lld %lld\n", x1, x2);
	}
	return 0;
}