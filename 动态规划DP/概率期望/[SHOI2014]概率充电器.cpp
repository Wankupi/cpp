// 换根
#include <cstdio>
const int maxn = 500003;
int n = 0;
double q[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
double val[maxn << 1];
inline void insert(int u, int e, double v) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
	val[cnt] = v;
}
double f[maxn], fa[maxn];
void dfs1(int x, int fath) {
	fa[x] = fath;
	f[x] = 1 - q[x];
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fath) {
			dfs1(to[i], x);
			f[x] *= (1 - val[i] + val[i] * f[to[i]]);
		}
}
void dfs2(int x) {
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x]) {
			double t = f[x] / (1 - val[i] + val[i] * f[to[i]]);
			f[to[i]] *= (1 - val[i] + val[i] * t);
			dfs2(to[i]);
		}
}
int main() {
	scanf("%d", &n);
	int a = 0, b = 0;
	double p = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d%lf", &a, &b, &p);
		insert(a, b, 0.01 * p);
		insert(b, a, 0.01 * p);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%lf", q + i);
		q[i] *= 0.01;
	}
	dfs1(1, 0);
	dfs2(1);
	double sum = 0.0;
	for (int i = 1; i <= n; ++i)
		sum += 1 - f[i];
	printf("%.6lf", sum);
	return 0;
}