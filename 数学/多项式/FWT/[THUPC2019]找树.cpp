#include <cstdio>
#include <cstring>
#include <algorithm>
int const mod = 1000000007, inv2 = (mod + 1) / 2;
inline int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
inline int plus(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
inline int jian(int a, int b) { return a >= b ? a - b : a - b + mod; }
int n = 0, m = 0, w = 0, W = 0;
char opt[15];
int mat[71][71][1 << 12];

inline void AND(int &A, int &B, int op) { A = plus(A, op * B); if (A < 0) A += mod; }
inline void OR(int &A, int &B, int op) { B = plus(B, op * A); if (B < 0) B += mod; }
inline void XOR(int &A, int &B, int op) {
	int x = A, y = B;
	A = plus(x, y);
	B = jian(x, y);
	if (op != 1) {
		A = (long long)A * op % mod;
		B = (long long)B * op % mod;
	}
	if (A < 0) A += mod; if (B < 0) B += mod;
}
void FWT(int *f, int op) {
	for (int len = 1, bit = 0; len < W; len <<= 1, ++bit) {
		if (opt[bit] == '&')
			for (int l = 0; l < W; l += 2 * len) for (int i = 0; i < len; ++i) AND(f[l + i], f[l + len + i], op);
		else if (opt[bit] == '|')
			for (int l = 0; l < W; l += 2 * len) for (int i = 0; i < len; ++i) OR(f[l + i], f[l + len + i], op);
		else if (opt[bit] == '^')
			for (int l = 0; l < W; l += 2 * len) for (int i = 0; i < len; ++i) XOR(f[l + i], f[l + len + i], op == 1 ? 1 : inv2);
	}
}
inline int pow(int x, int b) {
	int r = 1;
	while (b) {
		if (b & 1) r = (long long)r * x % mod;
		x = (long long)x * x % mod;
		b >>= 1;
	}
	return r;
}
int a[71][71];
int det() {
	int r = 1;
	for (int i = 1; i < n; ++i) {
		if (!a[i][i]) {
			int j = i + 1;
			while (j < n && !a[j][i]) ++j;
			if (j >= n) return 0;
			std::swap(a[i], a[j]);
			r = mod - r;
		}
		int inv = pow(a[i][i], mod - 2);
		for (int j = i + 1; j < n; ++j)
			if (a[j][i]) {
				long long k = (long long)a[j][i] * inv;
				for (int p = 1; p < n; ++p)
					a[j][p] = jian(a[j][p], k * a[i][p] % mod);
			}
	}
	for (int i = 1; i < n; ++i) r = (long long)r * a[i][i] % mod;
	return r;
}
int c[1 << 12];
int main() {
	scanf("%d %d", &n, &m);
	scanf("%s", opt);
	w = strlen(opt);
	W = 1 << w;
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		x = read(); y = read(); z = read();
		++mat[x][x][z]; ++mat[y][y][z];
		--mat[x][y][z]; --mat[y][x][z];
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			for (int s = 0; s < W; ++s)
				if (mat[i][j][s] < 0) mat[i][j][s] += mod;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			FWT(mat[i][j], +1);
	for (int s = 0; s < W; ++s) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				a[i][j] = mat[i][j][s];
		c[s] = det();
	}
	FWT(c, -1);
	int ans = -1;
	for (int i = W - 1; i >= 0; --i)
		if (c[i]) {
			ans = i;
			break;
		}
	printf("%d\n", ans);
	return 0;
}