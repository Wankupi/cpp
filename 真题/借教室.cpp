#include <cstdio>
constexpr int maxN = 1000001;
int r[maxN], d[maxN], s[maxN], t[maxN];
int dif[maxN];//差分
inline int min(int a, int b) { return a < b ? a : b; }
int main() {
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", r + i);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", d + i, s + i, t + i);
		dif[t[i] + 1] -= d[i]; dif[s[i]] += d[i];
	}
	int sum = 0, j = m;
	for (int i = 1; i <= n; ++i) {
		sum += dif[i];
		while (sum > r[i]) {
			dif[t[j] + 1] += d[j];
			dif[s[j]] -= d[j];
			if (s[j] <= i && i <= t[j]) sum -= d[j];
			--j;
		}
	}
	if (j==m) printf("0");
	else printf("-1\n%d", j + 1);
	return 0;
}