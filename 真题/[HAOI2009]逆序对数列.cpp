#include <cstdio>
const int mod = 10000;
int n = 0, k = 0;
int f[1010][1010];
int main() {
	scanf("%d%d", &n, &k);
	f[1][0] = 1;
	for (int i = 2; i <= n; i++) {
		int sum = 0;
		for (int j = 0; j <= k; j++) {
			sum = (sum + f[i - 1][j]) % mod;
			f[i][j] = sum;
			if (j >= i - 1)
				sum = ((sum - f[i - 1][j - i + 1]) % mod + mod) % mod;
		}
	}
	printf("%d\n", f[n][k]);
	return 0;
}