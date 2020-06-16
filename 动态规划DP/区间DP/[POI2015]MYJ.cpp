#include <algorithm>
#include <cstdio>
using namespace std;
const int maxm = 4001;
int n = 0, m = 0;
int a[maxm], b[maxm], c[maxm], d[maxm], cD = 0;
void init() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", a + i, b + i, c + i);
		d[i] = c[i];
	}
	sort(d + 1, d + m + 1);
	cD = unique(d + 1, d + m + 1) - d - 1;
	for (int i = 1; i <= m; ++i) {
		c[i] = lower_bound(d + 1, d + cD + 1, c[i]) - d;
	}
}
int f[55][55][maxm]; // 区间为 l,r  最小值为 k 时， 最大的花费和 在 哪个位置取到
int mx[55][55][maxm], pre[55][55][maxm]; // mx[l][r][k] : 区间内最小值大于等于k时的最大花费和， pre:具体的最小值
int cnt[55][maxm];
int ans[55];
void GetAnswer(int l, int r, int k) {
	if (r < l) return;
	int K = pre[l][r][k];
	int p = f[l][r][K];
	ans[p] = d[K];
	GetAnswer(l, p - 1, K);
	GetAnswer(p + 1, r, K);
}

inline void getCnt(int l, int r) {
	// 求在区间内的，过点p的，最高金额比k高的有多少人
	for (int i = l; i <= r; ++i)
		for (int j = 1; j <= cD; ++j)
			cnt[i][j] = 0;
	for (int i = 1; i <= m; ++i)
		if (l <= a[i] && b[i] <= r)
			for (int j = a[i]; j <= b[i]; ++j)
				++cnt[j][c[i]];
	for (int i = l; i <= r; ++i)
		for (int k = cD - 1; k > 0; --k)
			cnt[i][k] += cnt[i][k + 1];
}

int main() {
	init();
	for (int len = 1; len <= n; ++len) {
		for (int l = 1; l <= n - len + 1; ++l) {
			int r = l + len - 1;
			getCnt(l, r);
			for (int k = cD; k > 0; --k) {
				int Max = 0; // Max 为 [l,r]内，最小值为k时的最大总额
				for (int p = l; p <= r; ++p) {
					if (Max <= mx[l][p - 1][k] + mx[p + 1][r][k] + cnt[p][k] * d[k]) {
						Max = mx[l][p - 1][k] + mx[p + 1][r][k] + cnt[p][k] * d[k];
						f[l][r][k] = p;
					}
				}
				if (Max >= mx[l][r][k + 1]) {
					mx[l][r][k] = Max;
					pre[l][r][k] = k;
				}
				else {
					mx[l][r][k] = mx[l][r][k + 1];
					pre[l][r][k] = pre[l][r][k + 1];
				}
			}
		}
	}
	printf("%d\n", mx[1][n][1]);
	GetAnswer(1, n, 1);
	for (int i = 1; i <= n; ++i)
		printf("%d ", ans[i]);
	return 0;
}