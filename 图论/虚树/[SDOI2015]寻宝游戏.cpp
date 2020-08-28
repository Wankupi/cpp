#include <cstdio>
#include <set>
using namespace std;
int const maxn = 100003;
int n = 0, m = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 0;
inline void insert(int u, int e, int v) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
	val[cnt] = v;
}
int dfn[maxn], cDfn = 0;
int siz[maxn], fa[maxn], son[maxn], top[maxn], dep[maxn];
long long dis[maxn];
void dfs1(int x, int f) {
	fa[x] = f;
	siz[x] = 1;
	dep[x] = dep[f] + 1;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dis[to[i]] = dis[x] + val[i];
			dfs1(to[i], x);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
		}
}
void dfs2(int x, int t) {
	dfn[x] = ++cDfn;
	top[x] = t;
	if (son[x]) dfs2(son[x], t);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x] && to[i] != son[x])
			dfs2(to[i], to[i]);
}
inline int lca(int x, int y) {
	while (top[x] != top[y])
		dep[top[x]] > dep[top[y]] ? (x = fa[top[x]]) : (y = fa[top[y]]);
	return dep[x] < dep[y] ? x : y;
}
inline long long Distantce(int x, int y) {
	return dis[x] + dis[y] - 2 * dis[lca(x, y)];
}
struct Node {
	Node(int x) { id = x; }
	int id;
};
inline bool operator<(const Node &lhs, const Node &rhs) { return dfn[lhs.id] < dfn[rhs.id]; }

set<Node> s;
long long ans = 0;
void add(int x) {
	set<Node>::iterator cur = s.insert(Node(x)).first;
	set<Node>::iterator pre = cur, nx = cur;
	if (pre == s.begin())
		pre = s.end();
	--pre;
	if (++nx == s.end())
		nx = s.begin();
	ans += Distantce(pre->id, x) + Distantce(x, nx->id) - Distantce(pre->id, nx->id);
}
void del(int x) {
	set<Node>::iterator cur = s.find(Node(x));
	set<Node>::iterator pre = cur, nx = cur;
	if (pre == s.begin())
		pre = s.end();
	--pre;
	if (++nx == s.end())
		nx = s.begin();
	ans -= Distantce(pre->id, x) + Distantce(x, nx->id) - Distantce(pre->id, nx->id);
	s.erase(cur);
}
bool in[maxn];
int main() {
	scanf("%d %d", &n, &m);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		insert(x, y, z);
		insert(y, x, z);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &x);
		if (in[x] == false) {
			add(x);
			in[x] = true;
		}
		else {
			del(x);
			in[x] = false;
		}
		printf("%lld\n", ans);
	}
	return 0;
}