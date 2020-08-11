#include <cstdio>
#include <algorithm>
#include <cstring>
const int maxn = 100003, maxm = 400003;
int read() {
	int x = 0, c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9')
		x = 10 * x + c - '0', c = getchar();
	return x;
}
int n = 0, m = 0, q = 0;
int head[maxn], nxt[maxm], to[maxm], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
void clear();
void tarjan(int x, int f);
namespace CirSqTr {
	int cPoint = 0;
	int head[maxn << 1], nxt[maxm], to[maxm], cnt = 0;
	inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
	int siz[maxn << 1], fa[maxn << 1], son[maxn << 1], dep[maxn << 1], dis[maxn << 1], cdfnTr = 0;
	int dfn[maxn << 1], top[maxn << 1];
	void dfs1(int x, int f);
	void dfs2(int x, int t);
	int lca(int x, int y);
	int Distance(int x, int y) { return dis[x] + dis[y] - 2 * dis[lca(x, y)]; }
} // namespace CirSqTr
bool cmp(int a, int b) { return CirSqTr::dfn[a] < CirSqTr::dfn[b]; }
int S = 0, s[maxn];
int solve();
int main() {
	int T = read();
	for (int t = 1; t <= T; ++t) {
		clear();
		CirSqTr::cPoint = n = read();
		m = read();
		int x = 0, y = 0;
		for (int i = 1; i <= m; ++i) {
			x = read(); y = read();
			insert(x, y); insert(y, x);
		}
		tarjan(1, 1);
		CirSqTr::dfs1(1, 0);
		CirSqTr::dfs2(1, 1);
		q = read();
		for (int j = 1; j <= q; ++j) {
			S = read();
			for (int i = 1; i <= S; ++i) s[i] = read();
			std::sort(s + 1, s + S + 1, cmp);
			printf("%d\n", solve());
		}
	}
	return 0;
}
inline int min(int a, int b) { return a < b ? a : b; }
inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
int dfn[maxn], low[maxn], cdfn = 0;
int stack[maxn], up = 0;
void tarjan(int x, int f) {
	dfn[x] = low[x] = ++cdfn;
	stack[++up] = x;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			if (!dfn[to[i]]) {
				tarjan(to[i], x);
				low[x] = min(low[x], low[to[i]]);
				if (low[to[i]] >= dfn[x]) {
					int k = ++CirSqTr::cPoint, y = 0;
					do {
						y = stack[up--];
						CirSqTr::insert(y, k);
						CirSqTr::insert(k, y);
					} while (y != to[i]);
					CirSqTr::insert(x, k);
					CirSqTr::insert(k, x);
				}
			}
			else low[x] = min(low[x], dfn[to[i]]);
		}
}
void CirSqTr::dfs1(int x, int f) {
	siz[x] = 1;
	fa[x] = f;
	dep[x] = dep[f] + 1;
	dis[x] = dis[f] + (x <= n);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs1(to[i], x);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
		}
}
void CirSqTr::dfs2(int x, int t) {
	dfn[x] = ++cdfnTr;
	top[x] = t;
	if (son[x]) dfs2(son[x], t);
	for(int i = head[x];i;i=nxt[i]) 
		if (to[i] != fa[x] && to[i] != son[x])
			dfs2(to[i], to[i]);
}
inline int CirSqTr::lca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
inline int solve() {
	int res = 0;
	s[0] = s[S];
	for (int i = 1; i <= S; ++i)
		res += CirSqTr::Distance(s[i - 1], s[i]);
	res /= 2;
	res = res - S + (CirSqTr::lca(s[1], s[S]) <= n);
	return res;
}
inline void clear() {
	memset(head, 0, sizeof head);
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	cnt = 0;
	cdfn = 0;
	up = 0;
	memset(CirSqTr::head, 0, sizeof CirSqTr::head);
	memset(CirSqTr::son, 0, sizeof CirSqTr::son);
	memset(CirSqTr::dep, 0, sizeof CirSqTr::dep);
	memset(CirSqTr::dis, 0, sizeof CirSqTr::dis);
	memset(CirSqTr::top, 0, sizeof CirSqTr::top);
	memset(CirSqTr::siz, 0, sizeof CirSqTr::siz);
	CirSqTr::cnt = 0;
	CirSqTr::cdfnTr = 0;
}