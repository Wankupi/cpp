#include <cstdio>
typedef unsigned long long ll;
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }
int n = 0, c1 = 0, c2 = 0, c3 = 0;
ll f[2][130][130];
int main() {
	scanf("%d%d%d%d", &n, &c1, &c2, &c3);
	f[0][0][0] = 1;
	int s = 0, sum = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &s);
		sum += s;
		for (int a = 0; a <= c1; ++a)
			for (int b = max(0, sum - a - c3); b <= c2; ++b) {
				f[i & 1][a][b] = 0;
				for (int c = max(a - s, 0); c <= a; ++c)
					for (int d = max(0, a - c + b - s); d <= b; ++d)
						(f[i & 1][a][b] += f[i & 1 ^ 1][c][d]) %= 100000000000000000ll;
			}
	}
	printf("%lld", f[n & 1][c1][c2]);
	return 0;
}