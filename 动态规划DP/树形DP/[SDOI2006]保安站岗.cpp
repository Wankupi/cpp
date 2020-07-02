#include <cstdio>
#define int long long
int n = 0;
int a[1501], fa[1501];
int head[1501], nxt[1503], to[1503], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
inline int min(int a, int b) { return a < b ? a : b; }
int f[1501][3]; // 0-> 自己有  1-> 被子节点覆盖  2-> 被父节点覆盖
void dfs(int x) {
	f[x][0] = a[x];
	f[x][1] = f[x][2] = 0;
	bool sons = false;
	int minn = 0x3f3f3f3f;
	for (int i = head[x]; i; i = nxt[i]) {
		sons = true;
		dfs(to[i]);
		int t = min(f[to[i]][0], f[to[i]][1]);
		f[x][0] += min(f[to[i]][2], t);
		f[x][1] += t;
		f[x][2] += t;
		minn = min(minn, f[to[i]][0] - f[to[i]][1]);
	}
	if (minn > 0) f[x][1] += minn;
	if (!sons) f[x][1] = 0x3f3f3f3f;
}
signed main() {
	scanf("%lld", &n);
	int id = 0, m = 0, x = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld%lld%lld", &id, &x, &m);
		a[id] = x;
		for (int j = 1; j <= m; ++j) {
			scanf("%lld", &x);
			fa[x] = id;
			insert(id, x);
		}
	}
	int root = 0;
	for (int i = 1; i <= n; ++i)
		if (fa[i] == 0) {
			root = i;
			dfs(i);
			break;
		}
	printf("%lld", min(f[root][0], f[root][1]));
	return 0;
}