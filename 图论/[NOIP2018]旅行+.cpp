#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 500003;
int n = 0, m = 0;
int from[maxn << 1], to[maxn << 1];
vector<int> G[maxn];
int p[maxn], cur = 0;
void dfs(int x, int fa) {
	p[++cur] = x;
	for (auto i : G[x]) {
		if (i[to] == fa) continue;
		dfs(to[i], x);
	}
}
int d[maxn];
void topu() {
	queue<int> q;
	for (int i = 1; i <= n; ++i)
		if (d[i] == 1) q.push(i);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (auto i : G[x])
			if (--d[to[i]] == 1)
				q.push(to[i]);
	}
}
bool vis[maxn], back = false;
int minUse = 0x7fffffff;
void dfs2(int x) {
	p[++cur] = x;
	vis[x] = true;
	if (d[x] >= 2 && !back) {
		bool flag = false;
		for (unsigned i = 0; i < G[x].size(); ++i) {
			int y = to[G[x][i]];
			if (vis[y]) continue;
			if (d[y] < 2) continue;
			unsigned int nxt = i + 1;
			while (nxt < G[x].size() && vis[to[G[x][nxt]]])
				++nxt;
			if (nxt == G[x].size() && y > minUse) {
				flag = back = true;
				break;
			}
			else if (nxt < G[x].size())
				minUse = to[G[x][nxt]];
			break;
		}
		for (auto i : G[x]) {
			int y = to[i];
			if (vis[y]) continue;
			if (d[y] >= 2 && flag) continue;
			dfs2(y);
		}
	}
	else
		for (auto i : G[x])
			if (!vis[to[i]]) dfs2(to[i]);
}
int main() {
	scanf("%d%d", &n, &m);
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		from[2 * i] = x;
		to[2 * i] = y;
		G[x].push_back(2 * i);
		from[2 * i + 1] = y;
		to[2 * i + 1] = x;
		G[y].push_back(2 * i + 1);
		++d[x];
		++d[y];
	}
	for (int i = 1; i <= n; ++i)
		sort(G[i].begin(), G[i].end(), [](int a, int b) { return to[a] < to[b]; });
	if (m == n - 1)
		dfs(1, 0);
	else {
		topu();
		dfs2(1);
	}
	for (int i = 1; i <= n; ++i)
		printf("%d ", p[i]);
	return 0;
}