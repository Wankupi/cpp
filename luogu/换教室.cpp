#include <cstdio>
#include <cstring>
const double inf = 1e9;
int n = 0, m = 0, v = 0, e = 0;
int c[2001], d[2001];
double k[2001];
int w[305][305];
inline int min(int a, int b) { return a < b ? a : b; }
inline double min(double a, double b) { return a < b ? a : b; }
void read_init() {
	scanf("%d %d %d %d", &n, &m, &v, &e);
	for (int i = 1; i <= n; ++i) scanf("%d", c + i);
	for (int i = 1; i <= n; ++i) scanf("%d", d + i);
	for (int i = 1; i <= n; ++i) scanf("%lf", k + i);
	memset(w,0x3f,sizeof(w));
	for (int i = 0; i <= v; ++i) w[i][i] = 0;
	int x = 0, y = 0, val=0;
	for (int i = 1; i <= e; ++i) {
		scanf("%d %d %d", &x, &y,&val);
		w[x][y] = w[y][x] = min(w[x][y], val);
	}
	for (int p = 1; p <= v; ++p)
		for (int i = 1; i <= v; ++i)
			for (int j = 1; j <= v; ++j)
				w[i][j] = min(w[i][j], w[i][p] + w[p][j]);
}
double f[2001][2001][2];
int main() {
	read_init();
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
			f[i][j][0] = f[i][j][1] = inf;
	f[1][0][0] = f[1][1][1] = 0;
	for (int i = 2; i <= n; ++i) {
		f[i][0][0] = f[i - 1][0][0] + w[c[i - 1]][c[i]];
		for (int j = 1; j <= min(m, i); ++j) {
			f[i][j][0] = min(f[i - 1][j][0] + w[c[i - 1]][c[i]],
							 f[i - 1][j][1] + w[c[i - 1]][c[i]] * (1 - k[i - 1]) + w[d[i - 1]][c[i]] * k[i - 1]);
			f[i][j][1] = min(
				f[i - 1][j - 1][0] + w[c[i - 1]][d[i]] * k[i] + w[c[i - 1]][c[i]] * (1 - k[i]),
				f[i - 1][j - 1][1] + w[c[i - 1]][c[i]] * (1 - k[i - 1]) * (1 - k[i]) + w[c[i - 1]][d[i]] * (1 - k[i - 1]) * k[i] + w[d[i - 1]][c[i]] * k[i - 1] * (1 - k[i]) + w[d[i - 1]][d[i]] * k[i - 1] * k[i]);
		}
	}
	double ans = inf;
	for (int j = 0; j <= m; ++j)
		ans = min(ans, min(f[n][j][0], f[n][j][1]));
	printf("%.2lf", ans);
	return 0;
}