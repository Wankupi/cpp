#include <algorithm>
#include <cstdio>
typedef long long ll;
const int maxn = 100003, bit = 31;
const ll mod = 1000000007;
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || '9' < c)
		c = getchar();
	while ('0' <= c && c <= '9')
		x = 10 * x + c - '0', c = getchar();
	return x;
}
int n = 0;
int a[maxn];
int sum[maxn][32][2];
int tr[maxn][2], l[maxn], r[maxn], siz[maxn], cP = 0;
void insert(int x, int id) {
	int p = 1;
	for (int j = bit; ~j; --j) {
		int c = (x >> j) & 1;
		if (tr[p][c] == 0) {
			tr[p][c] = ++cP;
			l[cP] = id;
		}
		p = tr[p][c];
		r[p] = id;
		++siz[p];
	}
}
int t[maxn];
ll k = 0;
ll QueryVal() {
	ll ans = 0;
	for (int i = 1; i <= n; ++i) t[i] = 1;
	for (int j = bit; ~j; --j) {
		ll cnt = 0;
		int nxt = 0;
		for (int i = 1; i <= n; ++i)
			cnt += siz[tr[t[i]][((a[i] >> j) & 1) ^ 1]];
		if (cnt >= k) {
			ans |= (1ll << j);
			nxt = 1;
		}
		else {
			nxt = 0;
			k -= cnt;
		}
		for (int i = 1; i <= n; ++i)
			t[i] = tr[t[i]][((a[i] >> j) & 1) ^ nxt];
	}
	return ans;
}
ll qsum(int x, int L, int R) {
	if (L == 0 || R == 0) return 0;
	ll ret = 0;
	for (int j = 0; j <= bit; ++j)
		ret = (ret + ((long long)sum[R][j][((x >> j) & 1) ^ 1] - sum[L - 1][j][((x >> j) & 1) ^ 1]) *
			((1ll << j) % mod) % mod) % mod;
	return ret;
}
ll QuerySum(ll Kth) {
	ll ret = k * Kth % mod;
	for (int i = 1; i <= n; ++i) t[i] = 1;
	for (int j = bit; ~j; --j) {
		int c = (Kth >> j) & 1;
		if (c == 0)
			for (int i = 1; i <= n; ++i)
				ret = (ret + qsum(a[i], l[tr[t[i]][(a[i] >> j & 1) ^ 1]], r[tr[t[i]][(a[i] >> j & 1) ^ 1]])) % mod;
		for (int i = 1; i <= n; ++i)
			t[i] = tr[t[i]][(a[i] >> j & 1) ^ c];
	}
	return ret;
}
int main() {
	n = read();
	k = read();
	k = k * 2;
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	std::sort(a + 1, a + n + 1);
	cP = 1;
	l[1] = 1;
	r[1] = n;
	siz[1] = n;
	for (int i = 1; i <= n; ++i)
		insert(a[i], i);
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= bit; ++j) {
			sum[i][j][0] = sum[i - 1][j][0];
			sum[i][j][1] = sum[i - 1][j][1];
			++sum[i][j][(a[i] >> j) & 1];
		}
	ll Kth = QueryVal();
	ll ans = QuerySum(Kth);
	ans = ans * 500000004 % mod;
	printf("%lld", ans);
	return 0;
}