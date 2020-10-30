#include <cstdio>
#include <algorithm>
using namespace std;
int const maxn = 150003;

int n = 0, m = 0;
struct Edge { int u, e, a, b; };
inline bool operator<(Edge const &lhs, Edge const &rhs) { return lhs.a == rhs.a ? lhs.b < rhs.b : lhs.a < rhs.a; }
Edge line[maxn];


int fa[maxn], son[maxn][2];
int MxP[maxn], rev[maxn], v[maxn];

inline bool isroot(int x) { return son[fa[x]][0] != x && son[fa[x]][1] != x; }
inline int iden(int x) { return son[fa[x]][1] == x; }
inline void tagRev(int x) { rev[x] ^= 1; std::swap(son[x][0], son[x][1]); }
inline void pushup(int x) {
	MxP[x] = v[MxP[son[x][0]]] > v[MxP[son[x][1]]] ? MxP[son[x][0]] : MxP[son[x][1]];
	if (x > n && v[x] > v[MxP[x]]) MxP[x] = x;
}
inline void pushdown(int x) {
	if (!rev[x]) return;
	if (son[x][0]) tagRev(son[x][0]);
	if (son[x][1]) tagRev(son[x][1]);
	rev[x] = 0;
}
inline void rotate(int x) {
	int f = fa[x], z = fa[f], m = iden(x), xs = son[x][m ^ 1];
	if (!isroot(f)) son[z][iden(f)] = x;
	fa[x] = z;
	son[f][m] = xs;
	if (xs) fa[xs] = f;
	son[x][m ^ 1] = f;
	fa[f] = x;
	pushup(f);
	pushup(x);
}
void splay(int x) {
	static int st[maxn];
	int top = 0;
	st[top = 1] = x;
	for (int y = x; !isroot(y); y = fa[y]) st[++top] = fa[y];
	while (top) pushdown(st[top--]);
	for (; !isroot(x); rotate(x))
		if (!isroot(fa[x])) rotate(iden(x) == iden(fa[x]) ? fa[x] : x);
}
void access(int x) {
	for (int y = 0; x; x = fa[y = x]) {
		splay(x);
		son[x][1] = y;
		pushup(x);
	}
}
void makeroot(int x) {
	access(x);
	splay(x);
	tagRev(x);
}
inline void split(int x, int y) { makeroot(x); access(y); splay(x); }
inline int findroot(int x) {
	access(x);
	splay(x);
	while (son[x][0]) { pushdown(x); x = son[x][0]; }
	splay(x);
	return x;
}
inline void link(int x, int y) {
	makeroot(x);
	if (findroot(y) != x) fa[x] = y;
}
inline void cut(int x, int y) {
	split(x, y);
	son[x][1] = 0;
	fa[y] = 0;
	pushup(x);
}

int fath[maxn];
inline int findFa(int x) { return fath[x] == x ? x : fath[x] = findFa(fath[x]); }
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d %d", &line[i].u, &line[i].e, &line[i].a, &line[i].b);
	}
	sort(line + 1, line + m + 1);
	for (int i = 1; i <= n; ++i) fath[i] = i;
	for (int i = 1; i <= m; ++i) MxP[i + n] = i + n, v[i + n] = line[i].b;
	int ans = 0x3f3f3f3f;
	for (int i = 1; i <= m; ++i) {
		if (findFa(line[i].u) != findFa(line[i].e)) {
			link(i + n, line[i].u);
			link(i + n, line[i].e);
			fath[findFa(line[i].u)] = findFa(line[i].e);
		}
		else {
			if (line[i].u == line[i].e) continue;
			split(line[i].u, line[i].e);
			int t = line[i].u;
			int k = MxP[t];
			if (line[k - n].b <= line[i].b) continue;
			cut(k, line[k - n].u);
			cut(k, line[k - n].e);
			link(i + n, line[i].u);
			link(i + n, line[i].e);
		}
		if (findFa(1) == findFa(n)) {
			split(1, n);
			ans = std::min(ans, line[i].a + line[MxP[1] - n].b);
		}
	}
	printf("%d", ans == 0x3f3f3f3f ? -1 : ans);
	return 0;
}