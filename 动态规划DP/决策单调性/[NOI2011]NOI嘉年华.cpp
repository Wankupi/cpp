#include <cstdio>
#include <algorithm>
#include <cstring>
using std::max;
using std::min;
int const maxn = 203, maxT = maxn << 1;
int n = 0;
int S[maxn], T[maxn]; // redefine: S begin time, T end time
int Times[maxT], cT = 0;
int c[maxT][maxT]; // contain
int f[maxT][maxn], g[maxT][maxn];
int s[maxT][maxT];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", S + i, T + i);
		T[i] += S[i];
		++S[i];
		Times[++cT] = S[i];
		Times[++cT] = T[i];
	}
	Times[++cT] = 0;
	Times[++cT] = 2147483647;
	std::sort(Times + 1, Times + cT + 1);
	cT = std::unique(Times + 1, Times + cT + 1) - Times - 1;
	for (int i = 1; i <= n; ++i) {
		S[i] = std::lower_bound(Times + 1, Times + cT + 1, S[i]) - Times;
		T[i] = std::lower_bound(Times + 1, Times + cT + 1, T[i]) - Times;
		for (int l = S[i]; l >= 1; --l)
			for (int r = T[i]; r <= cT; ++r)
				++c[l][r];
	}
	memset(f, -0x3f, sizeof f);
	memset(g, -0x3f, sizeof g);
	memset(s, -0x3f, sizeof s);
	f[0][0] = 0;
	for (int i = 1; i <= cT; ++i) {
		for (int j = 0; j < i; ++j) {
			for (int k = n; k >= c[j + 1][i]; --k)
				f[i][k] = max(f[i][k], f[j][k - c[j + 1][i]]);
		}
		for (int k = 0; k <= n; ++k) {
			for (int j = i - 1; j >= 0; --j)
				f[i][k] = max(f[i][k], f[j][k] + c[j + 1][i]);
		}
		for (int k = n - 1; k >= 0; --k) f[i][k] = max(f[i][k], f[i][k + 1]);
	}
	g[cT + 1][0] = 0;
	for (int i = cT; i >= 1; --i) {
		for (int j = i + 1; j <= cT + 1; ++j) {
			for (int k = n; k >= c[i][j - 1]; --k)
				g[i][k] = max(g[i][k], g[j][k - c[i][j - 1]]);
		}
		for (int k = 0; k <= n; ++k) {
			for (int j = i + 1; j <= cT + 1; ++j)
				g[i][k] = max(g[i][k], g[j][k] + c[i][j - 1]);
		}
		for (int k = n - 1; k >= 0; --k) g[i][k] = max(g[i][k], g[i][k + 1]);
	}

	for (int l = 1; l <= cT; ++l) {
		for (int r = l; r <= cT; ++r) {
			for (int i = 0, j = n; i <= n; ++i) {
				while (j >= 0) {
					int val = min(f[l - 1][i] + g[r + 1][j], i + j + c[l][r]);
					if (val >= s[l][r]) s[l][r] = val;
					else break;
					--j;
				}
				if (j < n) ++j;
			}
		}
	}
	int FirstAns = 0;
	for (int k = 0; k <= n; ++k)
		FirstAns = max(FirstAns, min(f[cT][k], k));
	printf("%d\n", FirstAns);
	for (int i = 1; i <= n; ++i) {
		int ans = 0;
		for (int l = S[i]; l >= 1; --l)
			for (int r = T[i]; r <= cT; ++r)
				ans = max(ans, s[l][r]);
		printf("%d\n", ans);
	}
	return 0;
}