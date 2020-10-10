#include <cstdio>
#include <algorithm>
using namespace std;
int const maxn = 100003;
int a[maxn];
int fa[maxn], son[maxn][2];
int sum[maxn], rev[maxn];

bool isNotRoot(int x) { return son[fa[x]][0] == x || son[fa[x]][1] == x; }
void pushUp(int x) { sum[x] = sum[son[x][0]] ^ a[x] ^ sum[son[x][1]]; }
void tagRev(int x) { rev[x] ^= 1; std::swap(son[x][0], son[x][1]); }
void pushDown(int x) { if (rev[x]) { if (son[x][0]) tagRev(son[x][0]); if (son[x][1]) tagRev(son[x][1]); rev[x] = 0; } }
inline int iden(int x) { return son[fa[x]][1] == x; }
void rotate(int x) { // we confirm that x is not root
	int f = fa[x], z = fa[f], m = iden(x), xs = son[x][m ^ 1];
	if (isNotRoot(f)) son[z][iden(f)] = x;
	son[x][m ^ 1] = f;
	son[f][m] = xs;
	if (xs) fa[xs] = f;
	fa[f] = x;
	fa[x] = z;
	pushUp(f);
	pushUp(x);
}

void splay(int x) {
	static int st[maxn];
	int y = x, z = 0;
	st[z = 1] = x;
	while (isNotRoot(y)) y = st[++z] = fa[y];
	while (z) pushDown(st[z--]);
	while (isNotRoot(x)) {
		y = fa[x]; z = fa[y];
		// if (isNotRoot(y)) rotate(iden(x) == iden(y) ? y : x);
		if (isNotRoot(y)) rotate(((son[y][0] == x) ^ (son[z][0] == y)) ? x : y);
		rotate(x);
	}
	pushUp(x);
}
inline void access(int x) {
	for (int y = 0; x; x = fa[y = x]) {
		splay(x); son[x][1] = y; pushUp(x);
	}
}
inline void makeroot(int x) { access(x); splay(x); tagRev(x); }
inline int findroot(int x) {
	access(x); splay(x);
	while (son[x][0]) { pushDown(x); x = son[x][0]; }
	splay(x);
	return x;
}
inline void split(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
}
inline void link(int x, int y) {
	makeroot(x);
	if (findroot(y) != x) fa[x] = y;
}
inline void cut(int x, int y) {
	split(x, y);
	if (son[y][0] == x && son[x][1] == 0) {
		son[y][0] = 0;
		fa[x] = 0;
		pushUp(y);
	}
}
int main() {
	int n = 0, m = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i), sum[i] = a[i];
	int opt = 0, x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &opt, &x, &y);
		if (opt == 0) {
			split(x, y);
			printf("%d\n", sum[y]);
		}
		else if (opt == 1) link(x, y);
		else if (opt == 2) cut(x, y);
		else { splay(x); a[x] = y; pushUp(x); }
	}
	return 0;
}