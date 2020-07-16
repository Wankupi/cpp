#include <cstdio>
using namespace std;
int c[101], u[101];
int  out[101];
bool vis[101];
int head[101], nxt[10001], to[10001], val[10001], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int dl[101], l = 0, r = 0;
int main() {
	int n = 0, p = 0;
	scanf("%d%d", &n, &p);
	int a = 0, b = 0, v = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a, u + i);
		c[i] = (a ? a : -u[i]);
	}
	for (int i = 1; i <= p; ++i) {
		scanf("%d%d%d", &a, &b, &v);
		insert(a, b, v); out[a]++;
	}
	for (int i = 1; i <= n; ++i)
		if (c[i] > 0) dl[++r] = i, vis[i] = true;
	while (l < r) {
		int x = dl[++l];
		for (int i = head[x]; i; i = nxt[i]) {
			if ((c[to[i]] += c[x] * val[i]) > 0 && !vis[to[i]])
				dl[++r] = to[i], vis[to[i]] = true;
		}
	}
	bool flag = false;
	for (int i = 1; i <= n; ++i) {
		if (!out[i] && c[i] > 0) flag = true;
	}
	if (flag) {
		for (int i = 1; i <= n; ++i)
			if (!out[i] && c[i] > 0)
				printf("%d %d\n", i, c[i]);
	}
	else printf("NULL");
	return 0;
}