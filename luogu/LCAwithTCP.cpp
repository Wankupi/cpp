//by WangKP
//LCA with 树链剖分
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
void dfs2(int x,int f) {
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
int main()
{
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