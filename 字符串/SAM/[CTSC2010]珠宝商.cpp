#include <cstdio>
#include <algorithm>
#include <cmath>
typedef long long ll;
int const maxn = 50003, maxP = maxn << 1, inf = 0x3f3f3f3f;

int n = 0, m = 0;
ll ans = 0;

template<unsigned N = maxn>
struct Graph {
	int head[N], nxt[N << 1], to[N << 1], cnt = 0;
	inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
};

struct SAM {
	struct Node {
		int len, fa, son[26];
		int& operator[](int x) { return son[x]; }
	};
	char *s = nullptr;
	Node sam[maxP];
	Graph<maxP> pt; // Parent Tree
	int tr[maxP][26]; // Suffix Tree
	int siz[maxP], pos[maxP], id[maxn]; // pos 节点i在字符串上的位置 id 1~i串的匹配节点
	int cnt = 1, last = 1;
	void expand(int c) {
		int p = last, np = ++cnt;
		sam[np].len = sam[p].len + 1;
		siz[np] = 1;
		for (; p && sam[p][c] == 0; p = sam[p].fa) sam[p][c] = np;
		if (p == 0) sam[np].fa = 1;
		else {
			int q = sam[p][c];
			if (sam[q].len == sam[p].len + 1) sam[np].fa = q;
			else {
				int nq = ++cnt;
				sam[nq] = sam[q];
				sam[nq].len = sam[p].len + 1;
				sam[np].fa = sam[q].fa = nq;
				for (; p && sam[p][c] == q; p = sam[p].fa) sam[p][c] = nq;
			}
		}
		last = np;
	}
	void dfs(int x) {
		for (int i = pt.head[x]; i; i = pt.nxt[i]) {
			int y = pt.to[i];
			dfs(y);
			siz[x] += siz[y];
			pos[x] = pos[y];
			tr[x][s[pos[y] - sam[x].len] - 'a'] = y;
		}
	}
	void buildSAM() {
		for (int i = 1; i <= m; ++i) expand(s[i] - 'a'), pos[last] = i, id[i] = last;
		for (int i = 2; i <= cnt; ++i) pt.insert(sam[i].fa, i);
		dfs(1);
	}

	ll tag[maxP];
	void pushDown(int x) { for (int i = pt.head[x]; i; i = pt.nxt[i]) { tag[pt.to[i]] += tag[x]; pushDown(pt.to[i]); } }
	void clear() { for (int i = 0; i <= cnt; ++i) tag[i] = 0; }
};

char a[maxn], S[maxn], revS[maxn];
Graph<maxn> G;
SAM A, B;
int BLOCK = 0; // sqrt(n) 根号分治

bool ban[maxn];
int siz[maxn];
int rt = 0, SizeRoot = inf, SizeAll = 0;

void dfs_rough(int x, int f, int p) {
	p = A.sam[p][a[x] - 'a'];
	if (p == 0) return;
	ans += A.siz[p];
	for (int i = G.head[x]; i; i = G.nxt[i])
		if (!ban[G.to[i]] && G.to[i] != f)
			dfs_rough(G.to[i], x, p);
}
void dfs_rough_root(int x, int f) {
	dfs_rough(x, 0, 1);
	for (int i = G.head[x]; i; i = G.nxt[i])
		if (!ban[G.to[i]] && G.to[i] != f)
			dfs_rough_root(G.to[i], x);
}

void get_root(int x, int f) {
	int MxSubtree = 0;
	siz[x] = 1;
	for (int i = G.head[x]; i; i = G.nxt[i])
		if (!ban[G.to[i]] && G.to[i] != f) {
			get_root(G.to[i], x);
			siz[x] += siz[G.to[i]];
			MxSubtree = std::max(MxSubtree, siz[G.to[i]]);
		}
	MxSubtree = std::max(MxSubtree, SizeAll - siz[x]);
	if (MxSubtree < SizeRoot) { rt = x; SizeRoot = MxSubtree; }
}

void dfs_tag(int x, int f, int p, int len, SAM &AM) { // len: length of fa
	if (len == AM.sam[p].len) p = AM.tr[p][a[x] - 'a'];
	else if (a[x] != AM.s[AM.pos[p] - len]) p = 0;
	if (p == 0) return;
	++len;
	++AM.tag[p];
	for (int i = G.head[x]; i; i = G.nxt[i])
		if (!ban[G.to[i]] && G.to[i] != f)
			dfs_tag(G.to[i], x, p, len, AM);
}
void calc(int x, int f, int op) {
	A.clear(); B.clear();
	if (f == 0) {
		dfs_tag(x, 0, 1, 0, A);
		dfs_tag(x, 0, 1, 0, B);
	}
	else {
		dfs_tag(x, f, A.tr[1][a[f] - 'a'], 1, A);
		dfs_tag(x, f, B.tr[1][a[f] - 'a'], 1, B);
	}
	A.pushDown(1); B.pushDown(1);
	for (int i = 1; i <= m; ++i)
		ans += op * ll(A.tag[A.id[i]]) * ll(B.tag[B.id[m - i + 1]]);
}

void solve(int x, int Siz) {
	if (Siz <= BLOCK) {
		dfs_rough_root(x, 0);
		return;
	}
	ban[x] = true; // ban mustn't set before rough
	calc(x, 0, +1);
	get_root(x, 0); // get Size
	for (int i = G.head[x]; i; i = G.nxt[i]) // ensure the size have been updated
		if (!ban[G.to[i]]) {
			calc(G.to[i], x, -1);
			SizeAll = siz[G.to[i]]; rt = 0; SizeRoot = inf;
			get_root(G.to[i], 0);
			solve(rt, siz[G.to[i]]);
		}
}
int main() {
	scanf("%d %d", &n, &m);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		G.insert(x, y);
		G.insert(y, x);
	}
	scanf("%s", a + 1);
	scanf("%s", S + 1);
	for (int i = 1; i <= m; ++i) revS[m - i + 1] = S[i];
	A.s = S; B.s = revS;
	A.buildSAM(); B.buildSAM();
	BLOCK = int(sqrt(n));
	SizeAll = n; rt = 0; SizeRoot = inf;
	get_root(1, 0);
	solve(rt, n);
	printf("%lld", ans);
	return 0;
}