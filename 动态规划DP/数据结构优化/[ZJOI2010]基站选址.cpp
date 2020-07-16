#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200005, inf = 0x3f3f3f3f;
int n = 0, k = 0;
int d[maxn], c[maxn], s[maxn], w[maxn];
int head[maxn], nxt[maxn], to[maxn], val[maxn], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int f[maxn];
inline int min(int a, int b) { return a < b ? a : b; }
int mi[maxn << 2], lazy[maxn << 2];
inline void pushUp(int p) { mi[p] = min(mi[p << 1], mi[p << 1 | 1]); }
inline void pushDown(int p) {
	if (!lazy[p]) return;
	mi[p << 1] += lazy[p];
	mi[p << 1 | 1] += lazy[p];
	lazy[p << 1] += lazy[p];
	lazy[p << 1 | 1] += lazy[p];
	lazy[p] = 0;
}
void build(int p, int L, int R) {
	lazy[p] = 0;
	if (L == R) {
		mi[p] = f[L];
		return;
	}
	int mid = (L + R) >> 1;
	build(p << 1, L, mid);
	build(p << 1 | 1, mid + 1, R);
	pushUp(p);
}
void add(int p, int L, int R, int l, int r, int v) {
	if (l <= L && R <= r) {
		mi[p] += v;
		lazy[p] += v;
		return;
	}
	pushDown(p);
	int mid = (L + R) >> 1;
	if (l <= mid) add(p << 1, L, mid, l, r, v);
	if (r > mid) add(p << 1 | 1, mid + 1, R, l, r, v);
	pushUp(p);
}
int query(int p, int L, int R, int l, int r) { // 前缀最小值
	if (l <= L && R <= r)
		return mi[p];
	pushDown(p);
	int mid = (L + R) >> 1;
	int res = inf;
	if (l <= mid) res = min(res, query(p << 1, L, mid, l, r));
	if (r > mid) res = min(res, query(p << 1 | 1, mid + 1, R, l, r));
	return res;
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 2; i <= n; ++i) scanf("%d", d + i);
	for (int i = 1; i <= n; ++i) scanf("%d", c + i);
	for (int i = 1; i <= n; ++i) scanf("%d", s + i);
	for (int i = 1; i <= n; ++i) scanf("%d", w + i);
	++n; ++k;
	d[n] = w[n] = inf; s[n] = c[n] = 0;
	for (int i = 1; i <= n; ++i) {
		int L = lower_bound(d + 1, d + n + 1, d[i] - s[i]) - d; // 最左的能覆盖的
		int R = lower_bound(d + 1, d + n + 1, d[i] + s[i]) - d;
		if (d[R] - d[i] > s[i]) --R; // 第一个不能覆盖
		insert(R, L, w[i]);
	}
	int tem = 0;
	for (int i = 1; i <= n; ++i) {
		f[i] = tem + c[i];
		for (int j = head[i]; j; j = nxt[j])
			tem += val[j];
	}
	int ans = 0x7fffffff;
	for (int q = 2; q <= k; ++q) {
		build(1, 1, n);
		for (int i = 1; i <= n; ++i) {
			if (i >= q)
				f[i] = query(1, 1, n, q - 1, i - 1) + c[i];
			else f[i] = c[i];
			for (int j = head[i]; j; j = nxt[j])
				if (to[j] > 1)
					add(1, 1, n, 1, to[j] - 1, w[j]);
		}
		ans = min(ans, f[n]);
	}
	printf("%d", ans);
	return 0;
}