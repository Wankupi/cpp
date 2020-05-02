#include <algorithm>
#include <cstdio>
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }
int read() {
	int x = 0, c = getchar();
	while (c < '0' || c>'9') c = getchar();
	while ('0' <= c && c <= '9') { x = 10 * x + c - '0'; c = getchar(); }
	return x;
}
namespace SegmentTree {
	struct Node {
		int lc, rc;
		int mx, lazy;
	};
	Node tree[2000000];
	int cnt = 0;
	int l = 0, r = 0, v = 0;
	inline int CreateNew() {
		++cnt;
		tree[cnt].lazy = tree[cnt].mx = 0;
		return cnt;
	}
	inline void pushDown(int p) {
		Node &lc = tree[tree[p].lc], &rc = tree[tree[p].rc];
		lc.mx += tree[p].lazy;
		lc.lazy += tree[p].lazy;
		rc.mx += tree[p].lazy;
		rc.lazy += tree[p].lazy;
		tree[p].lazy = 0;
	}
	void add(int p, int L, int R) {
		if (l <= L && R <= r) {
			tree[p].mx += v;
			tree[p].lazy += v;
			return;
		}
		if (tree[p].lc == 0 && L != R) {
			tree[p].lc = CreateNew();
			tree[p].rc = CreateNew();
		}
		if (L != R && tree[p].lazy != 0)
			pushDown(p);
		int mid = (L + R) >> 1;
		if (l <= mid) add(tree[p].lc, L, mid);
		if (r > mid) add(tree[p].rc, mid + 1, R);
		tree[p].mx = max(tree[tree[p].lc].mx, tree[tree[p].rc].mx);
	}
} // namespace SegmentTree
struct interval {
	interval() :l(0), r(0) {}
	int l, r;
	int length;
};
bool operator<(const interval &lhs, const interval &rhs) { return lhs.length < rhs.length; }
int n = 0, m = 0;
interval a[500005];
inline void add(interval in, int val) {// 区间加，返回区间最大值
	SegmentTree::l = in.l;
	SegmentTree::r = in.r;
	SegmentTree::v = val;
	SegmentTree::add(0, 0, 1000000);
}
inline int maxValue() {
	return SegmentTree::tree[0].mx;
}
int lsh[1000005], lshcnt = 0;
int main() {
	n = read(); m = read();
	for (int i = 1; i <= n; ++i) {
		a[i].l = read(); a[i].r = read();
		a[i].length = a[i].r - a[i].l;
		lsh[++lshcnt] = a[i].l;
		if (a[i].l != a[i].r) lsh[++lshcnt] = a[i].r;
	}
	std::sort(a + 1, a + n + 1);
	std::sort(lsh + 1, lsh + lshcnt + 1);
	int *LSHend = std::unique(lsh + 1, lsh + lshcnt + 1);
	for (int i = 1; i <= n; ++i) {
		a[i].l = std::lower_bound(lsh + 1, LSHend, a[i].l) - lsh;
		a[i].r = std::lower_bound(lsh + 1, LSHend, a[i].r) - lsh;
	}
	int L = 1, R = 0;
	int ans = 0x7fffffff;
	while (L < n) {
		if (maxValue() >= m) ans = min(ans, a[R].length - a[L].length);
		while (R < n && maxValue() < m) {
			add(a[++R], +1);
			if (maxValue() >= m)
				ans = min(ans, a[R].length - a[L].length);
		}
		add(a[L++], -1);
	}
	printf("%d", ans == 0x7fffffff ? -1 : ans);
	return 0;
}