#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;

int const maxn = 100003, maxm = 1000003;

struct Edge {
	int x, y, v;
};

int n = 0, m = 0;
int h[maxn];
Edge li[maxm];

inline bool operator<(Edge const &lhs, Edge const &rhs) {
	return h[lhs.y] != h[rhs.y] ? h[lhs.y] > h[rhs.y] : lhs.v < rhs.v;
}

int head[maxn], nxt[maxm << 1], to[maxm << 1], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}

bool vis[maxn];
void bfs() {
	queue<int> q;
	q.push(1);
	vis[1] = true;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (!vis[to[i]]) {
				vis[to[i]] = true;
				q.push(to[i]);
			}
	}
}

int fa[maxn], siz[maxn];
long long sum;

inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

inline void merge(int x, int y, int cost) {
	x = find(x);
	y = find(y);
	if (x == y) return;
	if (siz[x] < siz[y]) swap(x, y);
	fa[y] = x;
	siz[x] += siz[y];
	sum += cost;
}

int main() {
	freopen("1.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", h + i);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &li[i].x, &li[i].y, &li[i].v);
		if (h[li[i].x] < h[li[i].y]) swap(li[i].x, li[i].y);
		if (h[li[i].x] >= h[li[i].y]) insert(li[i].x, li[i].y);
		if (h[li[i].y] >= h[li[i].x]) insert(li[i].y, li[i].x);
	}
	bfs();
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		siz[i] = 1;
	}
	sort(li + 1, li + m + 1);
	for (int i = 1; i <= m; ++i) {
		int x = li[i].x, y = li[i].y;
		if (!vis[x] || !vis[y]) continue;
		merge(x, y, li[i].v);
	}
	printf("%d %lld", siz[find(1)], sum);
	return 0;
}