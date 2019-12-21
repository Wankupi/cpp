#include <iostream>
#include <cmath>
using namespace std;
int n = 0, m = 0, s = 0;

int head[500001], nxt[1000001], to[1000001];
int cnt = 0;
inline void add(int u, int e) {
	nxt[++cnt] = head[u]; to[cnt] = e; head[u] = cnt;
}
int deep[500001];
int fa[500001][30];//第i个节点的第2^j个父节点
int mD = 0;
void dfs(int ro, int f,int de) {
	if (de > mD) mD = de;
	for (int i = head[ro]; i; i = nxt[i])
		if (to[i] != f) {
			fa[to[i]][0] = ro; deep[to[i]] = de;
			dfs(to[i], ro, de + 1);
		}
}
inline void lca(){
	for (int j = 1; j <= mD; j++)
		for (int i = 1; i <= n; ++i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
}
int main()
{
	scanf("%d%d%d", &n, &m, &s);
	int x = 0, y = 0;
	for (int i = 1; i <= n - 1; i++){
		scanf("%d%d", &x, &y);
		add(x, y); add(y, x);
	}
	fa[s][0] = s;
	deep[s] = 1;
	dfs(s, s, 2);
	mD = log(mD) / log(2) + 1;
	lca();
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		if (deep[x] < deep[y]) swap(x, y);//使x的深度更大
		for (int j = 20; ~j; --j)
			if (deep[fa[x][j]] >= deep[y]) x = fa[x][j];
		if (x == y) printf("%d\n", x);
		else {
			for (int j = mD; ~j; --j)
				if (fa[x][j] != fa[y][j]) x = fa[x][j], y = fa[y][j];
			printf("%d\n", fa[x][0]);
		}
	}
	return 0;
}