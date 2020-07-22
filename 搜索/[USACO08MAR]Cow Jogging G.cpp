#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n = 0, m = 0, k = 0;
int head[1001], nxt[10003], to[10003], val[10003], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int head2[1001], nxt2[10003], to2[10003], val2[10003], cnt2 = 0;
inline void insert2(int u, int e, int v) { nxt2[++cnt2] = head2[u]; head2[u] = cnt2; to2[cnt2] = e; val2[cnt2] = v; }

int dis[1001], in[1001];
void spfa() {
	memset(dis, 0x3f, sizeof dis);
	dis[1] = 0;
	queue<int> q;
	q.push(1); in[1] = true;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		in[x] = false;
		for (int i = head2[x]; i; i = nxt2[i]) {
			int y = to2[i];
			if (dis[y] > dis[x] + val2[i]) {
				dis[y] = dis[x] + val2[i];
				if (!in[y]) {
					q.push(y);
					in[y] = true;
				}
			}
		}
	}
}
struct State {
	State(int point, int distance) { t = point; h = distance; }
	int t;
	int h;
};
inline bool operator<(const State &lhs, const State &rhs) { return dis[lhs.t] + lhs.h > dis[rhs.t] + rhs.h; }
int res[120], CNT = 0;
void bfs() {
	priority_queue<State> p;
	p.push(State(n, 0));
	while (!p.empty() && CNT < k) {
		State s = p.top(); p.pop();
		if (s.t == 1)
			res[++CNT] = s.h;
		for (int i = head[s.t]; i; i = nxt[i])
			p.push(State(to[i], s.h + val[i]));
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		insert(x, y, z);
		insert2(y, x, z);
	}
	spfa();
	bfs();
	for (int i = 1; i <= CNT; ++i)
		printf("%d\n", res[i]);
	for (int i = CNT + 1; i <= k; ++i) printf("-1\n");
	return 0;
}