// 一般路径的交叉 
// 可以和
// 交叉起电和终点后的路径
// 建立一一映射

#include <cstdio>
#include <cstring>
typedef long long ll;
const ll mod = 1000000007;
int n = 0, m = 0;
char map[3001][3001];
ll f[3001];
ll A = 0, B = 0, C = 0, D = 0;
int main() {
	scanf("%d %d\n", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%s", map[i] + 1);
	memset(f, 0, sizeof f);
	f[1] = 1;
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (map[i][j] == '.')
				f[j] = (f[j - 1] + f[j]) % mod;
			else
				f[j] = 0;
		}
		if (i == n - 1) C = f[m];
	}
	A = f[m - 1];
	memset(f, 0, sizeof f);
	f[1] = 1;
	for (int i = 1; i <= n; ++i) {
		if (i > 1) f[1] = 0;
		for (int j = 2; j <= m; ++j) {
			if (map[i][j] == '.')
				f[j] = (f[j - 1] + f[j]) % mod;
			else
				f[j] = 0;
		}
		if (i == n - 1) B = f[m];
	}
	D = f[m - 1];
	ll ans = (A * B % mod - C * D % mod + mod) % mod;
	printf("%lld", ans);
	return 0;
}