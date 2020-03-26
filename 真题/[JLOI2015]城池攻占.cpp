#include <cstdio>
typedef long long ll;
const int maxn = 300005;
int n = 0, m = 0;
int beg[maxn];
ll force[maxn], defense[maxn];
int PointAns[maxn], genPopPoint[maxn];
inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
namespace Heap {
	int son[maxn][2], dis[maxn];
	ll tplus[maxn], tmuti[maxn];
	void init() {
		dis[0] = -1;
		for (int i = 1; i <= m; ++i) {
			son[i][0] = son[i][1] = 0;
			dis[i] = 0;
			tplus[i] = 0; tmuti[i] = 1;
		}
	}
	inline void plusTag(int rt, ll p, ll m) {
		if (rt == 0) return;
		force[rt] = force[rt] * m + p;
		tmuti[rt] *= m;
		tplus[rt] = tplus[rt] * m + p;
	}
	inline void pushDown(int rt) {
		plusTag(son[rt][0], tplus[rt], tmuti[rt]);
		plusTag(son[rt][1], tplus[rt], tmuti[rt]);
		tplus[rt] = 0; tmuti[rt] = 1;
	}
	int merge(int x, int y) {
		if (x == 0 || y == 0) return x + y;
		pushDown(x); pushDown(y);
		if (force[x] > force[y]) swap(x, y);
		son[x][1] = merge(son[x][1], y);
		if (son[x][0] == 0 || dis[son[x][0]] < dis[son[x][1]])
			swap(son[x][0], son[x][1]);
		dis[x] = dis[son[x][1]] + 1;
		return x;
	}
	int pop(int rt, int point) { //pop all that less than val, return the new root
		while (rt && force[rt] < defense[point]) {
			genPopPoint[rt] = point;
			++PointAns[point];
			pushDown(rt);
			int nrot = merge(son[rt][0], son[rt][1]);
			son[rt][0] = son[rt][1] = 0;
			rt = nrot;
		}
		return rt;
	}
};
int head[maxn], nxt[maxn], to[maxn], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
ll pl[maxn], mu[maxn];
int top[maxn], dep[maxn];
void dfs(int x) {
	for (int i = head[x]; i; i = nxt[i]) {
		dep[to[i]] = dep[x] + 1;
		dfs(to[i]);
		top[x] = Heap::merge(top[x], top[to[i]]);
	}
	top[x] = Heap::pop(top[x], x);
	Heap::plusTag(top[x], pl[x], mu[x]);
}
int main() {
	scanf("%d %d", &n, &m);
	Heap::init();
	for (int i = 1; i <= n; ++i) scanf("%lld", defense + i);
	int f = 0, a = 0;
	ll v = 0;
	for (int i = 2; i <= n; ++i) {
		scanf("%d %d %lld", &f, &a, &v);
		insert(f, i);
		pl[i] = (a == 0 ? v : 0);
		mu[i] = (a == 1 ? v : 1);
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%lld %d", &v, &a);
		force[i] = v;
		beg[i] = a;
		top[a] = Heap::merge(top[a], i); // top[a]==0 is also ok
	}
	dep[1] = 1;
	dfs(1);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", PointAns[i]);
	for (int i = 1; i <= m; ++i)
		printf("%d\n", dep[beg[i]] - dep[genPopPoint[i]]);
	return 0;
}