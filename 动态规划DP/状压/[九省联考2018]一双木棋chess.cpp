#include <cstdio>

inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || '9' < c) c = getchar();
	while ('0' <= c && c <= '9') { x = 10 * x + c - '0'; c = getchar(); }
	return x;
}
inline int max(int a, int b) { return a < b ? b : a; }
inline int min(int a, int b) { return a < b ? a : b; }
int const inf = 0x3f3f3f3f;

int n = 0, m = 0;
int a[12][12], b[12][12];
int f[1 << 20];
bool vis[1 << 20];

int dfs(int st, bool first) {
	if (vis[st]) return f[st];
	vis[st] = true;
	f[st] = first ? -inf : inf;
	int y = n + 1, x = 1;
	for (int i = 0; i < n + m - 1; ++i) {
		if ((st >> i) & 1) --y;
		else ++x;
		if (((st >> i) & 3) != 1) continue;
		int nxt = st ^ (3 << i);
		if (first) f[st] = max(f[st], dfs(nxt, !first) + a[y][x]);
		else f[st] = min(f[st], dfs(nxt, !first) - b[y][x]);
	}
	return f[st];
}

int main() {
	n = read(); m = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			a[i][j] = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			b[i][j] = read();
	
	vis[((1 << n) - 1) << m] = true;
	f[((1 << n) - 1) << m] = 0;

	dfs((1 << n) - 1, true);

	printf("%d", f[(1 << n) - 1]);
	return 0;
}
