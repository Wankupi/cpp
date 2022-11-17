#include <cstdio>
#include <cmath>
using ll = long long;
int const mod = 1000000007;
int const inv3 = 333333336, inv2 = 500000004;
inline int pls(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
inline int dec(int a, int b) { return a < b ? a - b + mod : a - b; }
int const N = 1000000, maxn = N + 3;

bool com[maxn]; // is composite number
int prime[maxn], c_p = 0; // cnt_prime
int sp1[maxn], sp2[maxn];
void euler(int n) {
	com[1] = true;
	for (int i = 2; i <= n; ++i) {
		if (!com[i]) {
			prime[++c_p] = i;
			sp1[c_p] = pls(sp1[c_p - 1], i);
			sp2[c_p] = pls(sp2[c_p - 1], ll(i) * i % mod);
		}
		for (int j = 1; j <= c_p && prime[j] * i <= n; ++j) {
			com[prime[j] * i] = true;
			if (i % prime[j] == 0) break;
		}
	}
}
ll n = 0;
int sqrtn = 0;
int id1[maxn], id2[maxn];
ll w[maxn], tot = 0;
int g1[maxn], g2[maxn];
void init(ll n) {
	sqrtn = std::sqrt(n);
	euler(sqrtn);
	for (ll l = 1, r = 0; l <= n; l = r + 1) {
		w[++tot] = n / l;
		r = n / w[tot];
		// do not use w[tot]*w[tot]<=n
		// it will exceed long long
		if (w[tot] <= sqrtn) id1[w[tot]] = tot;
		else id2[n / w[tot]] = tot;
	}
	// get g(x,0)
	for (int i = 1; i <= tot; ++i) {
		g1[i] = w[i] % mod * (w[i] % mod + 1) % mod * inv2 % mod;
		g2[i] = w[i] % mod * (w[i] % mod + 1) % mod * inv2 % mod * (2 * w[i] % mod + 1) % mod * inv3 % mod;
		g1[i] = dec(g1[i], 1); // 减去x=1
		g2[i] = dec(g2[i], 1);
	}
	// get g(x, inf)
	for (int j = 1; j <= c_p; ++j) {
		for (int i = 1; i <= tot && ll(prime[j]) * prime[j] <= w[i]; ++i) {
			int k = w[i] / prime[j] <= sqrtn ? id1[w[i] / prime[j]] : id2[n / (w[i] / prime[j])];
			// k must > i, because w is descending.
			g1[i] = dec(g1[i], ll(prime[j]) * dec(g1[k], sp1[j - 1]) % mod);
			g2[i] = dec(g2[i], ll(prime[j]) * prime[j] % mod * dec(g2[k], sp2[j - 1]) % mod);
		}
	}

}

ll S(ll x, int y) {
	if (prime[y] >= x) return 0;
	int k = x <= sqrtn ? id1[x] : id2[n / x];
	ll ans = dec(dec(g2[k], g1[k]), dec(sp2[y], sp1[y]));
	for (int i = y + 1; i <= c_p && ll(prime[i]) * prime[i] <= x; ++i) {
		ll pe = prime[i];
		for (int e = 1; pe <= x; ++e, pe *= prime[i]) {
			ll f_at_pe = pe % mod * (pe % mod - 1) % mod;
			ans = pls(ans, f_at_pe * (S(x / pe, i) + (e != 1)) % mod);
		}
	}
	return ans;
}

int main() {
	scanf("%lld", &n);
	init(n);
	printf("%lld\n", pls(S(n, 0), 1));
	return 0;
}
