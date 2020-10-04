#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
int const LEN = 100003, maxn = 50003 * 40;
int n = 0, m = 0;
int ans1[LEN], ans2[LEN];

namespace SegTr {
	int val[maxn], lc[maxn], rc[maxn], cntP = 0;
	int lazy[maxn];
	void set(int &p, int L, int R, int x) {
		if (p == 0) p = ++cntP;
		if (L == R) {
			val[p] = 1;
			return;
		}
		int mid = (L + R) >> 1;
		if (x <= mid) set(lc[p], L, mid, x);
		else set(rc[p], mid + 1, R, x);
		val[p] = val[lc[p]] + val[rc[p]]; // val[0] = 0
	}
	int merge_In_SAM(int x, int y, int L, int R) {
		if (x == 0 || y == 0) return x | y;
		if (val[x] == R - L + 1) return x;
		if (val[y] == R - L + 1) return y;
		if (L == R) return x;
		int mid = (L + R) >> 1;
		lc[x] = merge_In_SAM(lc[x], lc[y], L, mid);
		rc[x] = merge_In_SAM(rc[x], rc[y], mid + 1, R);
		val[x] = val[lc[x]] + val[rc[x]];
		return x;
	}
	int merge_Persistent(int x, int y, int L, int R) { // x is on the AnsTree
		if (y == 0) return x;
		if (x == 0) x = ++cntP;
		if (val[y] == R - L + 1) {
			++lazy[x];
			return x;
		}
		if (L == R) {
			val[x] += val[y];
			return x;
		}
		int mid = (L + R) >> 1;
		lc[x] = merge_Persistent(lc[x], lc[y], L, mid);
		rc[x] = merge_Persistent(rc[x], rc[y], mid + 1, R);
		val[x] = val[lc[x]] + val[rc[x]];
		return x;
	}
	void dfs(int p, int L, int R, int laz) {
		if (p == 0) {
			for (int i = L; i <= R; ++i)
				ans2[i] = laz;
			return;
		}
		laz += lazy[p];
		if (L == R) {
			ans2[L] = val[p] + laz;
			return;
		}
		int mid = (L + R) >> 1;
		dfs(lc[p], L, mid, laz);
		dfs(rc[p], mid + 1, R, laz);
	}
}

namespace Graph {
	int head[LEN << 1], nxt[LEN << 1], to[LEN << 1], cnt;
	inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
	int dfn[LEN << 1], siz[LEN << 1], cdfn = 0;
	void dfs(int x) {
		dfn[x] = ++cdfn;
		for (int i = head[x]; i; i = nxt[i])
			dfs(to[i]);
	}
}

int root[LEN << 1];

namespace SAM {
	struct Node {
		int len;
		map<int, int> son;
		int fa;
		int& operator[](int x) { return son[x]; }
	};
	Node tr[LEN << 1];
	int cnt = 1;
	inline int expand(int last, int c, int W) {
		int p = last, ret = 0;
		if (tr[p][c]) {
			int q = tr[p][c];
			if (tr[q].len == tr[p].len + 1) ret = q;
			else {
				int nq = ++cnt;
				tr[nq] = tr[q];
				tr[nq].len = tr[p].len + 1;
				tr[q].fa = nq;
				for (; p && tr[p][c] == q; p = tr[p].fa) tr[p][c] = nq;
				ret = nq;
			}
		}
		else {
			int np = ++cnt;
			tr[np].len = tr[p].len + 1;
			for (; p && tr[p][c] == 0; p = tr[p].fa) tr[p][c] = np;
			if (p == 0) tr[np].fa = 1;
			else {
				int q = tr[p][c];
				if (tr[q].len == tr[p].len + 1) tr[np].fa = q;
				else {
					int nq = ++cnt;
					tr[nq] = tr[q];
					tr[nq].len = tr[p].len + 1;
					tr[np].fa = tr[q].fa = nq;
					for (; p && tr[p][c] == q; p = tr[p].fa) tr[p][c] = nq;
				}
			}
			ret = np;
		}
		SegTr::set(root[ret], 1, n, W);
		return ret;
	}
	inline void make_ParentTree() {
		for (int i = 2; i <= cnt; ++i)
			Graph::insert(tr[i].fa, i);
		Graph::dfs(1);
	}
	inline int run(int p, int c) { return tr[p][c]; } // tr[p][c] may be not exist, then get 0 but insert an no use point to the map
};

struct Query {
	int endPoint;
	int id;
};
inline bool operator<(const Query &lhs, const Query &rhs) { return Graph::dfn[lhs.endPoint] > Graph::dfn[rhs.endPoint]; }
int poi[LEN << 1];
inline bool cmpPointDfn(int lhs, int rhs) { return Graph::dfn[lhs] > Graph::dfn[rhs]; }
Query que[LEN];

inline void combine(int x) {
	for (int i = Graph::head[x]; i; i = Graph::nxt[i])
		root[x] = SegTr::merge_In_SAM(root[x], root[Graph::to[i]], 1, n);
}

int main() {
	freopen("name1.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d %d", &n, &m);
	int L = 0, x = 0, last = 1;
	for (int i = 1; i <= n; ++i) {
		last = 1;
		scanf("%d", &L);
		for (int j = 1; j <= L; ++j) {
			scanf("%d", &x);
			last = SAM::expand(last, x, i);
		}
		last = 1;
		scanf("%d", &L);
		for (int j = 1; j <= L; ++j) {
			scanf("%d", &x);
			last = SAM::expand(last, x, i);
		}
	}
	SAM::make_ParentTree();
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &L);
		que[i].id = i;
		last = 1;
		for (int j = 1; j <= L; ++j) {
			scanf("%d", &x);
			if (last) last = SAM::run(last, x);
		}
		que[i].endPoint = last;
	}

	for (int i = 1; i <= SAM::cnt; ++i) poi[i] = i;
	sort(que + 1, que + m + 1);
	sort(poi + 1, poi + SAM::cnt + 1, cmpPointDfn);
	int cur = 1, AnsRoot = 0;
	for (int i = 1; i <= m; ++i) {
		if (que[i].endPoint == 0) {
			ans1[que[i].id] = 0;
			continue;
		}
		while (cur <= SAM::cnt && Graph::dfn[poi[cur]] >= Graph::dfn[que[i].endPoint]) combine(poi[cur++]);
		ans1[que[i].id] = SegTr::val[root[que[i].endPoint]];
		AnsRoot = SegTr::merge_Persistent(AnsRoot, root[que[i].endPoint], 1, n);
	}
	SegTr::dfs(AnsRoot, 1, n, 0);
	for (int i = 1; i <= m; ++i) printf("%d\n", ans1[i]);
	for (int i = 1; i <= n; ++i) printf("%d ", ans2[i]);
	putchar('\n');
	return 0;
}