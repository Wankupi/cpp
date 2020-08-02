#include <cstdio>
#include <cstring>
#include <queue>
using std::priority_queue;
const int maxn = 200003, maxm = 800003, maxP = maxn << 1;
inline int min(int a, int b) { return a < b ? a : b; }
inline void read(int &x) {
	x = 0;
	int c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getchar();
}
struct AdJ {
	int head[maxP], to[maxm], nxt[maxm], val[maxm], cnt;
	AdJ() { clear(); }
	void insert(int u, int e, int v) {
		nxt[++cnt] = head[u];
		head[u] = cnt;
		to[cnt] = e;
		val[cnt] = v;
	}
	void clear() {
		memset(head, 0, sizeof head);
		cnt = 0;
	}
};
struct Edge { Edge(int u, int e, int H) { x = u, y = e, height = H; } int x, y, height; };
bool operator<(const Edge &lhs, const Edge &rhs) { return lhs.height < rhs.height; }
int n = 0, m = 0, cP = 0;
AdJ gr, kt; // graph KruskalTree
int w[maxP];
priority_queue<Edge> q;
int fa[maxP];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void Kruskal() {
	cP = n;
	for (int i = 1; i <= 2 * n; ++i)
		fa[i] = i;
	while (!q.empty()) {
		Edge e = q.top();
		q.pop();
		if ((e.x = find(e.x)) == (e.y = find(e.y))) continue;
		w[++cP] = e.height;
		kt.insert(cP, e.x, 0);
		kt.insert(cP, e.y, 0);
		fa[e.x] = cP;
		fa[e.y] = cP;
	}
}
struct PoiDis { PoiDis(int point, int distance) { p = point, d = distance; } int p, d; };
inline bool operator<(const PoiDis &lhs, const PoiDis &rhs) { return lhs.d > rhs.d; }
int dis[maxn];
bool sign[maxn];
void dij() {
	memset(dis, 0x3f, sizeof dis);
	memset(sign, 0, sizeof sign);
	priority_queue<PoiDis> q;
	dis[1] = 0;
	q.push(PoiDis(1, 0));
	while (!q.empty()) {
		int x = q.top().p;
		q.pop();
		if (sign[x]) continue;
		sign[x] = true;
		for (int i = gr.head[x]; i; i = gr.nxt[i]) {
			int t = gr.to[i];
			if (dis[t] > dis[x] + gr.val[i]) {
				dis[t] = dis[x] + gr.val[i];
				q.push(PoiDis(t, dis[t]));
			}
		}
	}
}

int mV[maxP], fath[20][maxP];
void dfs(int x, int f) {
	fath[0][x] = f;
	for (int j = 1; j <= 18; ++j)
		fath[j][x] = fath[j - 1][fath[j - 1][x]];
	if (1 <= x && x <= n) mV[x] = dis[x];
	else mV[x] = 0x3f3f3f3f;
	for (int i = kt.head[x]; i; i = kt.nxt[i]) {
		dfs(kt.to[i], x);
		mV[x] = min(mV[x], mV[kt.to[i]]);
	}
}

int main() {
	int T = 0;
	read(T);
	for (int t = 1; t <= T; ++t) {
		read(n);
		read(m);
		int a = 0, b = 0, c = 0, d = 0;
		for (int i = 1; i <= m; ++i) {
			read(a);
			read(b);
			read(c);
			read(d);
			gr.insert(a, b, c);
			gr.insert(b, a, c);
			q.push(Edge(a, b, d));
		}
		dij();
		Kruskal();
		dfs(cP, cP);
		int Q = 0, K = 0, S = 0;
		read(Q); read(K); read(S);
		int v0 = 0, p0 = 0, lastAns = 0;
		for (int i = 1; i <= Q; ++i) {
			read(v0); read(p0);
			v0 = (v0 + K * lastAns - 1) % n + 1;
			p0 = (p0 + K * lastAns) % (S + 1);
			for (int j = 18; ~j; --j)
				if (w[fath[j][v0]] > p0) v0 = fath[j][v0];
			lastAns = mV[v0];
			printf("%d\n", lastAns);
		}
		gr.clear();
		kt.clear();
	}
	return 0;
}