#include <cstdio>
#include <cmath>
#include <unordered_map>
using namespace std;
typedef long long ll;
inline ll muti(ll a, ll b, ll mod) {
	ll ret = 0;
	while (b) {
		if (b & 1) {
			ret += a;
			if (ret > mod) ret -= mod;
		}
		a <<= 1;
		if (a > mod) a -= mod;
		b >>= 1;
	}
	return ret;
}
ll bsgs(ll a, ll b, ll m) {
	unordered_map<ll, ll> has;
	ll small = 1, s = ceil(sqrt(m));
	for (ll i = 1; i <= s; ++i) {
		small = muti(small, a, m);
		if (small == b) return i;
		has[muti(small, b, m)] = i;
	}
	ll Big = 1;
	for (ll i = 1; i <= s; ++i) {
		Big = muti(Big, small, m);
		if (has.find(Big) != has.end()) return i * s - has[Big];
	}
	return -1;
}
int main() {
	ll k = 0, m = 0;
	scanf("%lld %lld", &k, &m);
	k = (muti(k, 9, m) + 1) % m;
	printf("%lld", bsgs(10, k, m));
	return 0;
}