#include <cstdio>
const int maxn = 400003;
int n = 0, m = 0;
int head[maxn], nxt[maxn], to[maxn], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int fa[maxn], P = 0;
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) { fa[find(x)] = find(y); }
int k = 0, d[maxn], ans[maxn];
bool del[maxn];
int main() {
	scanf("%d%d", &n, &m);
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		insert(x + 1, y + 1);
		insert(y + 1, x + 1);
	}
	scanf("%d", &k);
	for (int i = 1; i <= k; ++i) {
		scanf("%d", d + i);
		++d[i];
		del[d[i]] = true;
	}
	P = n - k;
	for (int i = 1; i <= n; ++i)
		fa[i] = i;
	for (int x = 1; x <= n; ++x)
		for (int i = head[x]; i; i = nxt[i])
			if (!del[x] && !del[to[i]] && find(x) != find(to[i])) {
				merge(x, to[i]);
				--P;
			}
	for (int j = k; j; --j) {
		ans[j] = P;
		int x = d[j];
		del[x] = false; ++P;
		for (int i = head[x]; i; i = nxt[i])
			if (del[to[i]] == false && find(x) != find(to[i])) {
				merge(x, to[i]);
				--P;
			}
	}
	printf("%d\n", P);
	for (int i = 1; i <= k; ++i) printf("%d\n", ans[i]);
	return 0;
}