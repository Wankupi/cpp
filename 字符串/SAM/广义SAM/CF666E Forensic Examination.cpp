#include <cstdio>
#include <algorithm>
int const LenT = 50003, LenS = 500003;
namespace Graph {
	int head[LenT << 1], nxt[LenT << 1], to[LenT << 1], cnt = 0;
	int fa[21][LenT << 1];
	inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
	void dfs(int x, int f);
}
namespace SAM {
	struct Node {
		int len;
		int son[26], fa;
		int &operator[](int x) { return son[x]; }
	};
	Node tr[LenT << 1];
	int cnt = 1;
	int expand(int last, int c) {
		int p = last, r = 0;
		if (tr[p][c]) {
			int q = tr[p][c];
			if (tr[q].len == tr[p].len + 1) r = q;
			else {
				int nq = ++cnt;
				tr[nq] = tr[q];
				tr[nq].len = tr[p].len + 1;
				tr[q].fa = nq;
				for (; p && tr[p][c] == q; p = tr[p].fa) tr[p][c] = nq;
				r = nq;
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
			r = np;
		}
		return r;
	}

	inline void bulidTree() { for (int i = 2; i <= cnt; ++i) Graph::insert(tr[i].fa, i); }
}

namespace SegTr {
	int const maxP = LenT * 80;
	struct MT { int mx, p; };
	MT operator+(MT const &lhs, MT const &rhs) { return lhs.mx >= rhs.mx ? lhs : rhs; }
	MT v[maxP];
	int lc[maxP], rc[maxP], cP = 0;
	void add(int &p, int L, int R, int x) {
		if (p == 0) p = ++cP;
		if (L == R) { ++v[p].mx; v[p].p = L; return; }
		int mid = (L + R) >> 1;
		if (x <= mid) add(lc[p], L, mid, x);
		if (x > mid) add(rc[p], mid + 1, R, x);
		v[p] = v[lc[p]] + v[rc[p]];
	}
	int merge(int x, int y, int L, int R) {
		if (x == 0 || y == 0) return x | y;
		int p = ++cP;
		if (L == R) {
			v[p].mx = v[x].mx + v[y].mx;
			v[p].p = L;
			return p;
		}
		int mid = (L + R) >> 1;
		lc[p] = merge(lc[x], lc[y], L, mid);
		rc[p] = merge(rc[x], rc[y], mid + 1, R);
		v[p] = v[lc[p]] + v[rc[p]];
		return p;
	}
	MT query(int p, int L, int R, int l, int r) {
		if (p == 0 || (l <= L && R <= r)) return v[p];
		int mid = (L + R) >> 1;
		if (r <= mid) return query(lc[p], L, mid, l, r);
		else if (l > mid) return query(rc[p], mid + 1, R, l, r);
		else return query(lc[p], L, mid, l, r) + query(rc[p], mid + 1, R, l, r);
	}
}

int m = 0, lS = 0;
char S[LenS], T[LenT];
int pos[LenS], rlen[LenS];
int root[LenT << 1];
namespace Graph {
	void dfs(int x, int f) {
		fa[0][x] = f;
		for (int j = 1; j <= 20; ++j) fa[j][x] = fa[j - 1][fa[j - 1][x]];
		for (int i = head[x]; i; i = nxt[i]) {
			dfs(to[i], x);
			root[x] = SegTr::merge(root[x], root[to[i]], 1, m);
		}
	}
}

inline SegTr::MT Query(int ql, int qr, int sl, int sr) {
	if (rlen[sr] < sr - sl + 1) return SegTr::MT{ 0, ql };
	int p = pos[sr];
	for (int j = 20; ~j; --j)
		if (SAM::tr[Graph::fa[j][p]].len >= (sr - sl + 1))
			p = Graph::fa[j][p];
	return SegTr::query(root[p], 1, m, ql, qr);
}

int main() {
	scanf("%s", S + 1);
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%s", T);
		int p = 1;
		for (int j = 0; T[j]; ++j) {
			p = SAM::expand(p, T[j] - 'a');
			SegTr::add(root[p], 1, m, i);
		}
	}
	SAM::bulidTree();
	Graph::dfs(1, 1);
	pos[0] = 1;
	for (int i = 1; S[i]; ++i) {
		int p = pos[i - 1], len = rlen[i - 1];
		while (p && !SAM::tr[p][S[i] - 'a']) p = SAM::tr[p].fa;
		if (p == 0) p = 1, len = 0;
		else len = std::min(len, SAM::tr[p].len) + 1, p = SAM::tr[p][S[i] - 'a'];
		pos[i] = p;
		rlen[i] = len;
	}
	int Q = 0, ql = 0, qr = 0, sl = 0, sr = 0;
	scanf("%d", &Q);
	for (int i = 1; i <= Q; ++i) {
		scanf("%d %d %d %d", &ql, &qr, &sl, &sr);
		SegTr::MT rs = Query(ql, qr, sl, sr);
		if (rs.mx == 0) rs.p = ql;
		printf("%d %d\n", rs.p, rs.mx);
	}
	return 0;
}