#include <cstdio>
typedef long long ll;
const ll mod = 1000000007;
ll pow(ll x, ll b) {
	ll ret = 1;
	while (b) {
		if (b & 1) ret = ret * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return ret;
}
int k = 0;
ll pa = 0, pb = 0;
ll f[1003][1003];
int main() {
	scanf("%d %lld %lld", &k, &pa, &pb);
	ll sum = pow((pa + pb) % mod, mod - 2);
	pa = pa * sum % mod;
	pb = pb * sum % mod;
	ll invB = pow(pb, mod - 2);
	ll X = pa * invB % mod;
	for (int i = k; i >= 1; --i) {
		for (int j = k; j >= 0; --j) {
			f[i][j] = i + j >= k ? (i + j + X) % mod : (f[i + 1][j] * pa % mod + f[i][j + i] * pb % mod) % mod;
		}
	}
	printf("%lld", f[1][0]);
	return 0;
}