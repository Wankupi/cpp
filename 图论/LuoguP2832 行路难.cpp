/*
纯队列spfa
一个点后一次被更新时经过的边数不小于前一次
bfs -- 序
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n = 0, m = 0;
int head[10001], nxt[200003], to[200003], val[200003], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
inline int min(int a, int b) { return a < b ? a : b; }
int dis[10001], pl[10001];
struct St {
	int x, d, k, pre;
};
St dl[200000];
int l = 1, r = 0;
void spfa() {
	memset(dis, 0x3f, sizeof dis);
	dis[n] = 0;
	dl[l = r = 1] = { n,0,0,0 };
	while (l <= r) {
		St s = dl[l];
		for (int i = head[s.x]; i; i = nxt[i]) {
			if (dis[to[i]] > s.d + s.k + val[i]) {
				dis[to[i]] = s.d + s.k + val[i];
				dl[++r] = { to[i],dis[to[i]],s.k + 1, l };
				pl[to[i]] = r;
			}
		}
		l++;
	}
}
void dfs(int s) {
	printf("%d ", dl[s].x);
	if (dl[s].pre) dfs(dl[s].pre);
}
int main() {
	scanf("%d%d", &n, &m);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		insert(y, x, z);
	}
	spfa();
	printf("%d\n", dis[1]);
	dfs(pl[1]);
	return 0;
}