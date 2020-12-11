#include <cstdio>
const int maxn = 2000001;
int n = 0, m = 0;
int head[maxn], nxt[maxn], to[maxn], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
inline int min(int a, int b) { return a < b ? a : b; }
int dfn[maxn], low[maxn], cc = 0;
bool vis[maxn];
int stage[maxn], up = 0;
int nick[maxn],c2=0;
void tarjan(int x) {
	dfn[x] = low[x] = ++cc;
	stage[++up] = x;
	vis[x] = true;
	for (int i = head[x]; i; i = nxt[i]) {
		if (!dfn[to[i]]) {
			tarjan(to[i]);
			low[x] = min(low[x], low[to[i]]);
		} else if (vis[to[i]])
			low[x] = min(low[x], dfn[to[i]]);
	}
	if (dfn[x] == low[x]) {
		int y = 0;
		++c2;
		while (y != x) {
			y = stage[up--];
			nick[y] = c2;
			vis[y] = false;
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	int a = 0, b = 0, x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d%d", &x, &a, &y, &b);
		//不妨定义x为0，x+n为1
		// ~A -> B	~B -> A
		insert(x + (a ^ 1) * n, y + b * n);
		insert(y + (b ^ 1) * n, x + a * n);
	}
	for (int i = 1; i <= n << 1; ++i)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; ++i)
		if (nick[i] == nick[i + n]) {
			printf("IMPOSSIBLE");
			return 0;
		}
	printf("POSSIBLE\n");
	for(int i=1;i<=n;++i)
		printf("%d ",int(nick[i] > nick[i+n]));
	return 0;
}