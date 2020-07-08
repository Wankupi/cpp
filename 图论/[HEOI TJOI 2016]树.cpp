//标记永久化
#include <cstdio>
const int maxn = 100001;
int n = 0, q = 0;
int head[100001], nxt[200003], to[200003], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int dfn[maxn],id[maxn], siz[maxn], dep[maxn],  c = 0;
void dfs(int x, int f) {
	dfn[x] = ++c;
	id[c] = x;
	siz[x] = 1;
	dep[x] = dep[f] + 1;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs(to[i], x);
			siz[x] += siz[to[i]];
		}
}
int sign[maxn << 2];
inline int commit(int a, int b) {
	if (a == 0) return b;
	if (b == 0) return a;
	return dep[a] < dep[b] ? b : a;
}
void tag(int p, int L, int R, int l, int r, int v) {
	if (l <= L && R <= r) {
		sign[p] = commit(sign[p], v);
		return;
	}
	int mid = (L + R) >> 1;
	if (l <= mid) tag(p << 1, L, mid, l, r, v);
	if (r > mid) tag(p << 1 | 1, mid + 1, R, l, r, v);
}
int query(int p, int L, int R, int x) {
	if (L == R) return sign[p];
	int mid = (L + R) >> 1;
	return commit(sign[p], (x <= mid ? query(p << 1, L, mid, x) : query(p << 1 | 1, mid + 1, R, x)));
}
int main() {
	scanf("%d%d", &n, &q);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	dfs(1, 1);
	tag(1, 1, n, 1, n, 1);
	for (int i = 1; i <= q; ++i) {
		do y = getchar(); while (y != 'Q' && y != 'C');
		scanf("%d", &x);
		if (y == 'Q') printf("%d\n", query(1, 1, n, dfn[x]));
		else tag(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, x);
	}
	return 0;
}