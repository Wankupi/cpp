#include <cstdio>
#include <algorithm>

typedef long long ll;
int const mod = 1004535809;
int const maxn = 1 << 19, G = 3, iG = 334845270;

inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
inline int pls(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
inline int dec(int a, int b) { return a >= b ? a - b : a - b + mod; }
inline ll pow(ll x, int b) { ll r = 1; while (b) { if (b & 1) r = r * x % mod; x = x * x % mod; b >>= 1; } return r; }

int Rev[maxn << 1];
void prepare(int n) {
	for (int bit = 0, N = 1; N <= n && N <= maxn; N <<= 1, ++bit) {
		int *rev = Rev + N - 1;
		for (int i = 1; i < N; ++i)
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
	}
}

void NTT(int *f, int N, int op) { // N = 2^j
	int *rev = Rev + N - 1;
	for (int i = 0; i < N; ++i) if (rev[i] < i) swap(f[rev[i]], f[i]);
	for (int len = 1; len < N; len <<= 1) {
		int W1 = pow(op == 1 ? G : iG, (mod - 1) / (2 * len));
		for (int l = 0; l < N; l += (len << 1)) {
			ll W = 1;
			for (int i = 0; i < len; ++i) {
				int x = f[l + i], y = W * f[l + len + i] % mod;
				f[l + i] = pls(x, y);
				f[l + len + i] = dec(x, y);
				W = W * W1 % mod;
			}
		}
	}
	if (op == -1) { ll inv = pow(N, mod - 2); for (int i = 0; i < N; ++i) f[i] = f[i] * inv % mod; }
}

void inv(int const *f, int *g, int n) { // f is input, g is result
	static int tmp[maxn];
	g[0] = pow(f[0], mod - 2);
	int limit = 2, bit = 1;
	while (true) {
		for (int i = 0; i < limit; ++i) tmp[i] = f[i], tmp[limit + i] = 0;
		NTT(tmp, limit << 1, +1);
		NTT(g, limit << 1, +1);
		for (int i = 0; i < (limit << 1); ++i) g[i] = ll(g[i]) * dec(2, ll(g[i]) * tmp[i] % mod) % mod;
		NTT(g, limit << 1, -1);
		for (int i = std::min(limit, n); i < limit << 1; ++i) g[i] = 0;
		if (limit >= n) break;
		++bit; limit <<= 1;
	}
}

inline void ln(int const *f, int *g, int n) {
	static int tmp[maxn];
	int limit = 1, bit = 0;
	while (limit < 2 * n) ++bit, limit <<= 1;
	for (int i = 0; i + 1 < limit; ++i) tmp[i] = f[i + 1] * (i + 1ll) % mod;
	tmp[limit - 1] = 0;
	inv(f, g, n);
	NTT(g, limit, +1);
	NTT(tmp, limit, +1);
	for (int i = 0; i < limit; ++i) g[i] = ll(g[i]) * tmp[i] % mod;
	NTT(g, limit, -1);
	for (int i = n - 1; i >= 1; --i) g[i] = g[i - 1] * pow(i, mod - 2) % mod;
	for (int i = n; i < limit; ++i) g[i] = 0;
	g[0] = 0;
}

int fact[maxn], ifact[maxn];
inline int binom(int A, int B) { return B < 0 || B > A ? 0 : ll(fact[A]) * ifact[B] % mod * ifact[A - B] % mod; }

inline void init(int n) {
	prepare((n + 2) * 4);
	fact[0] = 1;
	for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * ll(i) % mod;
	ifact[n] = pow(fact[n], mod - 2);
	for (int i = n; i >= 1; --i) ifact[i - 1] = ifact[i] * ll(i) % mod;
}

int f[maxn], g[maxn];

int main() {
	int n = 0;
	scanf("%d", &n);
	init(n);
	for (int i = 0; i <= n; ++i) g[i] = pow(2ll, i * (i - 1ll) / 2 % (mod - 1)) * ifact[i] % mod;
	ln(g, f, n + 1);
	int ans = ll(f[n]) * fact[n] % mod;
	printf("%d", ans);
	return 0;
}