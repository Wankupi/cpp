#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
int const maxn = 5003, maxm = 200003;
int n = 0, m = 0;
double E = 0;
struct Graph {
	int head[maxn], nxt[maxm], from[maxm], to[maxm], cnt;
	double val[maxm];
	inline void insert(int u, int e, double v) { nxt[++cnt] = head[u]; head[u] = cnt; from[cnt] = u; to[cnt] = e; val[cnt] = v; }
};
Graph z, f;
int fa[maxn];
double dis[maxn];
bool confirm[maxn];
struct Distance {
	Distance(int Iden, double Length) : id(Iden), d(Length) {}
	int id;
	double d;
};
bool operator<(const Distance &lhs, const Distance &rhs) { return lhs.d > rhs.d; }
void dij() {
	for (int i = 1; i <= n; ++i)
		dis[i] = 1e20;
	dis[n] = 0;
	priority_queue<Distance> q;
	q.push(Distance(n, 0));
	while (!q.empty()) {
		int x = q.top().id;
		q.pop();
		if (confirm[x]) continue;
		confirm[x] = true;
		for (int i = f.head[x]; i; i = f.nxt[i])
			if (dis[f.to[i]] > dis[x] + f.val[i]) {
				dis[f.to[i]] = dis[x] + f.val[i];
				fa[f.to[i]] = i;
				q.push(Distance(f.to[i], dis[f.to[i]]));
			}
	}
}

struct Node {
	int i;
	int son[2], dist;
	double key() const { return dis[z.to[i]] - dis[z.from[i]] + z.val[i]; }
};
Node heap[maxm * 21];
int cnt_heap;
int merge_simple(int x, int y) {
	if (x == 0 || y == 0) return x | y;
	if (heap[x].key() > heap[y].key()) std::swap(x, y);
	heap[x].son[1] = merge_simple(heap[x].son[1], y);
	if (heap[heap[x].son[0]].dist < heap[heap[x].son[1]].dist) std::swap(heap[x].son[0], heap[x].son[1]);
	heap[x].dist = heap[heap[x].son[1]].dist + 1;
	return x;
}
int merge_persistent(int x, int y) {
	if (x == 0 || y == 0) return x | y;
	if (heap[x].key() > heap[y].key()) std::swap(x, y);
	int k = ++cnt_heap;
	heap[k] = heap[x];
	heap[k].son[1] = merge_persistent(heap[k].son[1], y);
	if (heap[heap[k].son[0]].dist < heap[heap[k].son[1]].dist) std::swap(heap[k].son[0], heap[k].son[1]);
	heap[k].dist = heap[heap[k].son[1]].dist + 1;
	return k;
}
int tr_per[maxn]; // tree permutation
inline bool cmp1(int a, int b) { return dis[a] < dis[b]; }
int root[maxn];
int main() {
	scanf("%d %d %lf", &n, &m, &E);
	int x = 0, y = 0;
	double v = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %lf", &x, &y, &v);
		if (x == n) {
			--i;
			--m;
			continue;
		}
		z.insert(x, y, v);
		f.insert(y, x, v);
	}
	dij();
	for (int i = 1; i <= n; ++i)
		tr_per[i] = i;
	sort(tr_per + 1, tr_per + n + 1, cmp1);
	cnt_heap = m;
	for (int i = 1; i <= m; ++i) {
		heap[i].i = i;
		heap[i].dist = 1;
	}
	for (int i = 1; i <= n; ++i) {
		x = tr_per[i];
		for (int j = z.head[x]; j; j = z.nxt[j])
			if (j != fa[x])
				root[x] = merge_simple(root[x], j);
		if (fa[x]) root[x] = merge_persistent(root[x], root[z.to[fa[x]]]);
	}
	int ans = 1;
	double left = E - dis[1];
	priority_queue<Distance> q;
	q.push(Distance(root[1], dis[1] + heap[root[1]].key()));
	while (!q.empty()) {
		Distance x = q.top();
		q.pop();
		if (x.d <= left) {
			left -= x.d;
			++ans;
		}
		else break;
		Node const &H = heap[x.id];
		if (root[z.to[H.i]])
			q.push(Distance(root[z.to[H.i]], x.d + heap[root[z.to[H.i]]].key()));
		if (H.son[0])
			q.push(Distance(H.son[0], x.d - H.key() + heap[H.son[0]].key()));
		if (H.son[1])
			q.push(Distance(H.son[1], x.d - H.key() + heap[H.son[1]].key()));
	}
	printf("%d\n", ans);
	return 0;
}