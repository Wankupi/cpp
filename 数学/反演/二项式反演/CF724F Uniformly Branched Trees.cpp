#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1009;
int f[maxn][12][maxn / 2], n, d, mod;
int inv[maxn], fac[maxn];

inline void pls(int &x, int y) { x = (x + y >= mod ? x + y - mod : x + y); }
inline int dec(int &x, int y) { return (x - y < 0 ? x - y + mod : x - y); }

void init() {
	inv[1] = 1;
	for (int i = 2; i < maxn; i++)
		inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
	for (int i = 2; i < maxn; i++)
		inv[i] = (long long)inv[i - 1] * inv[i] % mod;
}

inline int C(int n, int m) {
	if (m > n) return 0;
	int res = 1;
	for (int i = n - m + 1; i <= n; i++)
		res = (long long)res * i % mod;
	return (long long)res * inv[m] % mod;
}

int main() {
	scanf("%d%d%d", &n, &d, &mod);
	if (n <= 2) { puts("1"); return 0; }
	init();
	for (int i = 0; i <= n / 2; i++) f[1][0][i] = 1;
	f[1][d - 1][0] = 1;
	for (int i = 2; i <= n; i++)
		for (int j = 1; j <= min(d, i - 1); j++)
			for (int k = 1; k <= n / 2; k++) {
				f[i][j][k] = f[i][j][k - 1];
				for (int t = 1; t * k <= i && t <= j; t++)
					pls(f[i][j][k], (long long)f[i - t * k][j - t][k - 1] * C(f[k][d - 1][k - 1] + t - 1, t) % mod);
			}
	if (n & 1) printf("%d", f[n][d][n / 2]);
	else printf("%d", dec(f[n][d][n / 2], C(f[n / 2][d - 1][n / 2 - 1], 2)));
	return 0;
}