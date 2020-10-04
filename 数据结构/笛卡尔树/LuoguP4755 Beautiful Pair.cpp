#include <algorithm>
#include <cstdio>
using namespace std;
int const maxn = 100003;
int n = 0;
int a[maxn], A[maxn], cA = 0;
struct Node {
	int sum;
	int lc, rc;
};
Node tr[maxn * 20];
int cntStr = 0;
void Create(int &p, int L, int R) {
	p = ++cntStr;
	if (L == R) return;
	int mid = (L + R) >> 1;
	Create(tr[p].lc, L, mid);
	Create(tr[p].rc, mid + 1, R);
}
void add(int &p, int L, int R, int x) {
	tr[++cntStr] = tr[p];
	p = cntStr;
	if (L == R) { ++tr[p].sum; return; }
	int mid = (L + R) >> 1;
	if (x <= mid) add(tr[p].lc, L, mid, x);
	else add(tr[p].rc, mid + 1, R, x);
	tr[p].sum = tr[tr[p].lc].sum + tr[tr[p].rc].sum;
}
int query_Less(int p, int L, int R, int x) {
	if (x >= R) return tr[p].sum;
	int mid = (L + R) >> 1;
	return query_Less(tr[p].lc, L, mid, x) + (x > mid ? query_Less(tr[p].rc, mid + 1, R, x) : 0);
}
int root[maxn];
int st[maxn], top = 0;
int ls[maxn], rs[maxn];
long long ans = 0;
void solve(int p, int L, int R) {
	if (L > R) return;
	int L1 = L, R1 = p - 1, L2 = p + 1, R2 = R;
	if (R2 - L2 < R1 - L1) { std::swap(L1, L2); std::swap(R1, R2); }
	for (int i = L1; i <= R1; ++i) {
		int k = A[a[p]] / A[a[i]];
		k = upper_bound(A + 1, A + cA + 1, k) - A - 1;
		if (k < 1) continue;
		ans += query_Less(root[R2], 1, cA, k) - query_Less(root[L2 - 1], 1, cA, k);
	}
	int k = upper_bound(A + 1, A + cA + 1, 1) - A - 1;
	if (k > 0) ans += query_Less(root[R], 1, cA, k) - query_Less(root[L - 1], 1, cA, k);
	solve(ls[p], L, p - 1);
	solve(rs[p], p + 1, R);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		A[i] = a[i];
	}
	sort(A + 1, A + n + 1);
	cA = unique(A + 1, A + n + 1) - A - 1;
	for (int i = 1; i <= n; ++i)
		a[i] = lower_bound(A + 1, A + cA + 1, a[i]) - A;
	Create(root[0], 1, cA);
	for (int i = 1; i <= n; ++i) {
		root[i] = root[i - 1];
		add(root[i], 1, cA, a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		int cur = top;
		while (cur > 0 && a[i] >= a[st[cur]]) --cur;
		if (cur) rs[st[cur]] = i;
		if (cur != top) ls[i] = st[cur + 1];
		st[++cur] = i;
		top = cur;
	}
	solve(st[1], 1, n);
	printf("%lld", ans);
	return 0;
}