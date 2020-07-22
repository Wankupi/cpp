/*
查询路径权值第k小 -- 权值线段树-主席树
求 LCA- 倍增
树 连接 启发式合并
并查集 维护大小   令代表元素恰为根
注意 第一个输入是测试点编号。。不是数据组数
*/

#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
inline int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
const int maxn = 80003;
int n = 0, m = 0, Q = 0;
int a[maxn], ValTong[maxn], mV = 0;
int head[maxn], nxt[maxn << 2], to[maxn << 2], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }

int fa[maxn], siz[maxn];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) { // x --> y   y is the root
	x = find(x); y = find(y);
	siz[y] += siz[x];
	fa[x] = y;
}
void Init();

int root[maxn];
namespace Seg {
	const int maxP = maxn * 70;
	struct Node {
		int lc, rc;
		int sum;
	};
	Node tr[maxP];
	int c1 = 0;

	inline void pushUp(int p) {
		tr[p].sum = (tr[p].lc ? tr[tr[p].lc].sum : 0) + (tr[p].rc ? tr[tr[p].rc].sum : 0);
	}
	void Create(int &p, int L, int R) {
		p = ++c1;
		tr[p] = Node{ 0,0,0 };
		if (L == R) return;
		int mid = (L + R) >> 1;
		Create(tr[p].lc, L, mid);
		Create(tr[p].rc, mid + 1, R);
	}
	void Add(int &p, int L, int R, int x) {
		static int ST = 0;
		++ST;
		tr[++c1] = tr[p];
		p = c1;
		if (L == R) {
			++tr[p].sum;
			--ST;
			return;
		}
		int mid = (L + R) >> 1;
		if (x <= mid) Add(tr[p].lc, L, mid, x);
		else Add(tr[p].rc, mid + 1, R, x);
		pushUp(p);
		--ST;
	}
	int query(int p1, int p2, int p3, int p4, int L, int R, int k) { // +p1 +p2 -p3 -p4
		if (L == R) return L;
		int Lcnt = tr[tr[p1].lc].sum + tr[tr[p2].lc].sum - tr[tr[p3].lc].sum - tr[tr[p4].lc].sum;
		int mid = (L + R) >> 1;
		if (k <= Lcnt) return query(tr[p1].lc, tr[p2].lc, tr[p3].lc, tr[p4].lc, L, mid, k);
		return query(tr[p1].rc, tr[p2].rc, tr[p3].rc, tr[p4].rc, mid + 1, R, k - Lcnt);
	}
	void ReBase(int p, int p2, int L, int R, int x) {
		if (L == R) {
			tr[p].sum = tr[p2].sum + 1;
			return;
		}
		int mid = (L + R) >> 1;
		if (x <= mid) {
			tr[p].rc = tr[p2].rc;
			ReBase(tr[p].lc, tr[p2].lc, L, mid, x);
		}
		else {
			tr[p].lc = tr[p2].lc;
			ReBase(tr[p].rc, tr[p2].rc, mid + 1, R, x);
		}
		pushUp(p);
	}
}

int zx[maxn][18]; //祖先
int dep[maxn];
void dfsInit(int x, int f) {
	dep[x] = dep[f] + 1;
	zx[x][0] = f;
	for (int j = 1; j <= 16; ++j)
		zx[x][j] = zx[zx[x][j - 1]][j - 1];
	root[x] = root[f];
	Seg::Add(root[x], 1, mV, a[x]);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f)
			dfsInit(to[i], x);
}

int LCA(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int j = 16; ~j; --j)
		if (dep[zx[x][j]] >= dep[y])
			x = zx[x][j];
	if (x == y) return x;
	for (int j = 16; ~j; --j)
		if (zx[x][j] != zx[y][j]) {
			x = zx[x][j];
			y = zx[y][j];
		}
	return zx[x][0];
}

inline int Query(int x, int y, int k) {
	int lca = LCA(x, y);
	int flca = zx[lca][0];
	return ValTong[Seg::query(root[x], root[y], root[lca], root[flca], 1, mV, k)];
}

void dfsModify(int x, int f) {
	dep[x] = dep[f] + 1;
	zx[x][0] = f;
	for (int j = 1; j <= 16; ++j)
		zx[x][j] = zx[zx[x][j - 1]][j - 1];
	Seg::ReBase(root[x], root[f], 1, mV, a[x]);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f)
			dfsModify(to[i], x);
}

inline void Link(int x, int y) {
	insert(x, y);
	insert(y, x);
	int fx = find(x), fy = find(y);
	if (siz[x] > siz[y]) {
		swap(x, y); swap(fx, fy);
	}
	merge(fx, fy);
	dfsModify(x, y);
}

int main() {
	int Testcase = read();
	Init();
	Seg::Create(root[0], 1, mV);
	for (int i = 1; i <= n; ++i)
		if (!dep[i]) dfsInit(find(i), 0);
	int LastAns = 0;
	int opt = 0, x = 0, y = 0, k = 0;
	for (int i = 1; i <= Q; ++i) {
		do opt = getchar(); while (opt != 'Q' && opt != 'L');
		x = read() ^ LastAns; y = read() ^ LastAns;
		if (opt == 'Q') {
			k = read() ^ LastAns;
			LastAns = Query(x, y, k);
			printf("%d\n", LastAns);
			fflush(stdout);
		}
		else Link(x, y);
	}
	return 0;
}

void Init() {
	n = read(); m = read(); Q = read();
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		siz[i] = 1;
	}
	for (int i = 1; i <= n; ++i)
		ValTong[i] = a[i] = read();
	sort(ValTong + 1, ValTong + n + 1);
	mV = unique(ValTong + 1, ValTong + n + 1) - ValTong - 1;
	for (int i = 1; i <= n; ++i)
		a[i] = lower_bound(ValTong + 1, ValTong + mV + 1, a[i]) - ValTong;
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		x = read(); y = read();
		insert(x, y);
		insert(y, x);
		merge(x, y);
	}
}