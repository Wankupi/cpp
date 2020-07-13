#include <cstdio>
typedef long long ll;
const int maxn = 20001, bit = 60;
int n = 0, q = 0;
ll a[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
template <typename T>
void swap(T &a, T &b) {
	T c = a;
	a = b;
	b = c;
}
struct Base {
	ll b[bit + 1];
	int w[bit + 1];
	void insert(ll x, int p) {
		for (int i = bit; ~i; --i)
			if (x >> i & 1) {
				if (b[i] == 0) {
					b[i] = x;
					w[i] = p;
				}
				else if (w[i] < p) {
					swap(b[i], x);
					swap(w[i], p);
				}
				x ^= b[i];
			}
	}
	ll make(int limit) {
		ll x = 0;
		for (int i = bit; ~i; --i)
			if (((x >> i) & 1) == 0 && b[i] && w[i] >= limit)
				x ^= b[i];
		return x;
	}
};
Base combine(Base A, const Base &B) {
	for (int i = bit; ~i; --i)
		if (B.b[i]) A.insert(B.b[i], B.w[i]);
	return A;
}
int fa[16][maxn], dep[maxn];
Base ji[maxn];
void dfs(int x, int f) {
	fa[0][x] = f;
	dep[x] = dep[f] + 1;
	ji[x] = ji[f];
	ji[x].insert(a[x], dep[x]);
	for (int j = 1; j <= 15; ++j)
		fa[j][x] = fa[j - 1][fa[j - 1][x]];
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f)
			dfs(to[i], x);
}
int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = 15; ~i; --i)
		if (dep[fa[i][x]] >= dep[y]) x = fa[i][x];
	if (x == y) return x;
	for (int i = 15; ~i; --i)
		if (fa[i][x] != fa[i][y]) x = fa[i][x], y = fa[i][y];
	return fa[0][x];
}
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", a + i);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	dfs(1, 1);
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d", &x, &y);
		int LCA = lca(x, y);
		printf("%lld\n", combine(ji[x], ji[y]).make(dep[LCA]));
	}
	return 0;
}