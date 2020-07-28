#include <cstdio>
#include <cstring>
const int maxn = 50001, inf = 0x3f3f3f3f;
inline void swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}
inline int max(int a, int b) { return a < b ? b : a; }
int n = 0, m = 0;
int head[50001], nxt[100003], to[100003], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
char st[50001][3];

int dfn[maxn], id[maxn], fa[maxn], dep[maxn], siz[maxn], son[maxn], top[maxn], cDfn = 0;
void dfs1(int x, int f) {
	siz[x] = 1;
	dep[x] = dep[f] + 1;
	fa[x] = f;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs1(to[i], x);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
		}
}
void dfs2(int x, int t) {
	dfn[x] = ++cDfn;
	id[cDfn] = x;
	top[x] = t;
	if (son[x]) dfs2(son[x], t);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x] && to[i] != son[x])
			dfs2(to[i], to[i]);
}

struct Node {
	Node() { memset(this, 0, sizeof(Node)); }
	int l[2], r[2];
	int dis[2][2];
};
Node operator+(const Node &A, const Node &B) {
	Node re;
	for (int i = 0; i <= 1; ++i)
		for (int j = 0; j <= 1; ++j)
			re.l[i] = max(re.l[i], max(A.l[i], A.dis[i][j] + B.l[j]));
	for (int i = 0; i <= 1; ++i)
		for (int j = 0; j <= 1; ++j)
			re.r[i] = max(re.r[i], max(B.r[i], B.dis[j][i] + A.r[j]));
	for (int i = 0; i <= 1; ++i)
		for (int j = 0; j <= 1; ++j) {
			re.dis[i][j] = -inf;
			for (int k = 0; k <= 1; ++k)
				re.dis[i][j] = max(re.dis[i][j], A.dis[i][k] + B.dis[k][j]);
		}
	return re;
}
Node operator-(const Node &A) {
	Node re = A;
	swap(re.l[0], re.r[0]);
	swap(re.l[1], re.r[1]);
	swap(re.dis[0][1], re.dis[1][0]);
	return re;
}
Node tr[maxn << 2];
inline Node Value(int k) {
	Node ret;
	if (st[k][0] == '.' && st[k][1] == '.') {
		ret.dis[0][1] = ret.dis[1][0] = ret.l[0] = ret.l[1] = ret.r[0] = ret.r[1] = 2;
		ret.dis[0][0] = ret.dis[1][1] = 1;
	}
	else if (st[k][0] == '.' || st[k][1] == '.') {
		int w = (st[k][0] != '.');
		ret.l[w] = ret.r[w] = ret.dis[w][w] = 1;
		ret.l[w ^ 1] = ret.r[w ^ 1] = 0;
		ret.dis[w][w ^ 1] = ret.dis[w ^ 1][w] = ret.dis[w ^ 1][w ^ 1] = -inf;
	}
	else {
		ret.l[0] = ret.l[1] = ret.r[0] = ret.r[1] = 0;
		ret.dis[0][0] = ret.dis[0][1] = ret.dis[1][0] = ret.dis[1][1] = -inf;
	}
	return ret;
}
void Create(int p, int L, int R) {
	if (L == R) {
		tr[p] = Value(id[L]);
		return;
	}
	int mid = (L + R) >> 1;
	Create(p << 1, L, mid);
	Create(p << 1 | 1, mid + 1, R);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}
void ReLoad(int p, int L, int R, int x) {
	if (L == R) {
		tr[p] = Value(id[x]);
		return;
	}
	int mid = (L + R) >> 1;
	if (x <= mid)
		ReLoad(p << 1, L, mid, x);
	else
		ReLoad(p << 1 | 1, mid + 1, R, x);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}
Node Query(int p, int L, int R, int l, int r) {
	if (l <= L && R <= r)
		return tr[p];
	int mid = (L + R) >> 1;
	if (r <= mid)
		return Query(p << 1, L, mid, l, r);
	else if (l > mid)
		return Query(p << 1 | 1, mid + 1, R, l, r);
	else
		return Query(p << 1, L, mid, l, r) + Query(p << 1 | 1, mid + 1, R, l, r);
}

int que(int x, int y) { //尽力从x到y
	Node A, B;
	while (top[x] != top[y]) { //这里不能用交换的写法
		if (dep[top[x]] > dep[top[y]]) {
			A = Query(1, 1, n, dfn[top[x]], dfn[x]) + A;
			x = fa[top[x]];
		}
		else {
			B = Query(1, 1, n, dfn[top[y]], dfn[y]) + B;
			y = fa[top[y]];
		}
	}
	if (dep[x] > dep[y])
		A = Query(1, 1, n, dfn[y], dfn[x]) + A;
	else
		B = Query(1, 1, n, dfn[x], dfn[y]) + B;
	Node ans = -A + B; //不可颠倒
	return max(ans.l[0], ans.l[1]);
}

int main() {
	scanf("%d %d\n", &n, &m);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d\n", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	for (int i = 1; i <= n; ++i)
		scanf("%s\n", st[i]);
	dfs1(1, 1);
	dfs2(1, 1);
	Create(1, 1, n);
	int opt = 0;
	for (int i = 1; i <= m; ++i) {
		do
			opt = getchar();
		while (opt != 'Q' && opt != 'C');
		if (opt == 'Q') {
			scanf("%d %d", &x, &y);
			printf("%d\n", que(x, y)); //x y不可颠倒
			fflush(stdout);
		}
		else {
			scanf("%d ", &x);
			scanf("%s", st[x]);
			ReLoad(1, 1, n, dfn[x]);
		}
	}
	return 0;
}