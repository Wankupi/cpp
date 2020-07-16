#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int n = 0, m = 0;
long double a[501][501];
int c[501], sum = 0, cnt = 0;
int xv[501], base[501];
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n;++i) {
		for (int j = 1; j <= m;++j)
			cin >> a[i][j];
		xv[i] = i;
	}
	for (int i = 1; i <= n; ++i)
		cin >> c[i];
	sort(xv + 1, xv + n + 1, [](int a, int b) { return c[a] < c[b]; });
	for (int t = 1; t <= n; ++t) {
		int x = xv[t];
		for (int i = 1; i <= m; ++i)
			if(abs(a[x][i]) > 1e-5) {
				if(base[i]) {
					long double t1 = a[x][i] / a[base[i]][i];
					for (int k = i; k <= m; ++k)
						a[x][k] -= a[base[i]][k] * t1;
				}
				else {
					base[i] = x;
					++cnt;
					sum += c[x];
					break;
				}
			}
	}
	cout << cnt << ' ' << sum;
	return 0;
}