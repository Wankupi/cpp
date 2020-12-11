#include <cstdio>
#include <algorithm>
typedef long long ll;
int const maxn = 100003;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n = 0;
int a[maxn];
int siz[maxn], fa[maxn], ls[maxn], rs[maxn], cnt = 0;
int k = 0, root = 0;
ll cur[maxn], c[maxn], y = 0, p[maxn], ans = 0;

void tag(int x, ll v) {
	c[x] += v;
	cur[x] += v;
}

void pushdown(int x) {
	if (cur[x]) {
		if (ls[x]) tag(ls[x], cur[x]);
		if (rs[x]) tag(rs[x], cur[x]);
		cur[x] = 0;
	}
}

void insert(int &x, int f = 0) {
	if (!x) {
		x = ++cnt;
		siz[x] = 1; c[x] = (k + 1) * y; fa[x] = f;
		return;
	}
	pushdown(x);
	++siz[x];
	if ((k + siz[ls[x]] + 1) * y >= c[x]) {
		c[x] += y;
		tag(rs[x], y);
		insert(ls[x], x);
	}
	else {
		k += siz[ls[x]] + 1;
		insert(rs[x], x);
	}
}
void pushup(int x) {
	siz[x] = siz[ls[x]] + siz[rs[x]] + 1;
}

void rotate(int x) {
	int y = fa[x], z = fa[y];
	if (ls[z] == y) ls[z] = x;
	if (rs[z] == y) rs[z] = x;
	fa[x] = z;
	fa[y] = x;
	if (ls[y] == x) { fa[ls[y] = rs[x]] = y; rs[x] = y; }
	else { fa[rs[y] = ls[x]] = y; ls[x] = y; }
	pushup(y); pushup(x);
}

void splay(int x) {
	for (; fa[x]; rotate(x)) {
		int y = fa[x], z = fa[y];
		if (z) rotate(((ls[z] == y) ^ (ls[y] == x)) ? x : y);
	}
	root = x;
}
void dfs(int x) {
	if (x == 0) return;
	pushdown(x);
	dfs(ls[x]);
	p[++*p] = c[x];
	dfs(rs[x]);
}
void getAns() {
	dfs(root);
	ll x = 0;
	for (int i = 1; i <= n; ++i) {
		ans = std::max(ans, x += p[i]);
	}
	printf("%lld\n", ans);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) {
		k = 0; y = a[i];
		insert(root);
		splay(i);
	}
	getAns();
	return 0;
}