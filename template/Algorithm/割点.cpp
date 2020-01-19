#include <cstdio>
using namespace std;
int head[20001], nxt[200005], to[200005], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e;}
int dfn[20001], low[20001], num = 0;
int root = 0;
bool cut[20001];
inline int min(int a, int b) { return a < b ? a : b; }
void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	int flag = 0;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = to[i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x]) {
				++flag;
				if (x != root||flag > 1 )
					cut[x] = true;
			}
		}
		else low[x] = min(low[x], dfn[y]);
	}
}
int main() {
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		insert(x, y); insert(y, x);
	}
	for (int i = 1; i <= n; ++i) if (!dfn[i]) {
		root = i; tarjan(i);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		if (cut[i])++ans;
	printf("%d\n", ans);
	for (int i = 1; i <= n; ++i)
		if (cut[i]) printf("%d ", i);
	return 0;
}