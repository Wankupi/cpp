#include <cstdio>
#include <cmath>
#include <algorithm>
void read(int &x) {
	x = 0; int c = getchar();
	while (c < '0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
}
const int maxn = 50001;
int n = 0, q = 0, k = 0, block = 0;
int a[maxn], cnt[maxn], ans = 0;
int result[maxn];
struct Query {
	int l, r, id;
} qu[maxn];
inline bool operator<(const Query &L, const Query &R) {
	return L.l / block == R.l / block ? L.r < R.r : L.l < R.l;
}
inline void add(int x) {
	ans += cnt[x] * 2 + 1;
	++cnt[x];
}
inline void inadd(int x) {
	ans -= cnt[x] * 2 - 1;
	--cnt[x];
}
int main() {
	read(n); read(q); read(k);
	block = sqrt(n);
	for (int i = 1; i <= n; ++i)
		read(a[i]);
	for (int i = 1; i <= q; ++i) {
		read(qu[i].l); read(qu[i].r);
		qu[i].id = i;
	}
	std::sort(qu + 1, qu + q + 1);
	int l = 1, r = 0;
	for (int i = 1; i <= q; ++i) {
		while (l > qu[i].l) add(a[--l]);
		while (r < qu[i].r) add(a[++r]);
		while (l < qu[i].l)
			inadd(a[l++]);
		while (r > qu[i].r)
			inadd(a[r--]);
		result[qu[i].id] = ans;
	}
	for (int i = 1; i <= q; ++i)
		printf("%d\n", result[i]);
	return 0;
}