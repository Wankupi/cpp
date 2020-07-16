#include <cstdio>
typedef long long ll;
int n = 0, k = 0;
int lin[100], num[100], cnt = 0;
ll f[10][100][100];
inline int Count(int x) {
	int ret = 0;
	for (int i = 10; ~i; --i)
		if ((1 << i) & x)
			++ret;
	return ret;
}
inline bool check(int a, int b) {
	return (a & b) == 0 && ((a << 1) & b) == 0 && (a & (b << 1)) == 0;
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < (1 << n); ++i)
		if ((i & (i << 1)) == 0 && Count(i) <= k) {
			lin[cnt] = i;
			num[cnt] = Count(i);
			++cnt;
		}
	f[0][0][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int s = 0; s != cnt; ++s)
			for (int m = num[s]; m <= k; ++m)
				for (int la = 0; la != cnt; ++la)
					if (check(lin[s], lin[la]))
						f[i][s][m] += f[i - 1][la][m - num[s]];
	ll sum = 0;
	for (int i = 0; i != cnt; ++i)
		sum += f[n][i][k];
	printf("%lld", sum);
	return 0;
}