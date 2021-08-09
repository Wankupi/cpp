#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 1003;
int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int n = 0, m = 0, s = 0, t = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int d[maxn]; // 度
int dis[maxn];
void spfa(int S) {
	memset(dis, 0x3f, sizeof dis);
	queue<int> q;
	dis[S] = 0;
	q.push(S);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (dis[to[i]] > dis[x] + 1) {
				dis[to[i]] = dis[x] + 1;
				q.push(to[i]);
			}
	}
}
int step[maxn][maxn];
double f[maxn][maxn];
void init() {
	for (int x = 1; x <= n; ++x) {
		spfa(x);
		for (int y = 1; y <= n; ++y) {
			if (dis[y] <= 2) f[y][x] = 1.0;
			else f[y][x] = -1.0;

			for (int i = head[y]; i; i = nxt[i]) {
				if (dis[y] < dis[step[to[i]][x]] || (dis[y] == dis[step[to[i]][x]] && y < step[to[i]][x]))
					step[to[i]][x] = y;
			}
			step[x][x] = x;
		}
		f[x][x] = 0.0;
	}
	// 这样的变换是错误的，因为可能用到已经修改的值，导致前进好多步。
	//for (int x = 1; x <= n; ++x)
	//	for (int y = 1; y <= n; ++y)
	//		step[x][y] = step[step[x][y]][y]; // one step, another step
}
double dfs(int x, int y) {
	if (f[x][y] >= 0) return f[x][y];
	f[x][y] = 0;
	f[x][y] += dfs(step[step[x][y]][y], y) + 1.0;
	for (int i = head[y]; i; i = nxt[i])
		f[x][y] += dfs(step[step[x][y]][y], to[i]) + 1.0;
	f[x][y] /= d[y] + 1.0;
	return f[x][y];
}
int main() {
	n = read(); m = read(); s = read(); t = read();
	int a = 0, b = 0;
	for (int i = 1; i <= m; ++i) {
		a = read(); b = read();
		insert(a, b);
		insert(b, a);
		++d[a]; ++d[b];
	}
	init();
	double ans = dfs(s, t);
	printf("%.3lf", ans);
	return 0;
}