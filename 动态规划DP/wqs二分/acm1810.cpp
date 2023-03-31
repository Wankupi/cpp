#include <cstdio>
#include <cstring>
using ll = long long;
int const maxn = 100003;

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }

int n = 0, k = 0;
int a[maxn];

int t[maxn], ql = 1, qr = 0;
ll total = 0;

ll f[maxn];
int turn[maxn];

ll extra_cost = 0;


void clear() {
	memset(f, 0x3f, sizeof(ll) * (n + 1));
	f[0] = 0;
}

void checkout(int l, int r) {
	while (qr < r) total += t[a[++qr]]++;
	while (ql > l) total += t[a[--ql]]++;
	while (qr > r) total -= --t[a[qr--]];
	while (ql < l) total -= --t[a[ql++]];
}

int get_trans_pos(int p, int l, int r) {
	checkout(l, p);
	ll minV = f[l - 1] + total + extra_cost;
	int pos = l;
	for (int i = l + 1; i <= r; ++i) {
		checkout(i, p);
		ll v = f[i - 1] + total + extra_cost;
		if (v < minV) {
			minV = v;
			pos = i;
		}
	}
	if (minV < f[p]) {
		f[p] = minV;
		turn[p] = turn[pos - 1] + 1;
	}
	return pos;
}

void trans(int L, int R, int l, int r) {
	if (L > R) return;
	int mid = (L + R) >> 1;
	int p = get_trans_pos(mid, l, r);
	trans(L, mid - 1, l, p);
	trans(mid + 1, R, p, r);
}

void cdq(int L, int R) {
	if (L == R) {
		trans(L, L, L, L);
		return;
	}
	int mid = (L + R) >> 1;
	cdq(L, mid);
	trans(mid + 1, R, L, mid);
	cdq(mid + 1, R);
}

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);

	ll L = -10000000000, R = 10000000000;
	while (L <= R) {
		extra_cost = (L + R) / 2;
		clear();
		cdq(1, n);
		if (turn[n] > k) L = extra_cost + 1;
		else R = extra_cost - 1;
	}
	extra_cost = R + 1;
	clear();
	cdq(1, n);
	ll ans = f[n] - k * extra_cost;
	printf("%lld\n", ans);
	return 0;
}
