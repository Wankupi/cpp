//求 是否 存在 路径长度为给定值
#include <bitset>
#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 10001;
inline int max(int a, int b) { return a < b ? b : a; }
int n = 0, m = 0;
int head[maxn], nxt[20001], to[20001], val[20001], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int Siz = 0, root = 0;	 //整棵树的大小(目前正在处理的)
int siz[maxn], mx[maxn]; //子树大小和最大子树大小
bool vis[maxn];
void dfs_getRoot(int x, int f) {
	siz[x] = 1; mx[x] = 0;//先清零.
	for (int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]] && to[i] != f) {
			dfs_getRoot(to[i], x);
			siz[x] += siz[to[i]];
			mx[x] = max(mx[x], siz[to[i]]);
		}
	mx[x] = max(mx[x], Siz - mx[x]);
	if (mx[x] < mx[root])
		root = x;
}
int dis[maxn], fa[maxn], stage[maxn], up = 0;
void disToRoot(int r, int deta) {
	up = 0;
	queue<int> q;
	q.push(r); fa[r] = r;
	dis[r] = deta;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		stage[++up] = dis[x];
		for (int i = head[x]; i; i = nxt[i])
			if (!vis[to[i]] && fa[x] != to[i]) {
				dis[to[i]] = dis[x] + val[i];
				fa[to[i]] = x;
				q.push(to[i]);
			}
	}
}
bitset<10000001> able;
int ques[maxn], use[maxn];
bool ans[maxn];
void solve(int x) {
	able[0] = true;
	for (int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]) {
			disToRoot(to[i], val[i]); // 一个子树一个子树求dis->方便合并
			for (int i = 1; i <= up; ++i)
				for (int j = 1; j <= m; ++j)
					if (ques[j] >= stage[i]) //只关心可不可以拼出所询问的
						ans[j] |= able[(ques[j] - stage[i])];
			for (int i = 1; i <= up; ++i) {
				able[stage[i]] = true;
				use[++use[0]] = stage[i];
			}
		}
	while (use[0])
		able[use[use[0]--]] = false;
}

void devide(int x) { // 点分治主体
	vis[x] = true;
	solve(x); // 处理目前子树
	for (int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]) {
			Siz = siz[to[i]]; root = 0; //在solve中已经求过各树的大小.
			dfs_getRoot(to[i], x);
			if (siz[root] > 1)
				devide(root);
		}
}
int main() {
	scanf("%d%d", &n, &m);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i != n; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		insert(x, y, z); insert(y, x, z);
	}
	int k = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &k);
		ques[i] = k;
	}
	mx[0] = 0x7fffffff;
	Siz = n; root = 0;
	dfs_getRoot(1, 1);
	devide(root);
	for (int i = 1; i <= m; ++i)
		puts(ans[i] ? "AYE" : "NAY");
	return 0;
}