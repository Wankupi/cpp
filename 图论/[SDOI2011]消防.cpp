#include <cstdio>
#include <algorithm>

int const maxn = 300003;

int n = 0, s = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 1;
inline void insert(int u, int e, int v) {
	nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v;
}

int dis[maxn], mx[maxn], from[maxn];
void dfs(int x, int fa) {
	mx[x] = x;
	from[x] = fa;
	for (int i = head[x]; i; i = nxt[i]) {
		if (to[i] == fa) continue;
		dis[to[i]] = dis[x] + val[i];
		dfs(to[i], x);
		if (dis[mx[to[i]]] > dis[mx[x]])
			mx[x] = mx[to[i]];
	}
}

int p[maxn], cntP = 0;
int suf[maxn], pre[maxn];

void getChain(int x, int son) {
	mx[x] = 0;
	for (int i = head[x]; i; i = nxt[i]) {
		if (to[i] == from[x] || to[i] == son) continue;
		if (dis[mx[to[i]]] - dis[x] > mx[x])
			mx[x] = dis[mx[to[i]]] - dis[x];
	}
	if (from[x]) getChain(from[x], x);
	p[++cntP] = x;
}

int que[maxn], qV[maxn], ql = 1, qr = 0;
inline void add(int pos, int val) {
	while (ql <= qr && qV[qr] <= val) --qr;
	++qr;
	que[qr] = pos;
	qV[qr] = val;
}
inline int query(int pos) {
	while (ql <= qr && que[ql] < pos) ++ql;
	return qV[ql];
}

int main() {
	scanf("%d %d", &n, &s);
	for (int i = 1; i < n; ++i) {
		int x = 0, y = 0, z = 0;
		scanf("%d %d %d", &x, &y, &z);
		insert(x, y, z);
		insert(y, x, z);
	}
	dfs(1, 0);
	int p1 = mx[1];
	from[p1] = dis[p1] = 0;
	dfs(p1, 0);

	int p2 = mx[p1];
	getChain(p2, p2);

	for (int i = 1; i <= cntP; ++i)
		pre[i] = std::max(mx[p[i]] + (-dis[p[i]]), pre[i - 1]);
	
	for (int i = cntP; i >= 1; --i)
		suf[i] = std::max(mx[p[i]] + dis[p[i]], suf[i + 1]);

	int ans = 0x7fffffff;
	for (int l = 1, r = 0; l <= cntP; ++l) {
		while (r < cntP && dis[p[r + 1]] - dis[p[l]] <= s) {
			++r;
			add(r, mx[p[r]]);
		}
		int t = query(l);
		t = std::max(t, std::max(pre[l] + dis[p[l]], suf[r] - dis[p[r]]));
		t = std::max(t, std::max(dis[p[l]], dis[p[cntP]] - dis[p[r]]));
		ans = std::min(ans, t);
	}
	printf("%d\n", ans);
	return 0;
}
