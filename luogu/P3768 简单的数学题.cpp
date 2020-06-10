#include <cstdio>
#include <map>
using namespace std;
typedef long long ll;
ll mod = 0;
ll mpow(ll x, ll a) {
	ll ret = 1;
	while (a) {
		if (a & 1) ret = ret * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return ret;
}
const int maxn = 8000000;
int N = 0;
int prime[maxn], c = 0;
bool h[maxn + 3];
ll phi[maxn + 3];
ll F[maxn + 3];
void init(ll n) {
	N = (maxn < n ? maxn : n);
	h[1] = true;
	phi[1] = 1;
	F[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!h[i]) {
			prime[c++] = i;
			phi[i] = i - 1;
		}
		for (int j = 0; j < c && prime[j] * i <= N; ++j) {
			h[prime[j] * i] = true;
			if (i % prime[j])
				phi[prime[j] * i] = phi[prime[j]] * phi[i];
			else {
				phi[prime[j] * i] = prime[j] * phi[i];
				break;
			}
		}
		F[i] = (F[i - 1] + phi[i] * i % mod * i % mod) % mod;
	}
}

ll inv2 = 0, inv6 = 0;

inline ll s1(ll n) {
	n %= mod;
	return inv2 * n % mod * (n + 1) % mod;
}
inline ll s2(ll n) {
	n %= mod;
	return inv6 * n % mod * (n + 1) % mod * (2 * n + 1) % mod;
}
inline ll s3(ll n) {
	return s1(n) * s1(n) % mod;
}
map<ll, ll> Sign;
ll djs(ll n) {
	if (n <= N) return F[n];
	if (Sign.find(n) != Sign.end()) return Sign[n];
	ll ret = s3(n);
	for (ll l = 2, r = 0; l <= n; l = r + 1) {
		r = n / (n / l);
		ret = (ret - (s2(r) - s2(l - 1)) % mod * djs(n / l) % mod) % mod;
	}
	if (ret < 0) ret += mod;
	Sign[n] = ret;
	return ret;
}
int cnt = 0;
int main() {
	ll n = 0;
	scanf("%lld%lld", &mod, &n);
	init(n);
	inv2 = mpow(2, mod - 2);
	inv6 = mpow(6, mod - 2);
	ll ans = 0;
	for (ll l = 1, r = 0; l <= n; l = r + 1) {
		r = n / (n / l);
		ll A = (djs(r) - djs(l - 1) + mod) % mod;
		ans += A * s3(n / l) % mod;
		ans %= mod;
	}
	printf("%lld", ans);
	return 0;
}