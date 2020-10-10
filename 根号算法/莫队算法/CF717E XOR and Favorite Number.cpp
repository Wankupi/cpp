#include <algorithm>
#include <cmath>
#include <cstdio>
using std::sort;
int n = 0, m = 0, k = 0;
int block = 0;
int a[100001], s[100001];
int t[1048576];
struct Query {
	int id;
	int l, r;
};
inline bool operator<(const Query &lhs, const Query &rhs) {
	return lhs.l / block == rhs.l / block ? lhs.r < rhs.r : lhs.l < rhs.l;
}
Query qu[100001];
long long cnt = 0;
inline void add(int x) {
	cnt += t[x ^ k];
	++t[x];
}
inline void del(int x) {
	--t[x];
	cnt -= t[x ^ k];
}
long long ans[100001];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	block = int(sqrt(n)) + 1;
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = 1; i <= n; ++i)
		s[i] = s[i - 1] ^ a[i];
	for (int i = 1; i <= m; ++i)
		scanf("%d%d", &qu[i].l, &qu[i].r), qu[i].id = i;
	sort(qu + 1, qu + m + 1);

	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i) {
		while (r < qu[i].r)
			add(s[++r]);
		while (qu[i].l  - 1 < l)
			add(s[--l]);
		while (qu[i].r < r)
			del(s[r--]);
		while (l < qu[i].l - 1)
			del(s[l++]);
		ans[qu[i].id] = cnt;
	}
	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}