// 换根DP
#include <cstdio>
const int maxn = 20003;
int n = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 0;
inline void insert(int u, int e, int v) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
	val[cnt] = v;
}
int g[maxn][3];
void dfs1(int x, int f) {
	g[x][0] = 1;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs1(to[i], x);
			g[x][val[i] % 3] += g[to[i]][0];
			g[x][(1 + val[i]) % 3] += g[to[i]][1];
			g[x][(2 + val[i]) % 3] += g[to[i]][2];
		}
}
int tem[3];
void dfs2(int x, int f) {
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			tem[val[i] % 3] = g[x][val[i] % 3] - g[to[i]][0];
			tem[(1 + val[i]) % 3] = g[x][(1 + val[i]) % 3] - g[to[i]][1];
			tem[(2 + val[i]) % 3] = g[x][(2 + val[i]) % 3] - g[to[i]][2];
			g[to[i]][val[i] % 3] += tem[0];
			g[to[i]][(1 + val[i]) % 3] += tem[1];
			g[to[i]][(2 + val[i]) % 3] += tem[2];
			dfs2(to[i], x);
		}
}
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main() {
	scanf("%d", &n);
	int a = 0, b = 0, c = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		insert(a, b, c % 3);
		insert(b, a, c % 3);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	int sum = 0, down = n * n;
	for (int i = 1; i <= n; ++i)
		sum += g[i][0];
	int G = gcd(sum, down);
	sum /= G;
	down /= G;
	printf("%d/%d", sum, down);
	return 0;
}