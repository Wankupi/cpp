#include <cstdio>
#include <cstring>
int n = 0, W = 0, w[20];
int f[1 << 18], g[1 << 18];
inline int max(int a, int b) { return a < b ? b : a; }
int main() {
	scanf("%d%d", &n, &W);
	for (int i = 0; i < n; ++i)
		scanf("%d", w + i);
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	g[0] = 0;
	for (int st = 1; st < (1 << n); ++st) {
		for (int i = 0; i < n; ++i) {
			if (st & (1 << i)) {
				int S = st ^ (1 << i);
				if (w[i] <= g[S]) {
					if (f[S] <= f[st]) {
						f[st] = f[S];
						g[st] = max(g[st], g[S] - w[i]);
					}
				}
				else {
					if (f[S] + 1 <= f[st]) {
						f[st] = f[S] + 1;
						g[st] = max(g[st], max(W - w[i], g[S]));
					}
				}
			}
		}
	}
	printf("%d", f[(1 << n) - 1]);
	return 0;
}