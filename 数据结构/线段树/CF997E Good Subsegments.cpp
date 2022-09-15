#include <cstdio>
#include <algorithm>
using ll = long long;
int const maxn = 120003;
int n = 0, m = 0;
int a[maxn];
ll ans[maxn];
struct Query { int l, r; int id; };
bool operator<(Query const &lhs, Query const &rhs) { return lhs.r == rhs.r ? lhs.l < rhs.l : lhs.r < rhs.r; }
Query qs[maxn];

struct Node {
	int mi;
	int cnt;
	ll res;
};
inline Node operator+(Node const &A, Node const &B) {
	Node r{ std::min(A.mi, B.mi), 0, A.res + B.res};
	if (r.mi == A.mi) r.cnt += A.cnt;
	if (r.mi == B.mi) r.cnt += B.cnt;
	return r;
}

Node tr[maxn << 2];
int Lmer[maxn << 2], Ladd[maxn << 2];

void create(int p, int L, int R) {
	if (L == R) {
		tr[p] = Node{ L, 1, 0 };
		return;
	}
	int mid = (L + R) >> 1;
	create(p << 1, L, mid);
	create(p << 1 | 1, mid + 1, R);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}

inline void addMin(int p, int v) { tr[p].mi += v; Ladd[p] += v; }
inline void addMerge(int p, int v) { Lmer[p] += v; tr[p].res += ll(v) * tr[p].cnt; }

void pushdown(int p, int L, int R) {
	if (L == R) return;
	// 先加
	if (Ladd[p]) {
		addMin(p << 1, Ladd[p]);
		addMin(p << 1 | 1, Ladd[p]);
		Ladd[p] = 0;
	}
	if (Lmer[p]) {
		if (tr[p].mi == tr[p << 1].mi) addMerge(p << 1, Lmer[p]);
		if (tr[p].mi == tr[p << 1 | 1].mi) addMerge(p << 1 | 1, Lmer[p]);
		Lmer[p] = 0;
	}
}
void add(int p, int L, int R, int l, int r, int v) {
	if (l <= L && R <= r) {
		addMin(p, v);
		return;
	}
	pushdown(p, L, R);
	int mid = (L + R) >> 1;
	if (l <= mid) add(p << 1, L, mid, l, r, v);
	if (r > mid) add(p << 1 | 1, mid + 1, R, l, r, v);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}

ll query(int p, int L, int R, int l, int r) {
	if (l <= L && R <= r) return tr[p].res;
	pushdown(p, L, R);
	int mid = (L + R) >> 1;
	if (r <= mid) return query(p << 1, L, mid, l, r);
	else if (l > mid) return query(p << 1 | 1, mid + 1, R, l, r);
	else return query(p << 1, L, mid, l, r) + query(p << 1 | 1, mid + 1, R, l, r);
}

int st1[maxn], top1 = 0; // 递增，min
int st2[maxn], top2 = 0; // 递减，max

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) { scanf("%d %d", &qs[i].l, &qs[i].r); qs[i].id = i; }
	std::sort(qs + 1, qs + m + 1);
	create(1, 1, n);
	for (int r = 1, cur = 1; r <= n; ++r) {
		add(1, 1, n, 1, n, -1);
		while (top1 && a[st1[top1]] >= a[r]) {
			int _l = st1[top1 - 1] + 1, _r = st1[top1];
			add(1, 1, n, _l, _r, a[st1[top1]] - a[r]);
			--top1;
		}
		st1[++top1] = r;
		while (top2 && a[st2[top2]] <= a[r]) {
			int _l = st2[top2 - 1] + 1, _r = st2[top2];
			add(1, 1, n, _l, _r, a[r] - a[st2[top2]]);
			--top2;
		}
		st2[++top2] = r;
		addMerge(1, 1);
		while (cur <= m && qs[cur].r == r) {
			ll res = query(1, 1, n, qs[cur].l, r);
			ans[qs[cur].id] = res;
			++cur;
		}
	}
	for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
	return 0;
}

// r = max - min + l
