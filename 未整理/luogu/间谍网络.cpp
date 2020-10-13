/*
分析：
必选零入度点，而其他点不需要选
因为可以被零入度点直接或间接访问到
而显然图中存在环，因此先缩点为有向无环图，然后找到所有的起点
将起点的权加起来就是答案。
如果从可以收买的点，不能到达全部的点，那么没有答案。
*/
#include <cstdio>
using namespace std;
const int INF = 0x7fffffff;
int n = 0, p = 0;
int head[3001], nxt[8001], to[8001], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int need[3001], symbol[3001];
inline int max(int a, int b) { return a < b ? b : a; }
inline int min(int a, int b) { return a < b ? a : b; }
namespace TAR {
	int dfn[3001], low[3001], num = 0;
	int stack[3001], top = 0;
	bool instack[3001];
	void tarjan(int x) {
		dfn[x] = low[x] = ++num;
		stack[++top] = x; instack[x] = true;
		int y = 0;
		for (int i = head[x]; i; i = nxt[i]) {
			y = to[i];
			if (!dfn[y]) {
				tarjan(y);
				low[x] = min(low[x], low[y]);
			}
			else if (instack[y]) low[x] = min(low[x], dfn[y]);
		}
		if (dfn[x] == low[x])
			do {
				y = stack[top--]; instack[y] = false;
				symbol[y] = x;
				need[x] = min(need[x], need[y]);
			} while (y != x);
	}
}
int in[3001];
int main() {
	scanf("%d%d", &n, &p);
	int x = 0, y = 0;
	for (int i = 1; i <= n; ++i)
		need[i] = INF;
	for (int i = 1; i <= p; ++i) {
		scanf("%d%d", &x, &y);
		need[x] = y;
	}
	int r = 0; scanf("%d", &r);
	for (int i = 1; i <= r; ++i) {
		scanf("%d%d", &x, &y);
		insert(x, y);
	}
	for (int x = 1; x <= n; ++x) if (need[x] != INF && !TAR::dfn[x]) TAR::tarjan(x);
	for (int x = 1; x <= n; ++x)
		if (need[x] == INF && TAR::dfn[x] == 0) {
			printf("NO\n%d", x);
			return 0;
		}
	for (int x = 1; x <= n; ++x)
		for (int i = head[x]; i; i = nxt[i]) {
			if (symbol[x] != symbol[to[i]])
				++in[symbol[to[i]]];
		}
	int ans = 0;
	for (int x = 1; x <= n; ++x)
		if (x == symbol[x] && in[x] == 0) ans += need[x];
	printf("YES\n%d", ans);
	return 0;
}