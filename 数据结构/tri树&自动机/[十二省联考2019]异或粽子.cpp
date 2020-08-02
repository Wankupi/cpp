#include <algorithm>
#include <cstdio>
typedef unsigned long long ll;
const unsigned maxn = 10000003;
const int bit = 33;
inline ll read() {
	ll x = 0;
	int c = getchar();
	while (c < '0' || '9' < c) c = getchar();
	while ('0' <= c && c <= '9') x = 10 * x + c - '0', c = getchar();
	return x;
}
ll n = 0, k = 0;
ll a[500007];
ll sum[500007][bit + 1][2];
unsigned int tr[maxn][2], l[maxn], r[maxn], siz[maxn], cP = 0;
void insert(ll x, unsigned int id) {
	unsigned int p = 1;
	for (int j = bit; ~j; --j) {
		int c = (x >> j) & 1;
		if (tr[p][c] == 0) { tr[p][c] = ++cP; l[cP] = id; }
		p = tr[p][c];
		r[p] = id;
		++siz[p];
	}
}
unsigned int t[maxn];
ll QueryVal() {
	ll ans = 0;
	for (ll i = 1; i <= n; ++i) t[i] = 1;
	for (int j = bit; ~j; --j) {
		ll cnt = 0;
		unsigned int nxt = 0;
		for (ll i = 1; i <= n; ++i) cnt += siz[tr[t[i]][((a[i] >> j) & 1) ^ 1]];
		if (cnt >= k) { ans |= (1ull << j); nxt = 1; }
		else { nxt = 0; k -= cnt; }
		for (ll i = 1; i <= n; ++i) t[i] = tr[t[i]][((a[i] >> j) & 1) ^ nxt];
	}
	return ans;
}
ll qsum(ll x, unsigned int L, unsigned int R) {
	if (L == 0 || R == 0) return 0;
	ll ret = 0;
	for (int j = 0; j <= bit; ++j)
		ret += (sum[R][j][((x >> j) & 1) ^ 1] - sum[L - 1][j][((x >> j) & 1) ^ 1]) * (1ull << j);
	return ret;
}
ll QuerySum(ll Kth) {
	ll ret = k * Kth;
	//ll ret = 0;
	for (ll i = 1; i <= n; ++i) t[i] = 1;
	for (int j = bit; ~j; --j) {
		unsigned int c = (Kth >> j) & 1;
		if (c == 0)
			for (ll i = 1; i <= n; ++i)
				if (t[i])
					ret += qsum(a[i], l[tr[t[i]][(a[i] >> j & 1) ^ 1]], r[tr[t[i]][(a[i] >> j & 1) ^ 1]]);
		for (ll i = 1; i <= n; ++i) t[i] = tr[t[i]][(a[i] >> j & 1) ^ c];
	}
	return ret;
}
int main() {
	n = read();
	k = read();
	k = k * 2;
	for (unsigned int i = 1; i <= n; ++i) {
		a[i] = read();
		a[i] ^= a[i - 1];
	}
	a[++n] = 0;
	std::sort(a + 1, a + n + 1);
	cP = 1;
	l[1] = 1;
	r[1] = n;
	siz[1] = n;
	for (unsigned int i = 1; i <= n; ++i)
		insert(a[i], i);
	for (unsigned int i = 1; i <= n; ++i)
		for (int j = 0; j <= bit; ++j) {
			sum[i][j][0] = sum[i - 1][j][0];
			sum[i][j][1] = sum[i - 1][j][1];
			++sum[i][j][(a[i] >> j) & 1];
		}
	ll Kth = QueryVal();
	ll ans = QuerySum(Kth);
	ans = ans / 2;
	printf("%lld", ans);
	return 0;
}