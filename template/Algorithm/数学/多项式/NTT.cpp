#include <algorithm>
#include <cstdio>
#include <cstring>
int const mod = 998244353;
int pow(int x, int b) {
	int r = 1;
	while (b) { if (b & 1) r = (long long)r * x % mod; x = (long long)x * x % mod; b >>= 1; }
	return r;
}

int limit = 1, M = 0;
int rev[1 << 21];
int a[1 << 21], b[1 << 21], A = 0, B = 0;
int c[1 << 21];
char str[1 << 21];

inline int W(int k, int n, int type) { return pow(type == 1 ? 3 : 332748118, (mod - 1) / n * k); }
void DFT(int(&f)[1 << 21], int op) {
	for (int i = 0; i != limit; ++i)
		if (rev[i] < i) std::swap(f[i], f[rev[i]]);
	for (int len = 1; len < limit; len <<= 1) {
		int W1 = W(1, 2 * len, op);
		for (int l = 0; l < limit; l += len * 2) {
			int ome = 1;
			for (int i = 0; i < len; ++i) {
				int x = f[l + i], y = f[l + len + i];
				f[l + i] = x + (long long)ome * y % mod;
				f[l + len + i] = x - (long long)ome * y % mod;
				f[l + i] %= mod;
				f[l + len + i] %= mod;
				ome = (long long)ome * W1 % mod;
			}
		}
	}
}

int main() {
	scanf("%s", str);
	A = strlen(str);
	for (int i = 0; i < A; ++i) a[A - i - 1] = str[i] - '0';
	scanf("%s", str);
	B = strlen(str);
	for (int i = 0; i < B; ++i) b[B - i - 1] = str[i] - '0';

	while (limit < A + B) ++M, limit <<= 1;
	for (int i = 1; i < limit; ++i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (M - 1));

	DFT(a, 1);
	DFT(b, 1);
	for (int i = 0; i < limit; ++i) c[i] = (long long)a[i] * b[i] % mod;
	DFT(c, -1);
	int inv = pow(limit, mod - 2);
	for (int i = 0; i < limit; ++i) c[i] = ((long long)c[i] * inv % mod + mod) % mod;

	int Jin = 0, C = 0;
	for (int i = 0; i <= A + B; ++i) {
		Jin += c[i];
		str[i] = (Jin % 10) + '0';
		Jin /= 10;
		C = i;
	}
	bool head = true;
	for (int i = C; i >= 0; --i) {
		if (head && str[i] == '0') continue;
		putchar(str[i]);
		head = false;
	}
	if (head) putchar('0');
	printf("\n");
	return 0;
}