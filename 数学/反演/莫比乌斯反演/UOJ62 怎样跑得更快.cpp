#include <cstdio>
typedef long long ll;
const ll mod = 998244353;
const int maxn = 100003;
int read() {
	int x = 0; int c = getchar();
	while (c < '0' || c>'9')c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x;
}
int n = 0, q = 0;
ll c = 0, d = 0;
ll b[maxn], x[maxn];
int prime[maxn], cnt = 0, mu[maxn];
bool h[maxn];
ll A[maxn], B[maxn], iA[maxn], iB[maxn];
void euler() {
	h[1] = mu[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!h[i]) {
			prime[cnt++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < cnt && prime[j] * i <= n; ++j) {
			h[prime[j] * i] = true;
			if (i % prime[j])
				mu[prime[j] * i] = -mu[i];
			else break;
		}
	}
}
inline ll pow(ll x, ll b) {
	ll ret = 1;
	while (b) {
		if (b & 1) ret = ret * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return ret;
}
void init() {
	euler();
	for (int i = 1; i <= n; ++i) {
		A[i] = pow(i, c - d >= 0 ? c - d : c - d + mod - 1);
		B[i] = pow(i, d);
		iB[i] = pow(B[i], mod - 2);
	}
	for (int d = 1; d <= n; ++d) {
		for (int T = d; T <= n; T += d)
			iA[T] = (iA[T] + A[d] * mu[T / d] % mod + mod) % mod;
		A[d] = pow(iA[d], mod - 2);
	}
}
ll C[maxn];
bool solve() {
	for (int i = 1; i <= n; ++i) x[i] = C[i] = 0;
	for (int i = 1; i <= n; ++i)
		for (int T = i; T <= n; T += i)
			C[T] = (C[T] + mu[T / i] * b[i] % mod * iB[i] % mod + mod) % mod;
	for (int i = 1; i <= n; ++i) {
		if (A[i] == 0 && C[i] != 0) return false;
		C[i] = C[i] * A[i] % mod;
	}
	for (int i = 1; i <= n; ++i) {
		for (int T = i; T <= n; T += i)
			x[i] = (x[i] + mu[T / i] * C[T] % mod + mod) % mod;
	}
	for (int i = 1; i <= n; ++i)
		x[i] = x[i] * iB[i] % mod;
	return true;
}
int main() {
	n = read(); c = read(); d = read(); q = read();
	init();
	for (int t = 1; t <= q; ++t) {
		for (int i = 1; i <= n; ++i) b[i] = read();
		if (solve()) {
			for (int i = 1; i <= n; ++i) printf("%lld ", x[i]);
			putchar('\n');
		}
		else printf("-1\n");
	}
	return 0;
}