#include <algorithm>
#include <cstdio>
using namespace std;
int const mod = 31011;
int n = 0, m = 0;
struct Edge {
	int u, e;
	int v;
};
inline bool operator<(Edge const &lhs, Edge const &rhs) { return lhs.v < rhs.v; }
Edge line[1033];
bool onTree[1033];
int fa[1033], block = 0;
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) return;
	fa[x] = y;
}
int id[133];
long long a[133][133];
long long det(int N) {
	long long det = 1;
	for (int i = 1; i <= N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			while (a[j][i] != 0) {
				long long k = a[i][i] / a[j][i];
				for (int p = i; p <= N; ++p)
					a[i][p] = (a[i][p] - k * a[j][p] % mod + mod) % mod;
				det = mod - det;
				std::swap(a[i], a[j]);
			}
		}
	}
	for (int i = 1; i <= N; ++i)
		det = det * a[i][i] % mod;
	return det;
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i)
		scanf("%d %d %d", &line[i].u, &line[i].e, &line[i].v);
	sort(line + 1, line + m + 1);
	block = n;
	for (int i = 1; i <= n; ++i)
		fa[i] = i;
	for (int i = 1; i <= m; ++i)
		if (find(line[i].u) != find(line[i].e))
			merge(line[i].u, line[i].e), onTree[i] = true, --block;
	if (block > 1) {
		puts("0");
		return 0;
	}
	long long ans = 1;
	for (int i = 1; i <= m;) {
		for (int j = 1; j <= n; ++j)
			fa[j] = j;
		for (int j = 1; j <= m; ++j)
			if (onTree[j] && line[j].v != line[i].v)
				merge(line[j].u, line[j].e);
		for (int i = 0; i <= n; ++i) id[i] = 0;
		for (int j = 1; j <= n; ++j) {
			if (!id[find(j)]) id[find(j)] = ++id[0];
			id[j] = id[find(j)];
		}
		for (int j = 1; j <= id[0]; ++j)
			for (int k = 1; k <= id[0]; ++k)
				a[j][k] = 0;
		int j = i;
		while (j <= m && line[j].v == line[i].v) {
			int u = id[line[j].u], e = id[line[j].e];
			--a[u][e];
			--a[e][u];
			++a[u][u];
			++a[e][e];
			++j;
		}
		for (int k = 1; k <= id[0]; ++k)
			for (int p = 1; p <= id[0]; ++p)
				if (a[k][p] < 0) a[k][p] += mod;
		ans = ans * det(id[0] - 1) % mod;
		i = j;
	}
	printf("%lld", ans);
	return 0;
}