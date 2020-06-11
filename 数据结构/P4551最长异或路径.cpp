#include <cstdio>
#include <queue>
void read(int &x) {
	x = 0; int c = getchar();
	while (c < '0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
}
const int maxn = 100001, bit = 30;
int n = 0;
int head[maxn], nxt[200001], to[200001], val[200001], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int fa[maxn], dis[maxn];
void bfs() {
	std::queue<int> q;
	q.push(1); fa[1] = 1; dis[1] = 0;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != fa[x]) {
				fa[to[i]] = x;
				dis[to[i]] = dis[x] ^ val[i];
				q.push(to[i]);
			}
	}
}
int son[maxn << 5][2], tc = 0;
void insert(int x) {
	int p = 0, c = 0;
	for (int i = bit; ~i; --i) {
		c = (x >> i) & 1;
		if (!son[p][c]) son[p][c] = ++tc;
		p = son[p][c];
	}
}
int query(int x) {
	x = ~x;
	int p = 0, c = 0, ans = 0;
	for (int i = bit; ~i; --i) {
		c = (x >> i) & 1;
		if (son[p][c]) {
			p = son[p][c];
			ans |= (1 << i);
		}
		else p = son[p][c ^ 1];
	}
	return ans;
}
inline int max(int a, int b) { return a < b ? b : a; }
int main() {
	read(n);
	int a = 0, b = 0, c = 0;
	for (int i = 1; i != n; ++i) {
		read(a); read(b); read(c);
		insert(a, b, c); insert(b, a, c);
	}
	bfs();
	for (int i = 1; i <= n; ++i)
		insert(dis[i]);
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = max(ans, query(dis[i]));
	printf("%d", ans);
	return 0;
}