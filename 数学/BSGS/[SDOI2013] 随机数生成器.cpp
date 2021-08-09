#include <cstdio>
#include <unordered_map>
#include <cmath>

typedef long long ll;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
ll pow(ll x, ll b, ll const mod) {
	ll r = 1;
	while (b) {
		if (b & 1) r = r * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return r;
}
inline ll inv(ll x, ll mod) { return pow(x, mod - 2, mod); }

ll bsgs(ll a, ll b, ll mod) {
	std::unordered_map<ll, int> um;
	int B = int(sqrt(mod));
	ll v = 1;
	for (int i = 0; i < B; ++i) {
		if (b == v)
			return i;
		if (um.find(v) != um.end()) return -2;
		um[v] = i;
		v = v * a % mod;
	}
	ll base = inv(v, mod);
	v = base;
	for (int i = 1; i <= B; ++i) {
		auto p = um.find(v * b % mod);
		if (p != um.end())
			return i * B + p->second;
		v = v * base % mod;
	}
	return -2;
}

int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		ll p = 0, a = 0, b = 0, x = 0, t = 0;
		scanf("%lld %lld %lld %lld %lld", &p, &a, &b, &x, &t);
		if (x == t) printf("1\n");
		else if (a == 0)
			printf("%d\n", (b == t ? 2 : -1));
		else if (a == 1) {
			ll k = ((t - x) % p + p) % p;
			ll d = gcd(b, p);
			if (k % d != 0) printf("-1\n");
			else {
				ll ans = (k * inv(b, p) + 1) % p;
				printf("%lld\n", ans == 0 ? p : ans);
			}
		}
		else {
			ll k = (t + b * inv(a - 1, p) % p) % p * inv((x + b * inv(a - 1, p) % p) % p, p) % p;
			ll ans = bsgs(a, k, p) + 1;
			printf("%lld\n", ans);
		}
	}
	return 0;
}
