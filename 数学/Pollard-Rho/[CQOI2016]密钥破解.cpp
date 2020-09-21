#include <algorithm>
#include <cstdio>
#include <cstdlib>
typedef long long ll;
inline ll muti(ll a, ll b, ll mod) {
	ll r = 0;
	while (b) {
		if (b & 1) r = (r + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return r;
}
inline ll pow(ll x, ll b, ll mod) {
	ll r = 1;
	while (b) {
		if (b & 1) r = muti(r, x, mod);
		x = muti(x, x, mod);
		b >>= 1;
	}
	return r;
}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll f(ll x, ll c, ll mod) { return (muti(x, x, mod) + c) % mod; }
ll PollardRho(ll n) {
	ll c = rand() % (n - 1) + 1;
	ll t = f(0, c, n), r = f(f(0, c, n), c, n);
	while (t != r) {
		ll d = gcd(std::abs(t - r), n);
		if (d > 1) return d;
		t = f(t, c, n);
		r = f(f(r, c, n), c, n);
	}
	return n;
}
struct Res {
	Res(ll D, ll X, ll Y) : d(D), x(X), y(Y) {}
	ll d, x, y;
};
Res exgcd(ll a, ll b) {
	if (b == 0) return Res(a, 1, 0);
	Res r = exgcd(b, a % b);
	return Res(r.d, r.y, (r.x - muti(r.y, (a / b), a / r.d)) % (a / r.d));
}
int main() {
	ll e = 0, N = 0, c = 0;
	scanf("%lld %lld %lld", &e, &N, &c);
	ll p = PollardRho(N);
	ll q = N / p;
	ll r = (p - 1) * (q - 1);
	Res res = exgcd(e, r);
	ll d = (res.x % (r / res.d) + (r / res.d)) % (r / res.d);
	ll n = pow(c, d, N);
	printf("%lld %lld", d, n);
	return 0;
}