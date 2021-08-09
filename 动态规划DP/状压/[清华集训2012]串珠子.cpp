#include <cstdio>
typedef long long ll;

ll const mod = 1000000007;
inline ll pls(ll a, ll b) { return a + b < mod ? a + b : a + b - mod; }
inline ll dec(ll a, ll b) { return a >= b ? a - b : a - b + mod; }

int n = 0;
int c[16][16];

ll f[1 << 16], g[1 << 16];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%d", &c[i][j]);
		}
	}
	int  N = 1 << n;
	g[0] = 1;
	for (int s = 1; s < N; ++s) {
		int t = s & (s - 1), k = s & -s;
		for (int i = 0; i < n; ++i) if (k == (1 << i)) { k = i; break; }
		g[s] = g[t];
		for (int i = 0; i < n; ++i)
			if (t & (1 << i))
				g[s] = g[s] * (c[k][i] + 1) % mod;
	}
	for (int s = 0; s < N; ++s) {
		int k = s & -s;
		for (int t = s & (s - 1); t; t = (t - 1) & s) {
			if (t & k)
				f[s] = pls(f[s], f[t] * g[s ^ t] % mod);
		}
		f[s] = dec(g[s], f[s]);
	}
	printf("%lld", f[N - 1]);
	return 0;
}
