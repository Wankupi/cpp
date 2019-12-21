#include <iostream>
using namespace std;
inline long long max(long long a, long long b) { return a > b ? a : b; }
inline long long min(long long a, long long b) { return a < b ? a : b; }
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
char oper[105];
long long a[105], f[105][105], g[105][105];
int main() {
	int n = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> oper[i] >> a[i];
		oper[i + n] = oper[i];
	}
	for (int i = 1; i <= n; ++i) {
		f[i][i] = f[i + n][i + n] = a[i];
		g[i][i] = g[i + n][i + n] = a[i];
	}
	for (int len = 2; len <= n; ++len) {
		for (int i = 1; i + len - 1 <= 2 * n; ++i) {
			int r = i + len - 1;
			f[i][r] = -INF;
			g[i][r] = INF;
			for (int k = i; k != r; ++k) {
				if (oper[k + 1] == 't') {//加法
					f[i][r] = max(f[i][r], f[i][k] + f[k + 1][r]);
					g[i][r] = min(g[i][r], g[i][k] + g[k + 1][r]);
				}
				else {
					f[i][r] = max(f[i][r],
						max(max(f[i][k] * f[k + 1][r], g[i][k] * g[k + 1][r]),
							max(f[i][k] * g[k + 1][r], g[i][k] * f[k + 1][r])));
					g[i][r] = min(g[i][r],
						min(min(f[i][k] * f[k + 1][r], g[i][k] * g[k + 1][r]),
							min(f[i][k] * g[k + 1][r], g[i][k] * f[k + 1][r])));
				}
			}
		}
	}
	long long re = -INF, ans[60] = { 0 };
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (re < f[i][i + n - 1]) {
			ans[cnt = 0] = i;
			re = f[i][i + n - 1];
		}
		else if (re == f[i][i + n - 1]) {
			ans[++cnt] = i;
		}
	}
	cout << re << endl;
	for (int i = 0; i <= cnt; ++i) {
		cout << ans[i] << ' ';
	}
	return 0;
}