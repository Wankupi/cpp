#include <cstdio>
typedef long long ll;
ll const mod = 998244353;
int n = 0, N = 0;
ll A[1 << 17], B[1 << 17], C[1 << 17];
ll dA[1 << 17], dB[1 << 17];
ll dC[1 << 17];
void OR(ll *f, ll *a, ll opt) {
	for (int i = 0; i < N; ++i)
		f[i] = a[i];
	for (int len = 1; len < N; len <<= 1)
		for (int i = 0; i < N; i += (len << 1))
			for (int j = 0; j < len; ++j)
				(f[i + len + j] += f[i + j] * opt) %= mod;
}

void AND(ll *f, ll *a, ll opt) {
	for (int i = 0; i < N; ++i)
		f[i] = a[i];
	for (int len = 1; len < N; len <<= 1)
		for (int i = 0; i < N; i += (len << 1))
			for (int j = 0; j < len; ++j)
				(f[i + j] += f[i + len + j] * opt) %= mod;
}

void XOR(ll *f, ll *a, ll opt) {
	for (int i = 0; i < N; ++i)
		f[i] = a[i];
	for (int len = 1; len < N; len <<= 1)
		for (int i = 0; i < N; i += (len << 1))
			for (int j = 0; j < len; ++j) {
				f[i + j] = (f[i + j] + f[i + len + j]) % mod;
				f[i + len + j] = (f[i + j] - 2 * f[i + len + j]) % mod;
				f[i + j] = f[i + j] * opt % mod;
				f[i + len + j] = f[i + len + j] * opt % mod;
			}
}
int main() {
	scanf("%d", &n);
	N = 1 << n;
	for (int i = 0; i < N; ++i)
		scanf("%lld", A + i);
	for (int i = 0; i < N; ++i)
		scanf("%lld", B + i);
	// 499122177;
	OR(dA, A, 1);
	OR(dB, B, 1);
	for (int i = 0; i < N; ++i)
		dC[i] = dA[i] * dB[i] % mod;
	OR(C, dC, -1);
	for (int i = 0; i < N; ++i)
		printf("%lld ", (C[i] + mod) % mod);
	printf("\n");

	AND(dA, A, 1);
	AND(dB, B, 1);
	for (int i = 0; i < N; ++i)
		dC[i] = dA[i] * dB[i] % mod;
	AND(C, dC, -1);
	for (int i = 0; i < N; ++i)
		printf("%lld ", (C[i] + mod) % mod);
	printf("\n");

	XOR(dA, A, 1);
	XOR(dB, B, 1);
	for (int i = 0; i < N; ++i)
		dC[i] = dA[i] * dB[i] % mod;
	XOR(C, dC, 499122177);
	for (int i = 0; i < N; ++i)
		printf("%lld ", (C[i] + mod) % mod);
	printf("\n");
	return 0;
}