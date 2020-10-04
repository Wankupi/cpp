#include <cstdio>
int const mod = 1000000007, inv2 = (mod + 1) / 2;
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || '9' < c)
		c = getchar();
	while ('0' <= c && c <= '9')
		x = 10 * x + c - '0', c = getchar();
	return x;
}
inline int plus(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
inline int reduce(int a, int b) { return a >= b ? a - b : a - b + mod; }

int n = 0, N = 1, bit = 0, maxS = 0;

void FWT(int *f, int op, void (*calc)(int &, int &, int)) {
	for (int len = 1; len < N; len <<= 1)
		for (int l = 0; l < N; l += (len << 1))
			for (int i = 0; i < len; ++i)
				calc(f[l + i], f[l + len + i], op);
}
void AND(int &a, int &b, int op) {
	a = plus(a, op * b);
	if (a < 0) a += mod;
}
void OR(int &a, int &b, int op) {
	b = plus(b, op * a);
	if (b < 0) b += mod;
}
void XOR(int &a, int &b, int op) {
	int x = a, y = b;
	a = plus(x, y);
	b = reduce(x, y);
	if (op != 1) {
		a = (long long)a * inv2 % mod;
		b = (long long)b * inv2 % mod;
	}
}

int s[1000003], f[1 << 17], cnt[1 << 17];
int A[18][1 << 17], AB[18][1 << 17];
int C[1 << 17], DE[1 << 17];
int ans[1 << 17];
int main() {
	n = read();
	for (int i = 1; i <= n; ++i) {
		s[i] = read();
		if (s[i] > maxS) maxS = s[i];
	}
	while (N <= maxS)
		N <<= 1, ++bit;
	f[0] = 0;
	f[1] = 1;
	for (int i = 2; i < N; ++i)
		f[i] = plus(f[i - 1], f[i - 2]);
	for (int i = 1; i < N; ++i)
		cnt[i] = cnt[i - (i & -i)] + 1;
	for (int i = 1; i <= n; ++i) {
		++A[cnt[s[i]]][s[i]];
		C[s[i]] = plus(C[s[i]], f[s[i]]);
		++DE[s[i]];
	}

	for (int i = 0; i <= bit; ++i)
		FWT(A[i], 1, OR);
	for (int i = 0; i <= bit; ++i)
		for (int j = 0; j <= i; ++j)
			for (int S = 0; S < N; ++S)
				AB[i][S] = plus(AB[i][S], (long long)A[j][S] * A[i - j][S] % mod);
	for (int i = 0; i <= bit; ++i) FWT(AB[i], -1, OR);
	for (int S = 0; S < N; ++S)
		AB[0][S] = (long long)AB[cnt[S]][S] * f[S] % mod;
	FWT(AB[0], 1, AND);

	FWT(C, 1, AND);

	FWT(DE, +1, XOR);
	for (int S = 0; S < N; ++S) DE[S] = (long long)DE[S] * DE[S] % mod;
	FWT(DE, -1, XOR);
	for (int S = 0; S < N; ++S) DE[S] = (long long)DE[S] * f[S] % mod;
	FWT(DE, +1, AND);

	for (int S = 0; S < N; ++S) ans[S] = (long long)AB[0][S] * C[S] % mod * DE[S] % mod;

	FWT(ans, -1, AND);
	int res = 0;
	for (int i = 0; i < bit; ++i) res = plus(res, ans[1 << i]);
	printf("%d", res);
	return 0;
}