#include <cmath>
#include <cstdio>
#include <map>
using namespace std;
typedef long long ll;
struct Result {
	Result(ll D, ll X, ll Y) { d = D, x = X, y = Y; }
	ll d, x, y;
};
inline Result gcd(ll a, ll b) {
	if (b == 0) return Result(a, 1, 0);
	Result r = gcd(b, a % b);
	return Result(r.d, r.y, r.x - (a / b) * r.y);
}

inline ll Inv(ll x, ll m) {
	ll inv = gcd(x, m).x;
	inv = (inv % m + m) % m;
	return inv;
}
ll A[50000], B[50000];
ll bsgs(ll a, ll b, ll m) {
	ll s = ceil(sqrt(m));
	A[0] = 1;
	map<ll, ll> has;
	for (ll i = 1; i <= s; ++i) {
		A[i] = A[i - 1] * a % m;
		if (A[i] == b) return i;
		has[A[i]] = i;
	}
	ll invs = Inv(A[s], m);
	B[0] = b;
	for (ll i = 1; i <= s; ++i) {
		B[i] = B[i - 1] * invs % m;
		if (has.find(B[i]) != has.end())
			return has[B[i]] + s * i;
	}
	return -1;
}
ll exbsgs(ll a, ll b, ll m) {
	if (m == 1 || b == 1) return 0;
	ll g = 0, k = 0, da = 1;
	while ((g = gcd(a, m).d) > 1) {
		if (b % g != 0) return -1;
		++k;
		b /= g;
		m /= g;
		da = da * a / g % m;
		if (da == b) return k;
	}
	ll res = bsgs(a, b * Inv(da, m) % m, m);
	return res < 0 ? -1 : res + k;
}

int main() {
	ll a = 0, p = 0, b = 0;
	while (scanf("%lld %lld %lld", &a, &p, &b) != EOF) {
		if (a == 0 && p == 0 && b == 0) break;
		a %= p; b %= p;
		ll x = exbsgs(a, b, p);
		if (x < 0)
			printf("No Solution\n");
		else
			printf("%lld\n", x);
	}
	return 0;
}