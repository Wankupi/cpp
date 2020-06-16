#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
void read(int &x) {
	x = 0; int c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	x *= f;
}
int n = 0, x0 = 0;
struct Data { int x, v; };
bool operator<(const Data &lhs, const Data &rhs) { return lhs.x < rhs.x; }
Data da[1005];
int sumY = 0, sv[1001];
int f[2][1001][1001];
inline int min(int a, int b) { return a < b ? a : b; }
int main() {
	read(n); read(x0);
	int y = 0;
	for (int i = 1; i <= n; ++i)
		read(da[i].x);
	for (int i = 1; i <= n; ++i) {
		read(y); sumY += y;
	}
	for (int i = 1; i <= n; ++i)
		read(da[i].v);
	sort(da + 1, da + n + 1);
	for (int i = 1; i <= n; ++i)
		sv[i] = sv[i - 1] + da[i].v;
	memset(f, 0x7f, sizeof(f));
	for (int i = 1; i <= n; ++i) {
		f[0][i][i] = f[1][i][i] =
			abs(da[i].x - x0) * sv[n];
	}
	for (int len = 2; len <= n; ++len) {
		for (int l = 1; l <= n - len + 1; ++l) {
			int r = l + len - 1;
			f[0][l][r] = min(f[0][l + 1][r] + (da[l + 1].x - da[l].x) * (sv[n] - sv[r] + sv[l]),
				f[1][l + 1][r] + (da[r].x - da[l].x) * (sv[n] - sv[r] + sv[l]));
			f[1][l][r] = min(f[0][l][r - 1] + (da[r].x - da[l].x) * (sv[n] - sv[r - 1] + sv[l - 1]),
				f[1][l][r - 1] + (da[r].x - da[r - 1].x) * (sv[n] - sv[r - 1] + sv[l - 1]));
		}
	}
	double ans = (sumY - min(f[0][1][n], f[1][1][n])) / 1000.0;
	printf("%.3lf", ans);
	return 0;
}