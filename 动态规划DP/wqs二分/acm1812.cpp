#include <algorithm>
#include <cstdio>

int const maxn = 100003;
int n = 0, m = 0, k = 0;

int extra_weigh = 0;
struct Edge {
	int u, v;
	int w, col;
	int weigh() const {
		return w + (col ? 0 : extra_weigh);
	}
};
bool operator<(Edge const &lhs, Edge const &rhs) {
	return lhs.weigh() == rhs.weigh() ? lhs.col < rhs.col : lhs.weigh() < rhs.weigh();
}

Edge a[maxn];

int fa[maxn];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) {
	fa[find(x)] = find(y);
}

int total = 0, use = 0;
bool check() {
	std::sort(a + 1, a + m + 1);
	for (int i = 0; i <= n; ++i)
		fa[i] = i;
	total = use = 0;
	for (int i = 1; i <= m; ++i) {
		if (find(a[i].u) == find(a[i].v))
			continue;
		merge(a[i].u, a[i].v);
		total += a[i].weigh();
		if (a[i].col == 0) ++use;
	}
	return use >= k;
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= m; ++i)
		scanf("%d %d %d %d", &a[i].u, &a[i].v, &a[i].w, &a[i].col);
	int const delta = 120;
	int L = 0, R = 2 * delta;
	int ans = 0;
	while (L <= R) {
		int mid = (L + R) >> 1;
		extra_weigh = mid - delta;
		if (check()) {
			ans = total - k * extra_weigh;
			L = mid + 1;
		}
		else R = mid - 1;
	}
	printf("%d\n", ans);
	return 0;
}
