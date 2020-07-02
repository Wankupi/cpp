#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 6800;
const ll mod = 998244353;
int c = 0;
ll y[maxn], f[maxn][maxn];

int main() {
	int T = 0;
	scanf("%d", &T);
	for (int _t = 1; _t <= T; ++_t) {
		ll n = 0;
		scanf("%lld", &n);
		c = 0;
		for (ll i = 1; i * i <= n; ++i)
			if (n % i == 0) {
				y[++c] = i;
				if (i * i != n) y[++c] = n / i;
			}
		sort(y + 1, y + c + 1);
		f[1][1] = 1;
		for (int i = 1; i <= c; ++i) { //采用 推出式写法 转移到?
			for (int j = 1; j <= c; ++j)
				f[i][j] = (f[i][j] + f[i][j - 1]) % mod;
			int t = i + 1;
			for (int j = 1; j <= c && y[i] * y[j + 1] <= n; ++j) {
				if (f[i][j] == 0) continue;
				while (t <= c && y[i] * y[j + 1] > y[t])
					++t;
				if (y[i] * y[j + 1] == y[t])
					f[t][j + 1] = (f[t][j + 1] + f[i][j]) % mod;
			}
		}
		printf("%lld\n", (f[c][c] - 1 + mod) % mod);
		memset(f, 0, sizeof(f));
	}

	return 0;
}