#include <cstdio>
#include <algorithm>

typedef long long ll;
int const maxn = 1677;
ll const mod = 64123;
inline ll pls(ll a, ll b) { return a + b < mod ? a + b : a + b - mod; }
inline ll dec(ll a, ll b) { return a >= b ? a - b : a - b + mod; }

int n = 0, k = 0, W = 0;
int d[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }

struct Data {
	Data() {}
	Data(int A, int B, int C, int D) : a(A), b(B), c(C), d(D) {}
	void clear() { a = 1; b = c = d = 0; }
	int a, b, c, d;
};
inline Data operator*(Data const &A, Data const &B) {
	return Data(ll(A.a) * B.a % mod, pls(ll(A.b) * B.a % mod, B.b), pls(A.c, ll(A.a) * B.c % mod), pls(pls(A.d, B.d), ll(A.b) * B.c % mod)); // there do not mod, because it will be mod in Data(..)
}
struct Node {
	Node() {}
	void init() {
		v.clear();
		ls = rs = 0;
	}
	Data v;
	int ls, rs;
};
Node tr[maxn * 50];
int bin[maxn * 50];
int cntNode = 0, binTop = 0;
inline int newNode() {
	int r = binTop ? bin[binTop--] : ++cntNode;
	tr[r].init();
	return r;
}
void delTree(int &p) {
	if (p == 0) return;
	if (tr[p].ls) delTree(tr[p].ls);
	if (tr[p].rs) delTree(tr[p].rs);
	bin[++binTop] = p;
	tr[p].init();
	p = 0;
}
void pushdown(int p) {
	if (tr[p].ls == 0) tr[p].ls = newNode();
	if (tr[p].rs == 0) tr[p].rs = newNode();
	tr[tr[p].ls].v = tr[tr[p].ls].v * tr[p].v;
	tr[tr[p].rs].v = tr[tr[p].rs].v * tr[p].v;
	tr[p].v.clear();
}
void modify(int &p, int L, int R, int l, int r, Data const x) {
	if (p == 0) p = newNode();
	if (l <= L && R <= r) { tr[p].v = tr[p].v * x; return; }
	pushdown(p);
	int mid = (L + R) >> 1;
	if (l <= mid) modify(tr[p].ls, L, mid, l, r, x);
	if (r > mid) modify(tr[p].rs, mid + 1, R, l, r, x);
}
int merge(int &x, int &y) { // 必须传引用 否则swap后del时会出错
	if (tr[x].ls == 0 && tr[x].rs == 0) std::swap(x, y);
	if (tr[y].ls == 0 && tr[y].rs == 0) {
		tr[x].v = tr[x].v * Data(tr[y].v.b, 0, 0, tr[y].v.d);
		return x;
	}
	pushdown(x);
	pushdown(y);
	merge(tr[x].ls, tr[y].ls);
	merge(tr[x].rs, tr[y].rs);
	return x;
}

ll querySumD(int p, int L, int R) {
	if (L == R) return tr[p].v.d;
	pushdown(p);
	int mid = (L + R) >> 1;
	int r = pls(querySumD(tr[p].ls, L, mid), querySumD(tr[p].rs, mid + 1, R));
	return r;
}

int root[maxn];
void dfs(int x, int const fa, int const z0) {
	modify(root[x], 1, W, 1, W, Data(0, 1, 0, 0));
	for (int i = head[x]; i; i = nxt[i]) {
		if (to[i] == fa) continue;
		dfs(to[i], x, z0);
		modify(root[to[i]], 1, W, 1, W, Data(1, 1, 0, 0));
		merge(root[x], root[to[i]]);
		delTree(root[to[i]]);
	}
	modify(root[x], 1, W, 1, d[x], Data(z0, 0, 0, 0));
	modify(root[x], 1, W, 1, W, Data(1, 0, 1, 0));
}

int inv[maxn];
ll pv[maxn], g[maxn];

void Lagrange() {
	static int f[maxn], a[maxn];
	f[0] = 1;
	for (int i = 1; i <= n + 1; ++i) {
		for (int j = n + 1; j >= 0; --j)
			f[j] = pls(f[j] * ll(mod - i) % mod, (j > 0 ? f[j - 1] : 0));
	}
	for (int i = 1; i <= n + 1; ++i) {
		for (int j = 0; j <= n + 1; ++j) a[j] = f[j];
		a[0] = a[0] * ll(mod - inv[i]) % mod;
		for (int j = 1; j <= n + 1; ++j)
			a[j] = dec(a[j], a[j - 1]) * ll(mod - inv[i]) % mod;

		ll k = pv[i];
		for (int j = 1; j <= n + 1; ++j)
			if (j < i) k = k * inv[i - j] % mod;
			else if (i < j) k = k * (mod - inv[j - i]) % mod;

		for (int j = 0; j <= n; ++j)
			g[j] = pls(g[j], k * a[j] % mod);
	}
}

int main() {
	scanf("%d%d%d", &n, &k, &W);
	int x = 0, y = 0;
	for (int i = 1; i <= n; ++i) scanf("%d", d + i);
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &x, &y);
		insert(x, y);
		insert(y, x);
	}

	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n + 1; ++i) inv[i] = ll(mod - mod / i) * inv[mod % i] % mod;

	for (int z = 1; z <= n + 1; ++z) {
		cntNode = binTop = 0;
		dfs(1, 0, z);
		pv[z] = querySumD(root[1], 1, W);
		delTree(root[1]);
	}
	
	Lagrange();
	
	int ans = 0;
	for (int i = k; i <= n; ++i) ans = pls(ans, g[i]);
	printf("%d\n", ans);
	return 0;
}