#include <cstdio>
#include <algorithm>
using namespace std;
int n = 0, m = 0;
struct ROAD {
	int u = 0; int e = 0; int v = 0;
};
inline  bool operator<(const ROAD &lhs, const ROAD &rhs) {
	return lhs.v > rhs.v;
}
ROAD road[50001];

int fa[10001];
int find(int i) { return fa[i] == i ? i : fa[i] = find(fa[i]); }

int head[10001], nxt[100001], to[100001], val[100001], cnt = 0;
void insert(int u,int e,int v) {
	nxt[++cnt] = head[u]; head[u] = cnt;
	to[cnt] = e; val[cnt] = v;
}
void Kruskal() {
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1; i <= m; ++i) {
		ROAD r = road[i];
		if (find(r.e) == find(r.u)) continue;
		insert(r.u, r.e, r.v); insert(r.e, r.u, r.v);
		fa[find(r.e)] = find(r.u);
	}
}

int minth[10001][20];
int fath[10001][20], deep[10001];
void dfs1(int x,int f);
int minRoad(int x,int y);
int main(){
	scanf("%d%d", &n, &m);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &z); road[i] = ROAD{ x,y,z };
	}
	sort(road + 1, road + m + 1);
	Kruskal();
	memset(minth, 0x3f3f3f3f, sizeof minth);
	for (int i = 1; i <= n; ++i)
		if (deep[i] == 0) dfs1(i, i);
	for(int j=1;j!=20;++j)
		for (int i = 1; i <= n; ++i) {
			fath[i][j] = fath[fath[i][j - 1]][j - 1];
			minth[i][j] = min(minth[i][j - 1], minth[fath[i][j - 1]][j - 1]);
		}
	int q = 0; scanf("%d", &q);
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d", &x, &y);
		printf("%d\n", minRoad(x, y));
	}
	return 0;
}
void dfs1(int x,int f){
	fath[x][0] = f;
	deep[x] = deep[f] + 1;//如果f是自身，0+1为1
	for (int i = head[x]; i; i = nxt[i]) {
		if (to[i] != f) { 
			minth[to[i]][0] = val[i];//下放边权到点权
			dfs1(to[i], x);
		}
	}
}
int minRoad(int x,int y)
{
	if (find(x) != find(y)) return -1;
	int ans = 0x3f3f3f3f;
	if (deep[x] < deep[y]) x ^= y ^= x ^= y;
	for(int j=19;~j;--j)if (deep[fath[x][j]] >= deep[y]) {
		ans = min(ans, minth[x][j]);
		x = fath[x][j];
	}
	if (x == y) return ans;
	for(int j=19;~j;--j)
		if (fath[x][j] != fath[y][j]) {
			ans = min(ans, min(minth[x][j], minth[y][j]));
			x = fath[x][j]; y = fath[y][j];
		}
	return min(ans, min(minth[x][0], minth[y][0]));
}