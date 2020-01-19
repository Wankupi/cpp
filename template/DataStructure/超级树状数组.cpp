#include <cstdio>
#include <cctype>
void read(int &x) {
	char c = getchar(); bool f = false; x = 0;
	while (!isdigit(c)) { if (c == '-') f = true; c = getchar(); }
	while (isdigit(c)) { x = (x << 1) + (x << 3) + c - '0'; c = getchar(); }
	if (f) x = -x;
}
const int N = 100000;
typedef long long ll;
inline int lowbit(int x) { return x & -x; }
class TreeArrey {
public:
	void add(int p, ll x) { while (p <= N) { tree[p] += x; p += lowbit(p); } }
	ll query(int p) { ll ret = 0; while (p) { ret += tree[p]; p -= lowbit(p); }return ret; }
	ll query(int l, int r) { return query(r) - query(l - 1); }
	ll tree[N + 1];
};
TreeArrey b, bi;
inline void add(int l, int r, ll x) {
	b.add(l, x);		b.add(r + 1, -x);
	bi.add(l, x * l);	bi.add(r + 1, -x * (r + 1));
}
inline ll query(int p) { return (p + 1) * b.query(p) - bi.query(p); }
inline ll query(int l, int r) { return query(r) - query(l - 1); }
int n = 0, m = 0, a[N + 1], sum[N + 1];
int main() {
	read(n); read(m);
	for (int i = 1; i <= n; ++i)
		read(a[i]);
	for (int i = 1; i <= n; ++i)
		sum[i] = sum[i - 1] + a[i];
	int l = 0, r = 0, v = 0;
	char opt = 0;
	for (int i = 1; i <= m; ++i) {
		do opt = getchar(); while (opt != '1' && opt != '2');
		read(l); read(r);
		if (opt == '1') { read(v); add(l, r, v); }
		else printf("%lld\n", sum[r] - sum[l - 1] + query(l, r));
	}
	return 0;
}