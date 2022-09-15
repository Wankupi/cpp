#include <cstdio>
int const mod = 998244353;
inline int pls(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int n = 0, k = 0;
int f[3003][6003];
int main() {
	scanf("%d %d", &n, &k);
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = i; j >= 1; --j)
			f[i][j] = pls(f[i - 1][j - 1], f[i][2 * j]);	
	printf("%d\n", f[n][k]);
	return 0;
}