#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n = 0, m = 0;
int a[101][11];
int dis[1100];
bool inQ[1100];
int All1 = 0;
unsigned Use(unsigned s, int t) { // for state s, use mutton t
	for (int j = 0; j < n; ++j) {
		if (a[t][j] == 1)
			s &= (All1 ^ (1 << j));
		else if (a[t][j] == -1)
			s |= (1 << j);
	}
	return s;
}
int bfs() {
	memset(dis, 0x3f, sizeof(dis));
	dis[All1] = 0;
	queue<unsigned> q;
	q.push(All1);
	while (!q.empty()) {
		unsigned x = q.front();
		q.pop();
		for (int i = 1; i <= m; ++i) {
			unsigned to = Use(x, i);
			if (dis[to] > dis[x] + 1) {
				dis[to] = dis[x] + 1;
				if (!inQ[to]) {
					q.push(to);
					inQ[to] = true;
				}
			}
		}
		inQ[x] = false;
	}
	return dis[0] == 0x3f3f3f3f ? -1 : dis[0];
}
int main() {
	scanf("%d%d", &n, &m);
	All1 = (1 << n) - 1;
	for (int i = 1; i <= m; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%d", &a[i][j]);
	printf("%d", bfs());
	return 0;
}