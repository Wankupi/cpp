#include <cstdio>
#include <iostream>
#include <iomanip>
int n = 0;
int x[200001], y[200001], s[200001];
inline int max(int a, int b) { return a > b ? a : b; }
bool ok(long double v) {
	long double now = 0;
	for (int i = 1; i <= n; ++i) {
		now += s[i] / v;
		if (now > y[i]) return false;
		if (now < x[i]) now = x[i];
	}
	return true;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d%d", x + i, y + i, s + i);
	long double l = 0, r = 1e8, mid = 0;
	while (r - l < 0.00001) {
		mid = (l + r) / 2;
		if (ok(mid)) r = mid;
		else l = mid;
	}
	std::fixed(std::cout);
	std::cout << std::setprecision(4) << l;
	return 0;
}