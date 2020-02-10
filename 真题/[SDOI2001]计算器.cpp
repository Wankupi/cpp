#include <cmath>
#include <cstdio>
#include <map>
using namespace std;
typedef long long ll;

ll mod = 0;

ll pow(ll x, ll a) {
	ll ret = 1;
	while (a) {
		if (a & 1) ret = ret * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return ret;
}

struct Res {
	Res(ll _d, ll _x, ll _y) {
		d = _d;
		x = _x;
		y = _y;
	}
	ll d, x, y;
};

Res exgcd(ll a, ll b) {
	if (b == 0)
		return Res(a, 1, 0);
	Res r = exgcd(b, a % b);
	return Res(r.d, r.y, (r.x - (a / b) * r.y) % mod);
}

map<ll, ll> m;

int main() {
	int T = 0, K = 0;
	scanf("%d%d", &T, &K);
	ll y = 0, z = 0;
	if (K == 1) {
		for (int t = 1; t <= T; ++t) {
			scanf("%lld%lld%lld", &y, &z, &mod);
			printf("%lld\n", pow(y, z));
		}
	} else if (K == 2) {
		for (int t = 1; t <= T; ++t) {
			scanf("%lld%lld%lld", &y, &z, &mod);
			Res r = exgcd(y, mod);
			if (z % r.d != 0)
				printf("Orz, I cannot find x!\n");
			else {
				mod = mod / r.d;
				r.x = (r.x % mod + mod) % mod;
				r.x = r.x * (z / r.d) % mod;
				printf("%lld\n", r.x);
			}
		}
	} else {
		for (int t = 1; t <= T; ++t) {
			scanf("%lld%lld%lld", &y, &z, &mod);
			y %= mod;
			z %= mod;
			m.clear();
			if (y == 0 && z == 0) {
				printf("1\n");
				continue;
			}
			if (y == 0 && z) {
				printf("Orz, I cannot find x!\n");
				continue;
			}
			ll tem = z, bas = sqrt(double(mod)) + 1;
			for (int i = 0; i < bas; ++i) {
				m[tem] = i;
				tem = tem * y % mod;
			}
			ll b2 = pow(y, bas);
			tem = 1;
			ll ans = -1;
			for (int i = 0; i <= bas; ++i) {
				if (m.find(tem) != m.end()) {
					ans = (i * bas - m[tem]) % mod;
					if(ans >= 0) break;
				}
				tem = tem * b2 % mod;
			}
			if (ans >= 0) {
				printf("%lld\n", ans);
			} else
				printf("Orz, I cannot find x!\n");
		}
	}
	return 0;
}