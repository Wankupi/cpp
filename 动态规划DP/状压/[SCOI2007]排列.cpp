#include <cstdio>
#include <cstring>
char str[15];
int n[13], c = 0, d = 0, to[10];
int fact[12];
int f[2050][1003];
int main() {
	fact[0] = 1;
	for (int i = 1; i <= 10; ++i)
		fact[i] = fact[i - 1] * i;
	int T = 0;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		scanf("%s%d", str + 1, &d);
		for (int i = 1; str[i] != 0; ++i)
			n[i] = str[i] - '0', c = i;
		memset(f, 0, sizeof f);
		f[0][0] = 1;
		for (int st = 1; st < (1 << c); ++st) {
			for (int i = 0; i < c; ++i)
				if ((st >> i) & 1) {
					int fr = st ^ (1 << i);
					for (int k = 0; k < d; ++k)
						f[st][(k * 10 + n[i + 1]) % d] += f[fr][k];
				}
		}
		for (int i = 0; i <= 9; ++i)
			to[i] = 0;
		for (int i = 1; i <= c; ++i)
			++to[n[i]];
		int ans = f[(1 << c) - 1][0];
		for (int i = 0; i <= 9; ++i)
			ans /= fact[to[i]];
		printf("%d\n", ans);
	}
	return 0;
}