#include <cstdio>
#include <cstring>
#include <algorithm>
int const maxn = 500003, maxm = 2000003;
int n = 0, m = 0;
int head[maxn], nxt[maxm], to[maxm], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int dep[maxn], fa[maxn];
void dfs(int x, int f) {
	dep[x] = dep[f] + 1;
	fa[x] = f;
	for (int i = head[x]; i; i = nxt[i])
		if (!dep[to[i]])
			dfs(to[i], x);
}
int a[maxn];
int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++i) head[i] = dep[i] = 0;
		cnt = 0;
		int x = 0, y = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%d %d", &x, &y);
			insert(x, y);
			insert(y, x);
		}
		dfs(1, 0);
		for (x = 1; x <= n; ++x)
			if (dep[x] >= (n + 1) / 2) break;
		if (x <= n) {
			printf("PATH\n%d\n", dep[x]);
			while (x) {
				printf("%d ", x);
				x = fa[x];
			}
			printf("\n");
		}
		else {
			for (int i = 1; i <= n; ++i) a[i] = i;
			std::sort(a + 1, a + n + 1, [](int x, int y) { return dep[x] < dep[y]; });
			int SDcnt = 0;
			for (int i = 1; i < n; ++i)
				if (dep[a[i]] == dep[a[i + 1]]) {
					++SDcnt;
					++i;
				}
			printf("PAIRING\n%d\n", SDcnt);
			for (int i = 1; i < n; ++i)
				if (dep[a[i]] == dep[a[i + 1]]) {
					printf("%d %d\n", a[i], a[i + 1]);
					++i;
				}
		}
	}
	return 0;
}