#include <cstdio>
#include <cstring>
int n = 0, m = 0, availPoint = 0;
char map[105][105];
const int dx[4] = {-1, +1, 0, 0}, dy[4] = {0, 0, +1, -1};
inline int funcPosID(int y, int x) { return (y - 1) * m + x; }
inline int color(int y, int x) { return (x + y) & 1; }
int head[10005], nxt[40005], to[40005], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int match[10005];
bool vis[10005];
bool dfs(int x) {
	vis[x] = true;
	for (int i = head[x]; i; i = nxt[i]) {
		if (!match[to[i]] || (!vis[match[to[i]]] && dfs(match[to[i]]))) {
			match[x] = to[i];
			match[to[i]] = x;
			return true;
		}
	}
	return false;
}
int win[10005];
void find(int x) {
	win[x] = 1;
	vis[x] = true;
	for (int i = head[x]; i; i = nxt[i])
		if (match[to[i]] && vis[match[to[i]]] == false)
			find(match[to[i]]);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%s", map[i] + 1);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (map[i][j] == '#') continue;
			++availPoint;
			//if (color(i, j) == 0) continue;
			for (int k = 0; k < 4; ++k) {
				int y = i + dy[k], x = j + dx[k];
				if (x < 1 || x > m || y < 1 || y > n) continue;
				if (map[y][x] == '#') continue;
				insert(funcPosID(i, j), funcPosID(y, x));
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			if (map[i][j] == '#' || color(i, j) == 0) continue;
			memset(vis, 0, sizeof vis);
			if (dfs(funcPosID(i, j))) ++ans;
		}
	if (ans * 2 == availPoint)
		puts("LOSE");
	else {
		puts("WIN");
		memset(vis, 0, sizeof vis);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (map[i][j] != '#' && match[funcPosID(i, j)] == 0)
					find(funcPosID(i, j));
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (win[funcPosID(i, j)] == 1)
					printf("%d %d\n", i, j);
	}
	return 0;
}