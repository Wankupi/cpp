#include <cstdio>
typedef long long ll;
const ll inf = 0x7fffffffffffffff;
int m = 0, N = 0;
ll d = 0, tree[200000];
inline ll max(ll a, ll b) { return a < b ? b : a; }
inline int lowbit(int x) { return x & -x; }
void set(int p, ll x) {
	while (p) {
		tree[p] = max(tree[p], x);
		p -= lowbit(p);
	}
}
ll query(int p) {
	ll ret = -inf;
	while (p <= N) {
		ret = max(ret, tree[p]);
		p += lowbit(p);
	}
	return ret;
}
int main() {
	scanf("%d%lld", &m, &d);
	ll opt = 0, x = 0, lastAns = 0;
	for (int i = 1; i <= m; ++i) {
		do { opt = getchar(); } while (opt != 'Q' && opt != 'A');
		scanf("%lld", &x);
		if (opt == 'A')	set(++N, (lastAns + x) % d);
		else			printf("%lld\n", lastAns = query(N - x + 1));
	}
	return 0;
}