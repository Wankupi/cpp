// 1 倍增
#include <iostream>
#include <cmath>
using namespace std;
int n = 0, m = 0, s = 0;
int head[500001], nxt[1000001], to[1000001];
int cnt = 0;
inline void add(int u, int e) {
	nxt[++cnt] = head[u]; to[cnt] = e; head[u] = cnt;
}
int deep[500001];
int fa[500001][30];//第i个节点的第2^j个父节点
int mD = 0;
void dfs(int ro, int f, int de) {
	if (de > mD) mD = de;
	for (int i = head[ro]; i; i = nxt[i])
		if (to[i] != f) {
			fa[to[i]][0] = ro; deep[to[i]] = de;
			dfs(to[i], ro, de + 1);
		}
}
inline void lca() {
	for (int j = 1; j <= mD; j++)
		for (int i = 1; i <= n; ++i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
}
int main() {
	scanf("%d%d%d", &n, &m, &s);
	int x = 0, y = 0;
	for (int i = 1; i <= n - 1; i++) {
		scanf("%d%d", &x, &y);
		add(x, y); add(y, x);
	}
	fa[s][0] = s;
	deep[s] = 1;
	dfs(s, s, 2);
	mD = log(mD) / log(2) + 1;
	lca();
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		if (deep[x] < deep[y]) swap(x, y);//使x的深度更大
		for (int j = 20; ~j; --j)
			if (deep[fa[x][j]] >= deep[y]) x = fa[x][j];
		if (x == y) printf("%d\n", x);
		else {
			for (int j = mD; ~j; --j)
				if (fa[x][j] != fa[y][j]) x = fa[x][j], y = fa[y][j];
			printf("%d\n", fa[x][0]);
		}
	}
	return 0;
}

// 2 树剖
#include <iostream>
using namespace std;
constexpr int maxN = 500001;
int n = 0, m = 0, root = 0;
int head[maxN], nxt[2 * maxN], to[2 * maxN], cnt = 0;
inline void add(int u, int e) { nxt[++cnt] = head[u]; to[cnt] = e; head[u] = cnt; }
int fa[maxN], siz[maxN], son[maxN], deep[maxN];
int top[maxN];
void dfs1(int x) {
	siz[x] = 1;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x]) {
			fa[to[i]] = x; deep[to[i]] = deep[x] + 1;
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[son[x]] < siz[to[i]])son[x] = to[i];
		}
}
void dfs2(int x, int f) {
	top[x] = f;
	if (son[x])	dfs2(son[x], f);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x] && to[i] != son[x]) dfs2(to[i], to[i]);
}
int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (deep[top[y]] > deep[top[x]]) x ^= y ^= x ^= y;
		x = fa[top[x]];
	}
	return deep[x] > deep[y] ? y : x;
}
int main() {
	scanf("%d%d%d", &n, &m, &root);
	int a = 0, b = 0;
	for (int i = 1; i != n; ++i) {
		scanf("%d%d", &a, &b); add(a, b); add(b, a);
	}
	deep[root] = 1; fa[root] = root; dfs1(root);
	dfs2(root, root);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &a, &b); printf("%d\n", lca(a, b));
	}
	return 0;
}