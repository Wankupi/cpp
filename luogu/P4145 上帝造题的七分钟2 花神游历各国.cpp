#include <cmath>
#include <cstdio>
typedef long long ll;
inline int lowbit(int x) { return x & -x; }
int n = 0, m = 0;
ll a[100003], s[100003], tree[100003];
inline void add(int p, ll v) { while (p <= n) { tree[p] += v; p += lowbit(p); } }
inline ll query(int p) {
	ll sum = 0;
	while (p) { sum += tree[p]; p -= lowbit(p); }
	return sum;
}
int fa[100003];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int main() {
	freopen("P4145_5.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", a + i);
		s[i] = a[i] + s[i - 1];
		tree[i] = s[i] - s[i - lowbit(i)];
		fa[i] = i;
		if (a[i] == 1) fa[i] = i + 1;
	}
	fa[n + 1] = n + 1;
	scanf("%d", &m);
	int opt = 0, l = 0, r = 0;
	for (int t = 1; t <= m; ++t) {
		scanf("%d%d%d", &opt, &l, &r);
		if (l > r) l ^= r ^= l ^= r;
		if (opt == 0) {
			while (l <= r) {
				if (a[l] != 1) {
					ll tem = sqrt(a[l]);
					add(l, tem - a[l]);
					a[l] = tem;
					if (a[l] == 1)
						fa[l] = find(l + 1);
				}
				if (a[l] == 1) l = find(l);
				else ++l;
			}
		}
		else
			printf("%lld\n", query(r) - query(l - 1));
	}
	return 0;
}