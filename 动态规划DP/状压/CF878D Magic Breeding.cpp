#include <cstdio>
#include <bitset>
#include <algorithm>
using namespace std;
int const maxn = 100103;
int n = 0, k = 0, q = 0;
int a[13][maxn], b[maxn][13], cnt = 0;
bitset<4096> F[maxn];
int main() {
	scanf("%d %d %d", &n, &k, &q);
	cnt = k;
	for (int i = 1; i <= k; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &a[i][j]);
			b[j][i] = i;
		}
	}
	for (int i = 1; i <= n; ++i)
		sort(b[i] + 1, b[i] + k + 1, [i](int x, int y) -> bool { return a[x][i] > a[y][i]; });
	for (int st = 0; st < (1 << k); ++st) {
		for (int i = 0; i < k; ++i)
			if ((st >> i) & 1) F[i + 1][st] = true;
	}
	int opt = 0, x = 0, y = 0;
	for (int t = 1; t <= q; ++t) {
		scanf("%d %d %d", &opt, &x, &y);
		if (opt == 1) F[++cnt] = F[x] | F[y];
		else if (opt == 2) F[++cnt] = F[x] & F[y];
		else {
			int s = 0;
			for (int i = 1; i <= k; ++i) {
				s |= (1 << (b[y][i] - 1));
				if (F[x][s]) {
					printf("%d\n", a[b[y][i]][y]);
					break;
				}
			}
		}
	}
	return 0;
}