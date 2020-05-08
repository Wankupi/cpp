#include <cstdio>
typedef long long ll;
const int maxn = 1000003;
const ll mod = 1000000007;
ll fac[maxn], inv[maxn];
ll f[maxn];
ll row(ll x, ll a) {
	ll ret = 1;
	while (a) {
		if (a & 1) ret = ret * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return ret;
}
int T = 0, n[500003], m[500003];
int Nm = 0;
void init() {
	fac[0] = 1;
	for (int i = 1; i <= Nm; ++i)
		fac[i] = fac[i - 1] * i % mod;
	inv[Nm] = row(fac[Nm], mod - 2);
	for (int i = Nm - 1; i >= 0; --i)
		inv[i] = inv[i + 1] * (i + 1) % mod;
	f[0] = 1; f[1] = 0; f[2] = 1;
	for (int i = 3; i <= Nm; ++i)
		f[i] = (i - 1) * (f[i - 1] + f[i - 2]) % mod;
}
inline ll C(int a, int b) { return fac[a] * inv[b] % mod * inv[a - b] % mod; }
int main() {
	scanf("%d", &T);
	for (int i = 1; i <= T; ++i) {
		scanf("%d%d", n + i, m + i);
		if (n[i] > Nm) Nm = n[i];
	}
	init();
	for (int i = 1; i <= T; ++i)
		printf("%lld\n", C(n[i], m[i]) * f[n[i] - m[i]] % mod);
	return 0;
}