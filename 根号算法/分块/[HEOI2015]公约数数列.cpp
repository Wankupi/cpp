#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 100003;
inline long long read() {
	ll x = 0;
	int c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x;
}
inline ll min(ll a, ll b) { return a < b ? a : b; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
struct sXOR {
	sXOR(int v = 0, int p = 0) { val = v, pos = p; }
	ll val, pos;
};
int n = 0, block = 0, B = 0;
ll a[maxn];
sXOR yh[maxn];
int l[400], r[400], belong[maxn];
ll GCD[400], xOr[maxn];

void FlushBlock(int k) {
	yh[l[k]].val = a[l[k]];
	yh[l[k]].pos = l[k];
	GCD[k] = a[l[k]];
	xOr[k] = a[l[k]];
	for (int j = l[k] + 1; j <= r[k]; ++j) {
		GCD[k] = gcd(GCD[k], a[j]);
		yh[j].val = yh[j - 1].val ^ a[j];
		yh[j].pos = j;
		xOr[k] ^= a[j];
	}
	sort(yh + l[k], yh + r[k] + 1);
}
void init() {
	block = sqrt(n);
	B = (n + block - 1) / block;
	for (int i = 1; i <= block; ++i)
		belong[i] = 1;
	for (int i = block + 1; i <= n; ++i)
		belong[i] = belong[i - block] + 1;
	for (int i = 1; i <= B; ++i) {
		l[i] = block * (i - 1) + 1;
		r[i] = min(block * i, n);
		FlushBlock(i);
	}
}
inline void Change(int pos, ll x) {
	a[pos] = x;
	FlushBlock(belong[pos]);
}
int Query(ll x) {
	ll g = 0, G = 0;
	ll Xor = 0;
	for (int i = 1; i <= B; ++i) {
		G = gcd(g, GCD[i]);
		if (g == G) {
			sXOR *rs = lower_bound(yh + l[i], yh + r[i] + 1, sXOR((x / G) ^ Xor, 0));
			if (rs != yh + r[i] + 1 && rs->val == ((x / G) ^ Xor)) return rs->pos;
			Xor ^= xOr[i];
		}
		else {
			for (int j = l[i]; j <= r[i]; ++j) {
				g = gcd(g, a[j]);
				Xor ^= a[j];
				if (ll(g) * Xor == x) return j;
			}
		}
	}
	return -1;
}
char buff[10];
int main() {
	n = int(read());
	for (int i = 1; i <= n; ++i) // 题目中从0编号
		a[i] = read();
	init();
	int q = read();
	for (int i = 1; i <= q; ++i) {
		scanf("%s", buff);
		ll x = read();
		if (*buff == 'M')
			Change(x + 1, read());
		else {
			int ret = Query(x);
			if (ret == -1) puts("no");
			else printf("%d\n", ret - 1);
		}
	}
	return 0;
}

bool operator<(const sXOR &lhs, const sXOR &rhs) {
	return lhs.val == rhs.val ? lhs.pos < rhs.pos : lhs.val < rhs.val;
}