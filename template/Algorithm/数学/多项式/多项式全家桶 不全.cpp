#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long ll;
int const maxn = 1 << 18;
int const mod = 998244353, G = 3, iG = 332748118;
inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
inline int plus(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
inline int dec(int a, int b) { return a >= b ? a - b : a - b + mod; }
inline int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
inline int read_mod() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = plus(x * 10ll % mod, c - '0'); c = getchar(); }
	return x * f;
}
int pow(ll x, int b) { ll r = 1; while (b) { if (b & 1) r = r * x % mod; x = x * x % mod; b >>= 1; } return int(r); }

class Polynomial {
public:
	static void prepare(int);
	int &operator[](int x) { return f[x]; }
	int const &operator[](int x) const { return f[x]; }
	void NTT(int N, int op);
	void inv(Polynomial &Res, int n) const;
	void ln(Polynomial &res, int n) const;
	void exp(Polynomial &res, int n) const;
	void Pow(Polynomial &res, int n, int k) const;
	void clear(int n) {
		int limit = 1;
		while (limit < n) limit <<= 1;
		memset(f, 0, sizeof(int) * limit);
	}
private:
	int f[maxn];
	static int Rev[maxn << 1];
};
int Polynomial::Rev[maxn << 1];
void Polynomial::prepare(int n) {
	for (int bit = 0, N = 1; N <= n && N <= maxn; N <<= 1, ++bit) {
		int *rev = Rev + N - 1;
		for (int i = 1; i < N; ++i)
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
	}
}
void Polynomial::NTT(int N, int op) {
	int *rev = Rev + N - 1;
	for (int i = 0; i < N; ++i) if (rev[i] < i) swap(f[rev[i]], f[i]);
	for (int len = 1; len < N; len <<= 1) {
		int W1 = pow(op == 1 ? G : iG, (mod - 1) / (2 * len));
		for (int l = 0; l < N; l += (len << 1)) {
			int W = 1;
			for (int i = 0; i < len; ++i) {
				int x = f[l + i], y = (long long)W * f[l + len + i] % mod;
				f[l + i] = plus(x, y);
				f[l + len + i] = dec(x, y);
				W = (long long)W * W1 % mod;
			}
		}
	}
	if (op == -1) { ll inv = pow(N, mod - 2); for (int i = 0; i < N; ++i) f[i] = (long long)f[i] * inv % mod; }
}
void Polynomial::inv(Polynomial &g, int n) const {
	static Polynomial tmp;
	g.clear(n);
	g[0] = pow(f[0], mod - 2);
	int limit = 2, bit = 1;
	while (true) {
		for (int i = 0; i < limit; ++i) tmp[i] = f[i], tmp[limit + i] = 0;
		tmp.NTT(limit << 1, +1);
		g.NTT(limit << 1, +1);
		for (int i = 0; i < limit << 1; ++i) g[i] = (long long)g[i] * dec(2, (long long)g[i] * tmp[i] % mod) % mod;
		g.NTT(limit << 1, -1);
		for (int i = std::min(limit, n); i < limit << 1; ++i) g[i] = 0;
		if (limit >= n) break;
		++bit; limit <<= 1;
	}
}
void Polynomial::ln(Polynomial &res, int n) const {
	static Polynomial tmp;
	int limit = 1, bit = 0;
	while (limit < 2 * n) ++bit, limit <<= 1;
	for (int i = 0; i + 1 < limit; ++i) tmp[i] = f[i + 1] * (i + 1ll) % mod;
	tmp[limit - 1] = 0;
	inv(res, n);
	res.NTT(limit, +1);
	tmp.NTT(limit, +1);
	for (int i = 0; i < limit; ++i) res[i] = (long long)res[i] * tmp[i] % mod;
	res.NTT(limit, -1);
	for (int i = n - 1; i >= 1; --i) res[i] = (long long)res[i - 1] * pow(i, mod - 2) % mod;
	for (int i = n; i < limit; ++i) res[i] = 0;
	res[0] = 0;
}
void Polynomial::exp(Polynomial &g, int n) const {
	static Polynomial tmp;
	g.clear(n);
	g[0] = 1;
	int limit = 2, bit = 1;
	while (true) {
		g.ln(tmp, std::min(limit, n));
		for (int i = 0; i < limit; ++i) tmp[i] = plus(dec(f[i], tmp[i]), i == 0);
		tmp.NTT(limit << 1, +1);
		g.NTT(limit << 1, +1);
		for (int i = 0; i < limit << 1; ++i) g[i] = (long long)g[i] * tmp[i] % mod;
		g.NTT(limit << 1, -1);
		for (int i = std::min(limit, n); i < limit << 1; ++i) g[i] = 0;
		if (limit >= n) break;
		++bit; limit <<= 1;
	}
}

void Polynomial::Pow(Polynomial &res, int n, int k) const {
	static Polynomial tmp;
	ln(tmp, n);
	for (int i = 0; i < n; ++i) tmp[i] = (long long)k * tmp[i] % mod;
	tmp.exp(res, n);
}
Polynomial f, g;
int main() {
	int n = read();
	int k = read_mod();
	Polynomial::prepare(n * 4);
	for (int i = 0; i < n; ++i) f[i] = read();
	f.Pow(g, n, k);
	for (int i = 0; i < n; ++i) printf("%d ", g[i]);
	printf("\n");
	return 0;
}