#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline ll pls(ll a, ll b, ll p) { return a + b < p ? a + b : a + b - p; }
inline ll dec(ll a, ll b, ll p) { return a >= b ? a - b : a - b + p; }
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || '9' < c) c = getchar();
	while ('0' <= c && c <= '9') x = 10 * x + c - '0', c = getchar();
	return x;
}
int const maxn = 100003, BLOCK = 350;
int n = 0, m = 0;
int a[maxn], t[maxn];
struct Query {
	int l, r, mod;
	int id;
};
inline bool operator<(Query const &lhs, Query const &rhs) {
	return (lhs.l / BLOCK) == (rhs.l / BLOCK) ? (((lhs.l / BLOCK) & 1) ? lhs.r < rhs.r : lhs.r > rhs.r) : lhs.l < rhs.l;
}
Query q[maxn];
int id[maxn], V[BLOCK], cId = 0;
int c[maxn], sT[BLOCK][maxn]; // 颜色的前缀出现次数
ll sum[BLOCK + 5], mi[BLOCK + 3], Mi[BLOCK + 3];
inline ll Pow(int t, int mod) { return Mi[t / BLOCK] * mi[t % BLOCK] % mod; }
void add(int x) {
	if (t[x] >= BLOCK) return;
	sum[c[x]++] -= x;
	sum[c[x]] += x;
}
void del(int x) {
	if (t[x] >= BLOCK) return;
	sum[c[x]--] -= x;
	sum[c[x]] += x;
}
ll ans[maxn];
int main() {
	n = read(); m = read();
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
		++t[a[i]];
	}
	for (int i = 1; i <= 100000; ++i)
		if (t[i] >= BLOCK) V[id[i] = cId++] = i;
		else id[i] = -1; // 如果错误访问会RE
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < cId; ++j) sT[j][i] = sT[j][i - 1];
		if (t[a[i]] >= BLOCK) ++sT[id[a[i]]][i];
		sum[0] += a[i];
	}
	for (int i = 1; i <= m; ++i) { q[i].l = read(); q[i].r = read(); q[i].mod = read(); q[i].id = i; }
	sort(q + 1, q + m + 1);
	int ql = 1, qr = 0;
	for (int i = 1; i <= m; ++i) {
		while (qr < q[i].r) add(a[++qr]);
		while (q[i].l < ql) add(a[--ql]);
		while (q[i].r < qr) del(a[qr--]);
		while (ql < q[i].l) del(a[ql++]);
		mi[0] = 1;
		for (int j = 1; j <= BLOCK; ++j) mi[j] = mi[j - 1] * 2 % q[i].mod;
		Mi[0] = 1;
		for (int j = 1; j <= BLOCK; ++j) Mi[j] = Mi[j - 1] * mi[BLOCK] % q[i].mod;

		ll &Ans = ans[q[i].id];
		int len = q[i].r - q[i].l + 1;
		for (int j = 1; j < BLOCK && j <= len; ++j) {
			Ans = pls(Ans, dec(Pow(len, q[i].mod), Pow(len - j, q[i].mod), q[i].mod) * sum[j] % q[i].mod, q[i].mod);
		}
		for (int j = 0; j < cId; ++j) {
			int k = sT[j][q[i].r] - sT[j][q[i].l - 1];
			Ans = pls(Ans, dec(Pow(len, q[i].mod), Pow(len - k, q[i].mod), q[i].mod) * V[j] % q[i].mod, q[i].mod);
		}
	}
	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}