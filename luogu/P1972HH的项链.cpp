#include <algorithm>
#include <cstdio>
void read(int &x) {
	x = 0;
	int c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
}
int n = 0, m = 0;
int a[1000001], last[1000001];
int ans[1000001];
struct Q {
	int l, r;
	int id;
} qu[1000001];
inline bool cmp(const Q &lhs, const Q &rhs) { return lhs.r < rhs.r; }
int tree[1000001];
inline int lowbit(int x) { return x & -x; }
inline void add(int p, int x) {
	while (p <= n) {
		tree[p] += x;
		p += lowbit(p);
	}
}
inline int query(int p) {
	int ans = 0;
	while (p) {
		ans += tree[p];
		p -= lowbit(p);
	}
	return ans;
}
int main() {
	read(n);
	for (int i = 1; i <= n; ++i)
		read(a[i]);
	read(m);
	for (int i = 1; i <= m; ++i) {
		read(qu[i].l); read(qu[i].r);
		qu[i].id = i;
	}
	std::sort(qu + 1, qu + m + 1, cmp);
	int j = 1;
	for (int i = 1; i <= m; ++i) {
		while (j <= qu[i].r) {
			if(last[a[j]]) add(last[a[j]], -1);
			add(last[a[j]] = j, 1);
			++j;
		}
		ans[qu[i].id] = query(qu[i].r) - query(qu[i].l - 1);
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
