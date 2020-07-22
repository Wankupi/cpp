#include <cstdio>
const int maxn = 200001;
int n = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 0;
inline void insert(int u, int e, int v) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
	val[cnt] = v;
}
int f[maxn][2], Mv[maxn], Mvp[maxn], sec[maxn];
inline int max(int a, int b) { return a < b ? b : a; }
void dfs1(int x, int fa) {
	Mv[x] = sec[x] = -0x3f3f3f3f;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa) {
			dfs1(to[i], x);
			f[x][0] += max(f[to[i]][0], f[to[i]][1] + val[i]);
			int v = f[to[i]][0] + val[i] - max(f[to[i]][0], f[to[i]][1] + val[i]);
			if (Mv[x] < v) {
				sec[x] = Mv[x];
				Mv[x] = v;
				Mvp[x] = to[i];
			} else if (v > sec[x])
				sec[x] = v;
		}
	f[x][1] = f[x][0] + Mv[x];
}
int ans = 0;
void dfs2(int x, int fa) {
	ans = max(ans, f[x][0]);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa) {
			int f0 = 0, f1 = 0;
			f0 = f[x][0] - max(f[to[i]][0], f[to[i]][1] + val[i]);
			if (to[i] != Mvp[x])
				f1 = f[x][1] - max(f[to[i]][0], f[to[i]][1] + val[i]);
			else
				f1 = f[x][1] - Mv[x] + sec[x] - max(f[to[i]][0], f[to[i]][1] + val[i]) ;

			f[to[i]][0] += max(f0, f1 + val[i]);
			int v = f0 + val[i] - max(f0, f1 + val[i]);
			if (v > Mv[to[i]]) {
				sec[to[i]] = Mv[to[i]];
				Mv[to[i]] = v;
				Mvp[to[i]] = x;
			} else if (v > sec[to[i]])
				sec[to[i]] = v;
			f[to[i]][1] = f[to[i]][0] + Mv[to[i]];
			dfs2(to[i], x);
		}
}
int main() {
	scanf("%d", &n);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		insert(x, y, z);
		insert(y, x, z);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	printf("%d", ans);
	return 0;
}