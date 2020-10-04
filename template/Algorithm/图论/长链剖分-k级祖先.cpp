#include <cstdio>
int const maxn = 500003;
int n = 0, q = 0;
int root = 0;
int head[maxn], nxt[maxn], to[maxn], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int fa[19][maxn];
int dep[maxn], len[maxn], son[maxn], top[maxn];
int dfn[maxn], cdfn = 0;
int up[maxn], down[maxn];
void dfs1(int x) {
	dep[x] = dep[fa[0][x]] + 1;
	for (int j = 1; j <= 18; ++j)
		fa[j][x] = fa[j - 1][fa[j - 1][x]];
	for (int i = head[x]; i; i = nxt[i]) {
		dfs1(to[i]);
		if (len[to[i]] > len[son[x]]) son[x] = to[i];
	}
	len[x] = len[son[x]] + 1;
}
void dfs2(int x, int t) {
	top[x] = t;
	if (x == t) {
		dfn[x] = cdfn + 1;
		cdfn += len[x];
		for (int i = 1, y = x; i <= len[x]; ++i, y = fa[0][y])
			up[dfn[x] + i - 1] = y;
		for (int i = 1, y = x; i <= len[x]; ++i, y = son[y])
			down[dfn[x] + i - 1] = y;
	}
	if (son[x]) dfs2(son[x], t);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != son[x]) dfs2(to[i], to[i]);
}
int height[maxn];
inline int GetFa(int x, int k) {
	if (k == 0) return x;
	int j = height[k];
	int y = top[fa[j][x]];
	k -= dep[x] - dep[y];
	return k >= 0 ? up[dfn[y] + k] : down[dfn[y] - k];
}
unsigned s = 0;
inline unsigned int get(unsigned int x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x;
}
unsigned long long AnsSum = 0, lasAns = 0;
int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d %d %u", &n, &q, &s);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &fa[0][i]);
		if (fa[0][i] == 0)
			root = i;
		else
			insert(fa[0][i], i);
	}
	dfs1(root);
	dfs2(root, root);
	height[0] = -1;
	for (int i = 1; i <= n; ++i)
		height[i] = height[i >> 1] + 1;
	for (int i = 1; i <= q; ++i) {
		unsigned x = (get(s) ^ lasAns) % n + 1;
		unsigned k = (get(s) ^ lasAns) % dep[x];
		lasAns = GetFa(x, k);
		// printf("%u %u %llu\n", x, k, lasAns);
		AnsSum ^= lasAns * i;
	}
	printf("%llu", AnsSum);
	fclose(stdin);
	fclose(stdout);
	return 0;
}