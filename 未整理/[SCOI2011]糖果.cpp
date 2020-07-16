#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 100010;
int n = 0, k = 0;
int head[maxn], nxt[maxn * 3], to[maxn * 3], val[maxn * 3], cnt = 0;
inline void insert(int u, int e, int v) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
	val[cnt] = v;
}
bool in[maxn];
int t[maxn], dis[maxn];
bool spfa() {
	queue<int> q;
	dis[0] = 0;
	q.push(0);
	t[0]++; in[0] = 1;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (dis[x] + val[i] > dis[to[i]]) {
				dis[to[i]] = dis[x] + val[i];
				if (!in[to[i]]) {
					q.push(to[i]);
					in[to[i]] = true;
				}
				if (++t[to[i]] > n) return false;
			}
		in[x] = false;
	}
	return true;
}
int main() {
	freopen("test.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d%d", &n, &k);
	int x = 0, a = 0, b = 0;
	for (int i = 1; i <= k; ++i) {
		scanf("%d%d%d", &x, &a, &b);
		if (a == b && x != 1 && x != 3 && x != 5) { printf("-1"); return 0; }
		if (x == 1) {
			insert(a, b, 0);
			insert(b, a, 0);
		}
		else if (x == 2) insert(a, b, 1);
		else if (x == 3) insert(b, a, 0);
		else if (x == 4) insert(b, a, 1);
		else if (x == 5) insert(a, b, 0);
	}
	for (int i = n; i >= 1; --i) insert(0, i, 1);
	if (spfa()) {
		long long sum = 0;
		for (int i = 1; i <= n; ++i) sum += dis[i];
		printf("%lld", sum);
	}
	else printf("-1");
	return 0;
}