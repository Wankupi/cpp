#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
ll const inf = 0x7fffffffffff;
int const maxn = 100003, maxP = maxn * 20;

int n = 0;
int a[maxn], b[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }

struct Line {
	ll k, b;
	ll f(ll x) { return k * x + b; }
};

Line tr[maxP];
int lc[maxP], rc[maxP], cntP = 0;

void add(int &p, int L, int R, Line a) {
	if (p == 0) { p = ++cntP; tr[p] = a; return; }
	int mid = int(floor((L + R) / 2.0));
	if (tr[p].f(mid) >= a.f(mid)) std::swap(tr[p], a);
	if (tr[p].f(L) <= a.f(L) && tr[p].f(R) <= a.f(R)) return;
	if (tr[p].f(L) > a.f(L)) add(lc[p], L, mid, a);
	else add(rc[p], mid + 1, R, a);
}
ll query(int p, int L, int R, ll x) {
	if (p == 0) return inf;
	int mid = int(floor((L + R) / 2.0));
	ll v = tr[p].f(x);
	if (L == R) return v;
	if (x <= mid) return std::min(v, query(lc[p], L, mid, x));
	else return std::min(v, query(rc[p], mid + 1, R, x));
}
int merge(int x, int y, int L, int R) {
	if (x == 0 || y == 0) return x | y;
	add(x, L, R, tr[y]);
	int mid = int(floor((L + R) / 2.0));
	lc[x] = merge(lc[x], lc[y], L, mid);
	rc[x] = merge(rc[x], rc[y], mid + 1, R);
	return x;
}
int root[maxn];
ll f[maxn];
void dfs(int x, int fa) {
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa) {
			dfs(to[i], x);
			root[x] = merge(root[x], root[to[i]], -100000, 100000);
		}
	if (root[x] == 0) f[x] = 0;
	else f[x] = query(root[x], -100000, 100000, a[x]);
	add(root[x], -100000, 100000, Line{b[x], f[x]});
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) scanf("%d", b + i);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		insert(x, y); insert(y, x);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i) printf("%lld ", f[i]);
	return 0;
}