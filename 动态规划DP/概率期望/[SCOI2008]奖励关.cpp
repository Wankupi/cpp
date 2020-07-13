#include <cstdio>
int k = 0, n = 0;
int p[20];
int s[17];
int cnt[70000];
double f[105][65600];
inline bool check(int x) {
	for (int i = 0; i < n; ++i)
		if (((x >> i) & 1) == 1 && ((x & s[i + 1]) != s[i + 1]))
			return false;
	return true;
}
inline double max(double a, double b) { return a < b ? b : a; }
int main() {
	scanf("%d%d", &k, &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", p + i);
		int x = 0;
		while (scanf("%d", &x)) {
			if (x == 0) break;
			s[i] |= (1 << (x - 1));
		}
	}
	for (int st = 1; st < (1 << n); ++st)
		for (int i = 0; i < n; ++i)
			if ((st >> i) & 1) ++cnt[st];
	for (int i = k; i >= 1; --i) {
		for (int st = 0; st < (1 << n); ++st)
			if (cnt[st] - 1 <= i && check(st)) {
				for (int j = 0; j < n; ++j)
					if (check(st | (1 << j)))
						f[i][st] += max(f[i + 1][st], f[i + 1][st | (1 << j)] + p[j + 1]);
					else
						f[i][st] += f[i + 1][st];
				f[i][st] /= n;
			}
	}
	printf("%.6lf", f[1][0]);
	return 0;
}