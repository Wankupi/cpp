#include <cstdio>
#include <map>
using namespace std;
typedef long long ll;
const int N = 10000000;
int n = 0, m = 0, k = 0;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int _f[2001];
inline ll f(ll x) { return (x / k) * _f[k] + _f[x % k]; }
struct Squery {
	Squery(int _X, int _C) : x(_X), c(_C) {}
	int x, c;
};
inline bool operator<(Squery const &lhs, Squery const &rhs) { return lhs.c == rhs.c ? lhs.x < rhs.x : lhs.c < rhs.c; }
int prime[N], cntPrime = 0;
int h[N + 1], mu[N + 1], smu[N + 1];
void euler() {
	mu[1] = h[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!h[i]) {
			prime[cntPrime++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < cntPrime && prime[j] * i <= N; ++j) {
			h[prime[j] * i] = true;
			if (i % prime[j])
				mu[prime[j] * i] = -mu[i];
			else
				break;
		}
	}
	for (int i = 1; i <= N; ++i)
		smu[i] = smu[i - 1] + mu[i];
}
map<Squery, ll> s;
inline ll S(int x, int c) {
	if (x == 0) return 0;
	if (c == 1 && x <= N) return smu[x];
	if (s.find(Squery(x, c)) != s.end()) return s[Squery(x, c)];
	ll r = 0;
	if (c == 1) {
		r = 1;
		for (int L = 2, R = 0; L <= x; L = R + 1) {
			R = x / (x / L);
			r -= (R - L + 1) * S(x / L, 1);
		}
	}
	else {
		for (int i = 1; i * i <= c; ++i)
			if (c % i == 0) {
				if (mu[i]) r += S(x / i, i);
				if (c / i != i && mu[c / i]) r += S(x / (c / i), c / i);
			}
	}
	return s[Squery(x, c)] = r;
}
int main() {
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= k; ++i)
		_f[i] = _f[i - 1] + (gcd(i, k) == 1);
	euler();
	ll ans = 0;
	for (int l = 1, r = 0; l <= n && l <= m; l = r + 1) {
		r = std::min(n / (n / l), m / (m / l));
		ans += (long long)(n / l) * f(m / l) * (S(r, k) - S(l - 1, k));
	}
	printf("%lld\n", ans);
	return 0;
}