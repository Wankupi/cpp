#include <cstdio>

typedef long long ll;
const int maxn = 10000000;
bool h[maxn + 1];
int phi[maxn + 1], prime[maxn], c = 0;
void ouler() {
	phi[1] = 1;
	h[1] = true;
	for (int i = 2; i <= maxn; ++i) {
		if (!h[i]) {
			prime[c++] = i;
			phi[i] = i - 1;
		}
		for (int j = 0; j != c && prime[j] * i <= maxn; ++j) {
			h[prime[j] * i] = true;
			if (i % prime[j])
				phi[prime[j] * i] = phi[prime[j]] * phi[i];
			else {
				phi[prime[j] * i] = phi[i] * prime[j];
				break;
			}
		}
	}
}
ll pow(ll x, ll a, ll mod) {
	ll ret = 1;
	while (a) {
		if (a & 1) ret = ret * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return ret;
}
ll query(ll p) {
	if (p == 1) return 0;
	return pow(2, query(phi[p]) + phi[p], p);
}
int main() {
	ouler();
	int T = 0, n = 0;
	scanf("%d", &T);
	for (int i = 1; i <= T; ++i) {
		scanf("%d", &n);
		printf("%lld\n", query(n));
	}
	return 0;
}