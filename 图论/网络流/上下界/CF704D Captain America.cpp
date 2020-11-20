#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;
int const maxn = 200007, maxm = 1000007, inf = 0x7fffffff;
int n = 0, m = 0, s = 0, t = 0, S = 0, T = 0;
int R = 0, B = 0, changed = 0;
map<int, int> NumX, NumY;
int cId = 0;
int mi[maxn], cnt[maxn], edId[maxn];
int need[maxn];
bool isY[maxn];

int head[maxn], nxt[maxm], to[maxm], val[maxm], cntEdge = 1;
inline void insert(int u, int e, int v) { nxt[++cntEdge] = head[u]; head[u] = cntEdge; to[cntEdge] = e; val[cntEdge] = v; /*printf("%d %d %d\n", u, e, v);*/ }
inline void insert2(int u, int e, int v) { insert(u, e, v); insert(e, u, 0); }
inline void insertLR(int u, int e, int l, int r) {
	need[u] -= l; need[e] += l;
	insert2(u, e, r - l);
}

int dep[maxn], cur[maxn];
bool bfs(int _s, int aim) {
	memset(dep, 0, sizeof dep);
	memcpy(cur, head, sizeof cur);
	queue<int> q;
	dep[_s] = 1;
	q.push(_s);
	while (q.size()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (dep[to[i]] == 0 && val[i] > 0) {
				dep[to[i]] = dep[x] + 1;
				if (to[i] == aim) return true;
				q.push(to[i]);
			}
	}
	return false;
}
int dfs(int x, int flow, int aim) {
	if (x == aim)  return flow;
	int use = 0;
	for (int i = cur[x]; i && use < flow; i = nxt[i]) {
		cur[x] = i;
		if (dep[to[i]] == dep[x] + 1 && val[i] > 0) {
			int k = dfs(to[i], std::min(flow - use, val[i]), aim);
			use += k;
			val[i] -= k;
			val[i ^ 1] += k;
		}
	}
	if (use < flow) dep[x] = 0;
	return use;
}
inline int dinic(int _S, int _T) {
	int sum = 0;
	while (bfs(_S, _T))
		sum += dfs(_S, inf, _T);
	return sum;
}
int main() {
	scanf("%d %d", &n, &m);
	scanf("%d %d", &R, &B);
	if (R > B) { std::swap(R, B); changed = 1; }
	for (int i = 1; i <= n; ++i) {
		int x = 0, y = 0;
		scanf("%d %d", &x, &y);
		if (!NumX[x]) { NumX[x] = ++cId; mi[cId] = inf; }
		if (!NumY[y]) { NumY[y] = ++cId; mi[cId] = inf; isY[cId] = true; }
		++cnt[NumX[x]];
		++cnt[NumY[y]];
		insert2(NumX[x], NumY[y], 1);
		edId[i] = cntEdge;
	}
	for (int i = 1; i <= m; ++i) {
		int t = 0, l = 0, d = 0;
		scanf("%d %d %d", &t, &l, &d);
		if (t == 1) {
			int x = NumX[l];
			if (x != 0) mi[x] = std::min(mi[x], d);
		}
		else {
			int y = NumY[l];
			if (y != 0) mi[y] = std::min(mi[y], d);
		}
	}
	s = cId + 1; t = s + 1; S = 0; T = t + 1;
	for (int i = 1; i <= cId; ++i) {
		int c = cnt[i], d = std::min(mi[i], cnt[i]);
		int l = (c - d + 1) / 2, r = (c + d) >> 1;
		if (l > r) { puts("-1"); return 0; }
		if (isY[i]) insertLR(i, t, l, r);
		else insertLR(s, i, l, r);
	}
	int tot = 0;
	for (int i = 1; i <= t; ++i) {
		if (need[i] < 0) insert2(i, T, -need[i]);
		else if (need[i] > 0) { insert2(S, i, need[i]); tot += need[i]; }
	}
	insert2(t, s, inf);

	if (dinic(S, T) != tot) {
		puts("-1"); return 0;
	}
	long long ans = dinic(s, t);
	printf("%lld\n", ans * R + (n - ans) * B);
	for (int i = 1; i <= n; ++i) {
		putchar((val[edId[i]] ^ changed) ? 'r' : 'b');
	}
	return 0;
}