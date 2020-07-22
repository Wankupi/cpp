#include <cstdio>
typedef long long ll;
const ll mod = 1000000007;
ll f[32][32][1 << 9][13];
inline int min(int a, int b) { return a < b ? a : b; }
int main() {
	int n = 0, m = 0, k = 0;
	scanf("%d%d%d", &n, &m, &k);
	f[1][0][0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			for (int s = 0; s < (1 << (k + 1)); ++s) {
				for (int r = min(k, i - 1); r >= 1; --r) {
					(f[i][j][s][r - 1] += f[i][j][s][r]) %= mod;
					if (j < m)
						(f[i][j + 1][s ^ (1 << r) ^ 1][r] += f[i][j][s][r]) %= mod;
				}
				if (((s >> k) & 1) == 0) {
					(f[i + 1][j][(s << 1)/* & ((1 << (k + 1)) - 1)*/][min(k, i)] += f[i][j][s][0]) %= mod;
				}
			}
		}
	}
	printf("%lld", f[n][m][0][0]);
	return 0;
}