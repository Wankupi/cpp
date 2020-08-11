#include <cstdio>
#include <cstring>
#include <queue>
int n = 0, k = 0;
int boy[53][2], girl[53][2], S = 0, T = 0, cPoint = 0;
char like[53][53];
int head[250], nxt[6000], to[6000], val[6000], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
inline int min(int a, int b) { return a < b ? a : b; }
int dep[250], cur[250];
bool bfs() {
	memset(dep, 0, sizeof dep);
	memcpy(cur, head, sizeof head);
	std::queue<int> q;
	dep[S] = 1;
	q.push(S);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (!dep[to[i]] && val[i]) {
				dep[to[i]] = dep[x] + 1;
				if (to[i] == T) return true;
				q.push(to[i]);
			}
	}
	return false;
}
int dfs(int x, int flow) {
	if (x == T) return flow;
	int use = 0;
	for (int i = cur[x]; i && use < flow; i = nxt[i]) {
		cur[x] = i;
		if (dep[to[i]] == dep[x] + 1 && val[i]) {
			int d = dfs(to[i], min(flow - use, val[i]));
			use += d;
			val[i] -= d;
			val[i ^ 1] += d;
		}
	}
	if (use < flow) dep[x] = 0;
	return use;
}
inline int dinic() {
	int sum = 0;
	while (bfs())
		sum += dfs(S, 0x3f3f3f3f);
	return sum;
}
bool check(int a) {
	memset(head, 0, sizeof head);
	cnt = 1;
	for (int i = 1; i <= n; ++i) {
		insert(S, boy[i][0], a);
		insert(boy[i][0], S, 0);
		insert(boy[i][0], boy[i][1], k);
		insert(boy[i][1], boy[i][0], 0);
		insert(girl[i][0], T, a);
		insert(T, girl[i][0], 0);
		insert(girl[i][1], girl[i][0], k);
		insert(girl[i][0], girl[i][1], 0);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int r = (like[i][j] != 'Y');
			insert(boy[i][r], girl[j][r], 1);
			insert(girl[j][r], boy[i][r], 0);
		}
	}
	return dinic() == a * n;
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%s", like[i] + 1);
	S = 0;
	for (int i = 1; i <= n; ++i) { boy[i][0] = ++cPoint; boy[i][1] = ++cPoint; }
	for (int i = 1; i <= n; ++i) { girl[i][0] = ++cPoint; girl[i][1] = ++cPoint; }
	T = ++cPoint;
	int L = 0, R = n, mid = 0, ans = 0;
	while (L <= R) {
		mid = (L + R) >> 1;
		if (check(mid)) { ans = mid, L = mid + 1; }
		else R = mid - 1;
	}
	printf("%d", ans);
	return 0;
}