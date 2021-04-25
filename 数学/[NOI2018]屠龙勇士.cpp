#include <cstdio>
#include <set>
using namespace std;
typedef long long ll;
typedef multiset<ll>::iterator Ptr;
int const maxn = 100003;
inline ll max(ll a, ll b) { return a < b ? b : a; }

int n = 0, m = 0;
ll a[maxn], p[maxn], rw[maxn];
ll c[maxn];
multiset<ll> sw;

struct Eq {
	Eq(ll A, ll M) :a(A), m(M) {}
	ll a, m;
};

inline ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
struct Result {
	Result(ll _d, ll _x, ll _y) :d(_d), x(_x), y(_y) {}
	ll d, x, y;
};
inline Result exgcd(ll a, ll b) {
	if (b == 0) return Result(a, 1, 0);
	Result r = exgcd(b, a % b);
	return Result(r.d, r.y, r.x - (a / b) * r.y);
}

ll getInv(ll a, ll m) { // (a, m) = 1
	Result r = exgcd(a, m);
	return (r.x % m + m) % m;
}

Eq make_Eq(ll a, ll b, ll m) {
	b = (b % m + m) % m;
	ll d = gcd(a, m);
	if (d != 1) {
		if (b % d != 0)
			throw -1;
		a /= d; b /= d; m /= d;
	}
	d = getInv(a, m);
	b = __int128_t(b) * d % m;
	return Eq(b, m);
}
Eq operator+(Eq const &A, Eq const &B) {
	ll b = B.a - A.a;
	Eq e = make_Eq(A.m, b, B.m);
	ll M = A.m * e.m;
	ll a = ((A.a + __int128_t(e.a) * A.m) % M + M) % M;
	return Eq(a, M);
}

int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		ll x = 0;
		bool all1 = true;
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		for (int i = 1; i <= n; ++i) { scanf("%lld", p + i); all1 = (all1 && p[i] == 1); }
		for (int i = 1; i <= n; ++i) scanf("%lld", rw + i);
		for (int i = 1; i <= m; ++i) {
			scanf("%lld", &x);
			sw.insert(x);
		}
		for (int i = 1; i <= n; ++i) {
			Ptr _A = sw.upper_bound(a[i]);
			if (_A != sw.begin()) --_A;
			c[i] = *_A;
			sw.erase(_A);
			sw.insert(rw[i]);
		}
		sw.clear();
		if (all1) {
			ll ans = 0;
			for (int i = 1; i <= n; ++i)
				ans = max(ans, (a[i] + c[i] - 1) / c[i]);
			printf("%lld\n", ans);
		}
		else {
			try {
				Eq ans(0, 0);
				for (int i = 1; i <= n; ++i) {
					Eq cur = make_Eq(c[i], a[i], p[i]);
					if (i == 1) ans = cur;
					else ans = ans + cur;	
				}
				printf("%lld\n", ans.a == 0 ? ans.m : ans.a);
			}
			catch(...) {
				printf("-1\n");
			}
		}
	}
	return 0;
}
// int128 is fragrant
