#include <cstdio>
#include <algorithm>
int const maxm = 20003, mod = 1004535809;
const int G1 = 3, G_1 = 334845270;
int n = 0, m = 0, X = 0, cntM = 0;
int lgm[maxm];

bool checkYvanGen(int x) {
	bool tmp[maxm] = { 0 };
	int mi = 1;
	for (int i = 1; i <= m - 1; ++i) {
		mi = mi * x % m;
		if (tmp[mi]) return false;
		tmp[mi] = true;
	}
	return true;
}
int find_YvanGen() {
	int g = 2;
	while (!checkYvanGen(g)) ++g;
	int mi = 1;
	lgm[1] = 0;
	for (int i = 1; i < m - 1; ++i) {
		mi = mi * g % m;
		lgm[mi] = i;
	}
	return g;
}

int limit = 1, bit = 0, invlimit;
int rev[maxm];

int pow(int x, int b) {
	int r = 1;
	while (b) {
		if (b & 1) r = (long long)r * x % mod;
		x = (long long)x * x % mod;
		b >>= 1;
	}
	return r;
}

class Polynomial {
public:
	Polynomial() : f{ 0 } {}
	Polynomial(int) : f{ 0 } { f[0] = 1; }
	int& operator[](int x) { return f[x]; }
	void DFT(int op) {
		for (int i = 0; i < limit; ++i)
			if (rev[i] < i) std::swap(f[rev[i]], f[i]);
		for (int len = 1; len < limit; len <<= 1) {
			int W1 = pow(op == 1 ? G1 : G_1, (mod - 1) / (2 * len));
			for (int l = 0; l < limit; l += 2 * len) {
				int o = 1;
				for (int i = 0; i < len; ++i) {
					int x = f[l + i], y = f[l + len + i];
					f[l + i] = (x + (long long)o * y % mod) % mod;
					f[l + len + i] = (x - (long long)o * y % mod) % mod;
					o = (long long)o * W1 % mod;
				}
			}
		}
	}
private:
	int f[maxm];
};
Polynomial operator*(Polynomial A, Polynomial B) {
	A.DFT(1); B.DFT(1);
	Polynomial C;
	for (int i = 0; i < limit; ++i) C[i] = (long long)A[i] * B[i] % mod;
	C.DFT(-1);
	for (int i = 0; i < limit; ++i) C[i] = (long long)C[i] * invlimit % mod;
	for (int i = m - 1; i < limit; ++i) {
		C[i % (m - 1)] = (C[i % (m - 1)] + C[i]) % mod;
		C[i] = 0;
	}
	
	return C;
}
Polynomial p1;

Polynomial pow(Polynomial x, int b) {
	Polynomial r(1);
	while (b) {
		if (b & 1) r = r * x;
		x = x * x;
		b >>= 1;
	}
	return r;
}

int main() {
	scanf("%d %d %d %d", &n, &m, &X, &cntM);
	find_YvanGen();
	X = lgm[X];
	while (limit < 2 * m) limit <<= 1, ++bit;
	invlimit = pow(limit, mod - 2);
	for (int i = 1; i < limit; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
	int s = 0;
	for (int i = 1; i <= cntM; ++i) {
		scanf("%d", &s);
		if (s == 0) continue;
		++p1[lgm[s]];
	}
	Polynomial res = pow(p1, n);
	int ans = res[X];
	if (ans < 0) ans += mod;
	printf("%d", ans);
	return 0;
}