#include <cstdio>
int n = 0, M = 0;
char G[50][50];
int fa[50], siz[50];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) {
	x = find(x); y = find(y);
	if (x == y) return;
	siz[x] += siz[y];
	fa[y] = x;
}
inline int lowbit(int x) { return x & -x; }
inline int Mcount(int x) { int cnt = 0; while (x) { cnt += (x & 1); x >>= 1; } return cnt; }
int id[50], cId = 0;
int ban[25];
int lg2[1 << 23], f[1 << 23], r[1 << 23], g[1 << 23];
int w[1 << 23];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) fa[i] = i, siz[i] = 1;
	for (int i = 1; i <= n; ++i) {
		scanf("%s", G[i] + 1);
		for (int j = 1; j <= n; ++j)
			if (G[i][j] == 'A') merge(i, j);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (G[i][j] == 'X' && find(i) == find(j)) {
				puts("-1");
				return 0;
			}
	for (int i = 1; i <= n; ++i)
		if (fa[i] == i && siz[i] >= 2) id[i] = cId++;
	M = 1 << cId;
	if (cId == 0) {
		printf("%d", n - 1);
		return 0;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (G[i][j] == 'X' && siz[find(i)] >= 2 && siz[find(j)] >= 2)
				ban[id[find(i)]] |= (1 << id[find(j)]);
	for (int i = 2; i < M; ++i) lg2[i] = lg2[i >> 1] + 1;
	for (int s = 1; s < M; ++s) {
		int fr = s ^ lowbit(s), t = lowbit(s);
		if (fr == 0 || (f[fr] && (r[fr] & t) == 0)) f[s] = 1;
		r[s] = (r[fr] | ban[lg2[t]]);
	}
	if (f[M - 1]) {
		printf("%d", n);
		return 0;
	}
	for (int len = 1; len < M; len <<= 1) {
		for (int i = 0; i < M; i += 2 * len) {
			for (int j = 0; j < len; ++j)
				f[i + j + len] += f[i + j];
		}
	}
	for (int i = 0; i < M; ++i) {
		g[i] = f[i];
		w[i] = (cId - Mcount(i)) & 1 ? -1 : 1;
	}
	for (int i = 1; i <= n; ++i) {
		int ans = 0;
		for (int j = 0; j < M; ++j) {
			g[j] *= f[j];
			ans += w[j] * g[j];
		}
		if (ans) {
			printf("%d", n + i);
			return 0;
		}
	}
	return 0;
}