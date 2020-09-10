#include <algorithm>
#include <cstdio>
int const maxn = 100003;
int n = 0;
namespace global {
	int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
	inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
	int dfn[maxn], fa[maxn], son[maxn], siz[maxn], top[maxn], dep[maxn];
	void dfs1(int x, int f);
	void dfs2(int x, int t);
	int lca(int x, int y);
} // namespace global
namespace Virtual {
	int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
	inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
	int dfs(int x);
}
int S[maxn], t = 0, root = 0;
bool isImportant[maxn];
inline bool cmp(int x, int y) { return global::dfn[x] < global::dfn[y]; }
int stack[maxn], top = 0;
void CreateVirtualTree() {
	int (&dfn)[maxn] = global::dfn;
    Virtual::cnt = 0;
	stack[top = 1] = S[1];
	root = S[1];
	for (int i = 2; i <= t; ++i) {
		int lca = global::lca(stack[top], S[i]);
		while (top > 1 && dfn[lca] <= dfn[stack[top -1]]) {
			Virtual::insert(stack[top - 1], stack[top]);
			--top;
		}
		if (stack[top] != lca) {
			Virtual::insert(lca, stack[top]);
			stack[top] = lca;
			if (top == 1) root = lca;
		}
		stack[++top] = S[i];
	}
	while (--top > 0) Virtual::insert(stack[top], stack[top + 1]);
}
int main() {
	scanf("%d", &n);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		global::insert(x, y);
		global::insert(y, x);
	}
	global::dfs1(1, 0);
	global::dfs2(1, 1);
	int q = 0;
	scanf("%d", &q);
	for (int T = 1; T <= q; ++T) {
		scanf("%d", &t);
		for (int i = 1; i <= t; ++i)
			scanf("%d", S + i);
		std::sort(S + 1, S + t + 1, cmp);
		for (int i = 1; i <= t; ++i) isImportant[S[i]] = true;	
		bool sign = true;
		for (int i = 1; i <= t; ++i)
			if (isImportant[global::fa[S[i]]]) {
				sign = false;
				break;
			}
		if (sign) {
			CreateVirtualTree();
			int ans = Virtual::dfs(root);
			printf("%d\n", ans);
		}
		else
			puts("-1");
		for (int i = 1; i <= t; ++i) isImportant[S[i]] = false;
	}
	return 0;
}

namespace global {
	void dfs1(int x, int f) {
		siz[x] = 1;
		fa[x] = f;
		dep[x] = dep[f] + 1;
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != f) {
				dfs1(to[i], x);
				siz[x] += siz[to[i]];
				if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
			}
	}
	void dfs2(int x, int t) {
		top[x] = t;
		dfn[x] = ++dfn[0];
		if (son[x]) dfs2(son[x], t);
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != fa[x] && to[i] != son[x])
				dfs2(to[i], to[i]);
	}
	inline int lca(int x, int y) {
		while (top[x] != top[y])
			dep[top[x]] > dep[top[y]] ? (x = fa[top[x]]) : (y = fa[top[y]]);
		return dep[x] > dep[y] ? y : x;
	}
}
bool g[maxn];
int Virtual::dfs(int x) {
	int f = 0, num = 0;
	for (int i = head[x]; i; i = nxt[i]) {
		f += dfs(to[i]);
		num += g[to[i]];
	}
	if (isImportant[x]) f += num, g[x] = true;
	else if (num >= 2) f += 1, g[x] = false;
	else if (num == 1) g[x] = true;
	else g[x] = false;
	head[x] = 0;
	return f;
}
