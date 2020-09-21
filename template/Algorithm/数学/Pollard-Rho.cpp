#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll const prime[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
inline ll muti(ll a, ll b, ll mod) {
	//ll r = 0;
	//while (b) {
	//	if (b & 1) r = (r + a) % mod;
	//	a = (a + a) % mod;
	//	b >>= 1;
	//}
	//return r;
	return __int128(a) * __int128(b) % mod;
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
bool MRtest(ll n, ll a) {
	if (n == a) return true;
	if (pow(a, n - 1, n) != 1) return false;
	ll k = n - 1;
	while (k /= 2) {
		ll r = pow(a, k, n);
		if (r == n - 1) return true;
		if (r != 1) return false;
		if (k & 1) break;
	}
	return true;
}
inline bool MillerRabin(ll n) {
	if (n == 0 || n == 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (ll a : prime)
		if (a <= n && MRtest(n, a) == false)
			return false;
	return true;
}
ll f(ll x, ll c, ll mod) { return (muti(x, x, mod) + c) % mod; }
ll PollardRho(ll n) {
	ll s = 0, t = 0, c = rand() % (n - 1) + 1;
	for (int goal = 1; ; goal <<= 1, s = t) {
		ll val = 1;
		for (int step = 1; step <= goal; ++step) {
			t = f(t, c, n);
			val = muti(val, abs(t - s), n);
			if (step % 127 == 0) {
				ll d = gcd(val, n);
				if (d > 1) return d;
			}
		}
		ll d = gcd(val, n);
		if (d > 1) return d;
	}
}
ll MxFac = 0;
void fac(ll n) {
	// ignore 1
	if (MillerRabin(n) || n < 2) {
		if (n > MxFac) MxFac = n;
		return;
	}
	ll k = PollardRho(n);
	fac(k);
	fac(n / k);
}
int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		ll n = 0;
		scanf("%lld", &n);
		MxFac = 1;
		fac(n);
		if (MxFac == n)
			printf("Prime\n");
		else printf("%lld\n", MxFac);
	}
	return 0;
}
