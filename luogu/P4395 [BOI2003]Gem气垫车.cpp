#include <cstdio>
int n = 0;
int head[10003], nxt[20007], to[20007], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int mv[10003][16];
inline int min(int a, int b) { return a < b ? a : b; }

void dfs(int x, int f) {
	for (int v = 1; v <= 15; ++v)
		mv[x][v] = v;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs(to[i], x);
			for (int v = 1; v <= 15; ++v)
				mv[x][v] += mv[to[i]][v];
		}
	int minV = 999999, minP = 0, cminV = 999999;
	for (int v = 1; v <= 15; ++v) {
		if (mv[x][v] < minV) {
			cminV = minV;
			minV = mv[x][v];
			minP = v;
		} else if (mv[x][v] < cminV)
			cminV = mv[x][v];
	}
	for (int v = 1; v <= 15; ++v) {
		if (v == minP)
			mv[x][v] = cminV;
		else
			mv[x][v] = minV;
	}
}

int main() {
	scanf("%d", &n);
	int a = 0, b = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &a, &b);
		insert(a, b);
		insert(b, a);
	}
	dfs(1, 0);
	printf("%d", min(mv[1][1], mv[1][2]));
	return 0;
}