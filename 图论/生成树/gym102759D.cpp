#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
int const maxn = 300003, inf = 0x3f3f3f3f;

struct Edge {
	int x, y, z;
};
inline bool operator<(Edge const &lhs, Edge const &rhs) { return lhs.z > rhs.z; }

int n = 0, m = 0;
Edge a[maxn];

int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 0;
inline void insert(int u, int e, int v) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
	val[cnt] = v;
}

namespace calc {
	int fa[maxn], siz[maxn], mi[maxn];
	inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

	ll Kruskal() {
		sort(a + 1, a + m + 1);
		for (int i = 1; i <= n; ++i) {
			fa[i] = i;
			siz[i] = 1;
			mi[i] = inf;
		}
		ll counted = 0, sum = 0;
		for (int i = 1; i <= m; ++i) {
			int x = find(a[i].x), y = find(a[i].y);
			if (x != y) {
				sum += ll(siz[x]) * siz[y] * a[i].z;
				counted += ll(siz[x]) * siz[y];
				if (siz[x] < siz[y]) std::swap(x, y);
				fa[y] = x;
				siz[x] += siz[y];
				mi[x] = a[i].z;
				insert(a[i].x, a[i].y, a[i].z);
				insert(a[i].y, a[i].x, a[i].z);
			} else if (mi[x] > a[i].z)
				return -1;
		}
		sum += (ll(n) * (n - 1ll) / 2 - counted);
		return sum;
	}
} // namespace calc

namespace check {
	bool vis[maxn];
	int dep[maxn], fa[19][maxn], mi[19][maxn];
	void dfs(int x) {
		vis[x] = true;
		for (int j = 1; j <= 18; ++j) {
			fa[j][x] = fa[j - 1][fa[j - 1][x]];
			mi[j][x] = min(mi[j - 1][x], mi[j - 1][fa[j - 1][x]]);
		}
		for (int i = head[x]; i; i = nxt[i])
			if (!vis[to[i]]) {
				dep[to[i]] = dep[x] + 1;
				fa[0][to[i]] = x;
				mi[0][to[i]] = val[i];
				dfs(to[i]);
			}
	}
	int query_min(int x, int y) {
		if (dep[x] < dep[y]) swap(x, y);
		int ans = inf;
		for (int j = 18; ~j; --j)
			if (dep[fa[j][x]] >= dep[y]) {
				ans = min(ans, mi[j][x]);
				x = fa[j][x];
			}
		if (x == y) return ans;
		for (int j = 18; ~j; --j)
			if (fa[j][x] != fa[j][y]) {
				ans = min(ans, min(mi[j][x], mi[j][y]));
				x = fa[j][x];
				y = fa[j][y];
			}
		ans = min(ans, min(mi[0][x], mi[0][y]));
		return ans;
	}
	bool check() {
		for (int i = 1; i <= n; ++i)
			if (!vis[i]) {
				fa[0][i] = i;
				mi[0][i] = inf;
				dep[i] = 1;
				dfs(i);
			}
		for (int i = 1; i <= m; ++i) {
			int v = query_min(a[i].x, a[i].y);
			if (v != a[i].z) return false;
		}
		return true;
	}
} // namespace check

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i)
		scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].z);
	ll ans = calc::Kruskal();
	if (ans == -1 || !check::check())
		printf("-1");
	else
		printf("%lld", ans);
	return 0;
}