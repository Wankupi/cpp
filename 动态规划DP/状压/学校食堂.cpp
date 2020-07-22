#include <cstdio>
#include <cstring>
const int delta = +8, inf = 0x3f3f3f3f;
int n = 0;
int t[1001], b[1001];
int f[1005][256][20];
// inline bool check(int st, int x) { // This is no-need and wrong. bu why?
// 	for (int i = 0; i <= 7 && x + i <= n; ++i)
// 		if ((st >> i) & 1) {
// 			for (int j = b[i + x] + 1; j <= 7; ++j)
// 				if ((st >> j) & 1) return false;
// 		}
// 	return true;
// }
inline int min(int a, int b) { return a < b ? a : b; }
int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", t + i, b + i);
		memset(f, 0x3f, sizeof f);
		f[1][0][-1 + delta] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int st = 0; st < (1 << 8); ++st) {
				//if (!check(st, i)) continue;
				for (int k = -8; k <= b[i]; ++k) {
					if (f[i][st][k + delta] == inf) continue;
					if (st & 1)
						f[i + 1][st >> 1][k - 1 + delta] = min(f[i + 1][st >> 1][k - 1 + delta], f[i][st][k + delta]);
					else {
						int limits = b[i];
						for (int p = 0; p <= limits; ++p) {
							if ((st >> p) & 1) continue;
							limits = min(limits, p + b[i + p]);
							f[i][st | (1 << p)][p + delta] =
								min(f[i][st | (1 << p)][p + delta], f[i][st][k + delta] + (i + k ? t[i + k] ^ t[i + p] : 0));
						}
					}
				}
			}
		}
		int ans = inf;
		for (int k = -8; k <= 0; ++k)
			ans = min(ans, f[n + 1][0][k + delta]);
		printf("%d\n", ans);
	}
	return 0;
}