#include <cstdio>
int n = 0, m = 0;
int head[100001], nxt[500001], to[500001], cnt = 0;
inline void add(int u, int e) {	nxt[++cnt] = head[u]; to[cnt] = e; head[u] = cnt;}
int dfn[100001], low[100001], stack[100001], up = 0, tc = 0;
bool vis[100001];
int fa[100001], in[100001];
inline int min(int a, int b) { return a < b ? a : b; }
void tarjan(int x) {
	dfn[x] = low[x] = ++tc;
	stack[++up] = x; vis[x] = true;
	for (int i = head[x]; i; i = nxt[i]) {
		if (!dfn[to[i]]) {
			tarjan(to[i]);
			low[x] = min(low[x],low[to[i]]);
		}
		else if (vis[to[i]])
			low[x] = min(low[x], dfn[to[i]]);
	}
	if (low[x] == dfn[x]) {
		int j = 0;
		while (j!=x) {
			j = stack[up--];
			fa[j] = x;
			vis[j] = false;
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	int b = 0, e = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &b, &e);
		if (b != e) add(b, e);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i);
	for (int x = 1; x <= n; ++x) {
		for (int i = head[x]; i; i = nxt[i])
			if (fa[x] != fa[to[i]]) ++in[fa[to[i]]];
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		if (fa[i] == i && in[i] == 0)++ans;
	printf("%d", ans);
	return 0;
}