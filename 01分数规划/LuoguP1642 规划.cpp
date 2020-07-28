#include <cstdio>
#include <cstring>
int n = 0, m = 0;
int A[103], B[103];
int head[103], nxt[203], to[203], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int siz[103];
double Val = 0;
double f[103][103];
// inline int min(int a, int b) { return a < b ? a : b; }
inline double max(double a, double b) { return a < b ? b : a; }
void dfs(int x, int fa) {
	siz[x] = 1;
	for (int j = 0; j <= m; ++j)
		f[x][j] = -1e6;
	f[x][1] = A[x] - B[x] * Val;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa) {
			dfs(to[i], x);
			// siz[x] += siz[to[i]];
			for (int j = m; j >= 1; --j) {
				for (int k = 0; k < j; ++k)
					f[x][j] = max(f[x][j], f[x][j - k] + f[to[i]][k]);
			}
		}
	f[x][0] = 0.0;
}
bool check() {
	dfs(1, 0);
	for (int i = 1; i <= n; ++i)
		if (f[i][m] >= 0) return true;
	return false;
}
int main() {
	scanf("%d%d", &n, &m);
	m = n - m; // 改为保留 m 个
	for (int i = 1; i <= n; ++i)
		scanf("%d", A + i);
	for (int i = 1; i <= n; ++i)
		scanf("%d", B + i);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	double L = 0.0, R = 100000.0;
	while (R - L > 0.001) {
		Val = 0.500 * (L + R);
		if (check())
			L = Val;
		else
			R = Val;
	}
	printf("%.1lf", L);
	return 0;
}