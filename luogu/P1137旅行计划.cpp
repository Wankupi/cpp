#include <cstdio>
#include <queue>
using namespace std;
int head[100001], nxt[200001], to[200001], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int in[100001], step[100001];
inline int max(int a, int b) { return a > b ? a : b; }
int main() {
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		insert(x, y);
		++in[y];
	}
	queue<int> q;
	for (int i = 1; i <= n; ++i)
		if (!in[i])
			q.push(i), step[i] = 1;
	while (!q.empty()) {
		x = q.front();
		q.pop();
		for (int i = head[x]; i; i = nxt[i]) {
			step[to[i]] = max(step[to[i]], step[x] + 1);
			if (--in[to[i]] == 0)
				q.push(to[i]);
		}
	}
	for (int i = 1; i <= n; ++i)
		printf("%d\n", step[i]);
	return 0;
}