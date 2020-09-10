#include <cstdio>
typedef long long ll;
ll pow(ll x, ll b, ll mod) {
	ll ret = 1;
	while (b) {
		if (b & 1) ret = ret * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return ret;
}
struct Result {
	Result(ll D, ll X, ll Y) { d = D, x = X, y = Y; }
	ll d, x, y;
};
Result gcd(ll a, ll b) {
	if (b == 0) return Result(a, 1, 0);
	Result r = gcd(b, a % b);
	return Result(r.d, r.y, r.x - (a / b) * r.y);
}
inline ll inv(ll a, ll mod) {
	Result r = gcd(a, mod);
	return ((r.x % mod) + mod) % mod;
}

ll p = 0, pc = 0;
ll s[1000003];

void init() {
	s[0] = 1;
	for (int i = 1; i <= pc; ++i) {
		s[i] = s[i - 1];
		if (i % p != 0)
			s[i] = s[i] * i % pc;
	}
}
ll fact(ll n) {
	if (n == 0 || n == 1) return 1;
	ll loop = pow(s[pc], n / pc, pc), leave = s[n % pc];
	return fact(n / p) * loop % pc * leave % pc;
}
ll g(ll n) {
	if (n < p) return 0;
	return g(n / p) + (n / p);
}
struct Eq {
	ll b, m;
};
Eq GetBinomMod(ll n, ll m) {
	Eq e;
	e.m = pc;
	ll N = fact(n), M = inv(fact(m), pc), N_M = inv(fact(n - m), pc);
	ll pm = pow(p, g(n) - g(m) - g(n - m), pc);
	e.b = N * M % pc * N_M % pc * pm % pc;
	return e;
}
Eq res;
void Combine(Eq eq) {
	static bool first = true;
	if (first) {
		res = eq;
		first = false;
	}
	Result r = gcd(eq.m, res.m);
	r.x = (r.x % (res.m / r.d) + res.m / r.d) % (res.m / r.d);
	ll m = eq.m / r.d * res.m;
	ll x = ((r.x * (res.b - eq.b) / r.d) * eq.m % m + eq.b) % m;
	res.m = m;
	res.b = (x % m + m) % m;
}
int main() {
	ll n = 0, m = 0, mod = 0;
	scanf("%lld%lld%lld", &n, &m, &mod);
	for (ll i = 2; i * i <= mod; ++i)
		if (mod % i == 0) {
			pc = p = i;
			mod /= i;
			while (mod % i == 0) {
				pc *= i;
				mod /= i;
			}
			init();
			Eq e = GetBinomMod(n, m);
			Combine(e);
		} 
	if (mod != 1) {
		pc = p = mod;
		init();
		Eq e = GetBinomMod(n, m);
		Combine(e);
	}
	printf("%lld", res.b);
	return 0;
}