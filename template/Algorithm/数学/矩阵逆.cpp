#include <algorithm>
#include <cstdio>
using namespace std;
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x;
}
typedef long long ll;
int n = 0, d = 0;
const ll mod = 1000000007;
inline ll pow(ll x, ll a) {
	ll ret = 1;
	while (a) {
		if (a & 1) ret = ret * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return ret;
}
ll w[403][807];
inline bool Gauss() {
	for (int i = 1; i <= n; ++i) {
		if (w[i][i] == 0)
			for (int j = i + 1; j <= n; ++j)
				if (w[j][i]) {
					for (int t = i; t <= n << 1; ++i) swap(w[i][t], w[j][t]);
					break;
				}
		if (w[i][i] == 0) return false;
		ll a = pow(w[i][i], mod - 2);
		for (int t = i; t <= n << 1; ++t)
			w[i][t] = w[i][t] * a % mod;
		for (int j = 1; j <= n; ++j)
			if (i != j) {
				a = w[j][i];
				for (int t = i; t <= n << 1; ++t)
					w[j][t] = (w[j][t] - a * w[i][t] % mod + mod) % mod;
			}
	}
	return true;
}

int main() {
	n = read();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			w[i][j] = read();
		w[i][n + i] = 1;
	}
	if (Gauss()) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j)
				printf("%lld ", w[i][j + n]);
			putchar('\n');
		}
	}
	else
		printf("No Solution");
	return 0;
}