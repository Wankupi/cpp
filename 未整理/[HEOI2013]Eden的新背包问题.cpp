#include <cstdio>
const int maxn = 1010, maxV = 1000;
int n = 0;
int v[maxn], w[maxn], t[maxn];
int f[maxn][maxn], g[maxn][maxn];

inline int max(int a, int b) { return a < b ? b : a; }
inline int min(int a, int b) { return a < b ? a : b; }
int q[maxn], l = 0, r = 0;
int use[maxn];
void dcbb(int (&dp)[maxn][maxn], int i, int last) {
	for (int d = 0; d < v[i]; ++d) {
		l = 1; r = 0;
		for (int j = 0; d + v[i] * j <= maxV; ++j) {
			int k = dp[last][j * v[i] + d] - w[i] * j;
			while (l <= r && q[r] <= k) --r;
			q[++r] = k;
			use[r] = j;
			while (l <= r && j - use[l] > t[i]) ++l;
			dp[i][j * v[i] + d] = max(dp[last][j * v[i] + d], q[l] + w[i] * j);
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d%d", v + i, w + i, t + i);
	for (int i = 1; i <= n; ++i)
		dcbb(f, i, i - 1);
	for (int i = n; i; --i)
		dcbb(g, i, i + 1);
	int q = 0, d = 0, e = 0;
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d", &d, &e);
		++d;
		int ans = 0;
		for (int v = 0; v <= e; ++v)
			ans = max(ans, f[d - 1][v] + g[d + 1][e - v]);
		printf("%d\n", ans);
	}
	return 0;
}