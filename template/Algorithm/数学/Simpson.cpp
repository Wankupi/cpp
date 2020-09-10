#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const double eps = 0.00000001;
double a = 0, b = 0, c = 0, d = 0;
inline double f(double x) { return (c * x + d) / (a * x + b); }
inline double Simpson(double L, double R) {
	return (R - L) * (f(L) + f(R) + 4 * f((L + R) / 2)) / 6;
}
double calc(double l, double r, double ans) {
	double mid = (l + r) / 2.0;
	double lRes = Simpson(l, mid), rRes = Simpson(mid, r);
	if (abs(lRes + rRes - ans) < eps) return lRes + rRes;
	return calc(l, mid, lRes) + calc(mid, r, rRes);
}
int main() {
	double L = 0, R = 0;
	cin >> a >> b >> c >> d >> L >> R;
	printf("%.6lf",calc(L,R,1e7));
	return 0;
}