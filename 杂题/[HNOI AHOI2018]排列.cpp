#include <cstdio>
#include <set>
using namespace std;
const int maxn = 500003;
int n = 0;
int a[maxn], w[maxn];
int head[maxn], nxt[maxn], to[maxn], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
bool vis[maxn], circle = false;
int visited = 0;
void dfs(int x) {
	vis[x] = true;
	++visited;
	for (int i = head[x]; i; i = nxt[i]) {
		if (vis[to[i]])
			circle = true;
		else
			dfs(to[i]);
		if (circle) return;
	}
}
long long W[maxn], sumW[maxn];
int siz[maxn];
struct Node {
	Node(int Id, long double v) { id = Id; Val = v; }
	int id;
	long double Val;
};
inline bool operator<(const Node &lhs, const Node &rhs) { return lhs.Val < rhs.Val; }
multiset<Node> s;
multiset<Node>::iterator it[maxn];
int fa[maxn];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = 1; i <= n; ++i)
		scanf("%d", w + i);
	for (int i = 1; i <= n; ++i)
		insert(a[i], i);
	dfs(0);
	if (circle || visited <= n) {
		printf("-1");
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		siz[i] = 1;
		sumW[i] = W[i] = w[i];
		it[i] = s.insert(Node(i, W[i] / 1.0));
	}
	long long ans = 0;
	siz[0] = 1;
	while(!s.empty()) {
		int x = s.begin()->id;
		int F = fa[x] = find(a[x]);
		s.erase(s.begin());
		if(F) s.erase(it[F]);
		ans += W[x] * siz[F];
		W[F] += W[x];
		siz[F] += siz[x];
		if (F) it[F] = s.insert(Node(F, (long double)(W[F]) / (long double)(siz[F])));
	}
	printf("%lld", ans);
	return 0;
}