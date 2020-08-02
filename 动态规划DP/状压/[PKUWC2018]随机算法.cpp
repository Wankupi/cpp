#include <cstdio>
typedef long long ll;
const ll mod = 998244353;
int n = 0, m = 0;
int w[21];
inline int max(int a, int b) { return a < b ? b : a; }
inline int lowbit(int x) { return x & -x; }
int which[1 << 20];
int crash[1 << 20], siz[1 << 20], all[1 << 20]; // all 相关点集
int maxInd = 0;
ll f[1 << 20];
ll inv[30];
int main() {
	scanf("%d%d", &n, &m);
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		w[x - 1] |= 1 << (y - 1);
		w[y - 1] |= 1 << (x - 1);
	}
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; ++i)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 0; i < n; ++i)
		which[1 << i] = i;
	for (int S = 1; S < (1 << n); ++S) {
		int fr = S ^ lowbit(S), i = which[lowbit(S)];
		crash[S] = crash[fr] | (fr & w[i]);
		all[S] = S | all[fr] | w[i];
		siz[S] = siz[fr] + 1;
		if (crash[S] == 0) maxInd = max(maxInd, siz[S]);
	}
	long long ans = 0;
	f[0] = 1;
	for (int S = 1; S < (1 << n); ++S) {
		if (crash[S]) continue;
		for (int i = 0; i < n; ++i) {
			if (((S >> i) & 1) == 0) continue;
			int fr = S ^ (1 << i);
			f[S] = (f[S] + f[fr] * inv[n - siz[all[fr]]] % mod) % mod;
		}
		if (siz[S] == maxInd) ans = (ans + f[S]) % mod;
	}
	printf("%lld", ans);
	return 0;
}