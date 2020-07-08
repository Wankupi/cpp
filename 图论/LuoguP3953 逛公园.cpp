/*
求每个点的最短路长

判断在最（次）短路上： 正距离 + 反距离 <= 最短路 + K

路径条数： 对 次短路构成的图 进行 拓扑序dp
判零环：在次短路图上的零环

正边也可构成环

*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
void read(int &x) {
	x = 0; int c = getchar(), f = 1;
	while (c < '0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	x *= f;
}
const int maxn = 100001, maxm = 200001;
int n = 0, m = 0, k = 0, mod = 0;
int head[maxn], nxt[maxm], to[maxm], val[maxm], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int head2[maxn], nxt2[maxm], to2[maxm], val2[maxm], cnt2 = 0; // 反图
inline void insert2(int u, int e, int v) { nxt2[++cnt2] = head2[u]; head2[u] = cnt2; to2[cnt2] = e; val2[cnt2] = v; }

bool sign[maxn], vis[maxn];
bool haveZeroLine[maxn];
struct toT {
	toT(int T, int D) { t = T; d = D; }
	int t, d;
	friend bool operator<(const toT&lh, const toT &rh) { return lh.d > rh.d; }
};
int dis[maxn];
int dis2[maxn];
int d[maxn], dep[maxn];

void dijkstra() {
	memset(sign, 0, sizeof(sign));
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	priority_queue<toT> p;
	for (int i = head[1]; i; i = nxt[i]) {
		dis[to[i]] = val[i];
		p.push(toT(to[i], val[i]));
	}
	while (!p.empty()) {
		toT x = p.top(); p.pop();
		if (sign[x.t]) continue;
		sign[x.t] = true;
		for (int i = head[x.t]; i; i = nxt[i])
			if (dis[to[i]] > dis[x.t] + val[i]) {
				dis[to[i]] = dis[x.t] + val[i];
				p.push(toT(to[i], dis[to[i]]));
			}
	}
}
void dijkstraFan() {
	memset(sign, 0, sizeof(sign));
	memset(dis2, 0x3f, sizeof(dis2));
	dis2[n] = 0;
	priority_queue<toT> p;
	for (int i = head2[n]; i; i = nxt2[i]) {
		dis2[to2[i]] = val2[i];
		p.push(toT(to2[i], val2[i]));
	}
	while (!p.empty()) {
		toT x = p.top(); p.pop();
		if (sign[x.t]) continue;
		sign[x.t] = true;
		for (int i = head2[x.t]; i; i = nxt2[i])
			if (dis2[to2[i]] > dis2[x.t] + val2[i]) {
				dis2[to2[i]] = dis2[x.t] + val2[i];
				p.push(toT(to2[i], dis2[to2[i]]));
			}
	}
}
inline bool inRoad(int x) { return dis[x] + dis2[x] <= dis[n] + k; } // x点是否在次短路图上
bool ToPu() { // 对存0边的点进行拓扑
	memset(sign, 0, sizeof(sign));
	for (int x = 1; x <= n; ++x)
		if (inRoad(x) && haveZeroLine[x])
			for (int i = head[x]; i; i = nxt[i])
				if (val[i] == 0 && haveZeroLine[to[i]])
					++d[to[i]];
	queue<int> q;
	for (int x = 1; x <= n; ++x)
		if (inRoad(x) && haveZeroLine[x] && d[x] == 0) q.push(x);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (val[i] == 0) {
				if (dep[x] + 1 > dep[to[i]]) dep[to[i]] = dep[x] + 1;
				if (haveZeroLine[to[i]] && --d[to[i]] == 0) q.push(to[i]);
			}
	}
	for (int i = 1; i <= n; ++i) if (d[i] > 0) return false;
	return true;
}

int dp[maxn][53];
int xv[maxn], ri = 0;
inline bool cmp(int a, int b) { return dis[a] == dis[b] ? dep[a] < dep[b] : dis[a] < dis[b]; }
void clear() {
	memset(head, 0, sizeof head);
	memset(head2, 0, sizeof head2);
	memset(haveZeroLine, 0, sizeof haveZeroLine);
	memset(d, 0, sizeof d);
	memset(dep, 0, sizeof dep);
	memset(dp, 0, sizeof dp);
	cnt = cnt2 = 0;
	ri = 0;
}
int main() {
	int T = 0;
	read(T);
	for (int t = 1; t <= T; ++t, clear()) {
		read(n); read(m); read(k); read(mod);
		int x = 0, y = 0, z = 0;
		for (int i = 1; i <= m; ++i) {
			read(x); read(y); read(z);
			insert(x, y, z);
			insert2(y, x, z);
		}
		dijkstra();
		dijkstraFan();
		//删图
		for (int x = 1; x <= n; ++x)
			if (inRoad(x)) {
				while (head[x] && !inRoad(to[head[x]]))
					head[x] = nxt[head[x]];
				for (int i = head[x]; i; i = nxt[i]) {
					while (nxt[i] && !inRoad(to[nxt[i]]))
						nxt[i] = nxt[nxt[i]];
					if (val[i] == 0) haveZeroLine[x] = true;
				}
			}
		if (!ToPu()) {
			printf("-1\n");
			continue;
		}
		for (int i = 1; i <= n; ++i) if (inRoad(i)) xv[++ri] = i;
		sort(xv + 1, xv + ri + 1, cmp);
		dp[1][0] = 1;
		for (int ce = 0; ce <= k; ++ce)
			for (int p = 1; p <= ri; ++p) {
				int x = xv[p];
				for (int i = head[x]; i; i = nxt[i])
					if (dis[x] + val[i] + ce - dis[to[i]] <= k)
						(dp[to[i]][dis[x] + val[i] + ce - dis[to[i]]] += dp[x][ce]) %= mod;
			}
		int sum = 0;
		for (int j = 0; j <= k; ++j) sum = (sum + dp[n][j]) % mod;
		printf("%d\n", sum);
	}
	return 0;
}
