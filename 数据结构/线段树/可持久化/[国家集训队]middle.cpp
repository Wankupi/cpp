/*
细节：
中位数的位置 1/2 > or <

二分 套 可持久化线段树 
可持久化线段树 上所有权值小于某值的点值为 -1
*/
#include <algorithm>
#include <cstdio>
#include <vector>
const int maxn = 20003;
using namespace std;
inline int read(int &x) {
	x = 0;
	int c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x;
}
int n = 0;
int a[maxn], A[maxn], cA = 0;
vector<int> poss[maxn];
int root[maxn], limit = 0;
namespace Seg {
	struct Node {
		Node(int sum = 0) {s = sum; lm = rm = sum; lc = rc = 0; }
		int lm, rm, s;
		int lc, rc;
	};
	inline void Combine(Node &re, const Node &lhs, const Node &rhs) {
		re.s = lhs.s + rhs.s;
		re.lm = max(lhs.lm, lhs.s + rhs.lm);
		re.rm = max(rhs.rm, rhs.s + lhs.rm);
	}
	Node tr[maxn << 5];
	int cT = 0;
	inline void pushUp(int p) {
		Combine(tr[p], tr[tr[p].lc], tr[tr[p].rc]);
	}
	void Create(int &p, int L, int R) {
		if (p == 0) p = ++cT;
		if (L == R) {
			tr[p] = Node(1);
			return;
		}
		int mid = (L + R) >> 1;
		Create(tr[p].lc, L, mid);
		Create(tr[p].rc, mid + 1, R);
		pushUp(p);
	}
	void SetFuOne(int &p, int L, int R, int x) {
		if (p <= limit) {
			tr[++cT] = tr[p];
			p = cT;
		}
		if (L == R) {
			tr[p].lm = tr[p].rm = tr[p].s = -1;
			return;
		}
		int mid = (L + R) >> 1;
		if (x <= mid)
			SetFuOne(tr[p].lc, L, mid, x);
		else
			SetFuOne(tr[p].rc, mid + 1, R, x);
		pushUp(p);
	}
	Node Query(int p, int L, int R, int l, int r) {
		//if (l > r) return Node();
		if (l <= L && R <= r)
			return tr[p];
		int mid = (L + R) >> 1;
		if (r <= mid)
			return Query(tr[p].lc, L, mid, l, r);
		else if (l > mid)
			return Query(tr[p].rc, mid + 1, R, l, r);
		else {
			Node re;
			Combine(re, Query(tr[p].lc, L, mid, l, r), Query(tr[p].rc, mid + 1, R, l, r));
			return re;
		}
	}
} // namespace Seg

int query(int a, int b, int c, int d) {
	int  L = 1, R = cA, mid = 0;
	int ans = 0;
	while (L <= R) {
		mid = (L + R) >> 1;
		int sum = 0;
		if (b + 1 <= c - 1) sum += Seg::Query(root[mid], 0, n - 1, b + 1, c - 1).s;
		sum += Seg::Query(root[mid], 0, n - 1, a, b).rm + Seg::Query(root[mid], 0, n - 1, c, d).lm;
		if (sum >= 0) ans = mid, L = mid + 1;
		else R = mid - 1;
	}
	return A[ans];
}
int main() {
	read(n);
	for (int i = 0; i < n; ++i) {
		read(a[i]);
		A[i + 1] = a[i];
	}
	sort(A + 1, A + n + 1);
	cA = unique(A + 1, A + n + 1) - A - 1;
	for (int i = 0; i < n; ++i) {
		a[i] = lower_bound(A + 1, A + cA + 1, a[i]) - A;
		poss[a[i]].push_back(i);
	}
	Seg::Create(root[1], 0, n - 1);
	for (int i = 2; i <= cA; ++i) {
		limit = Seg::cT;
		root[i] = root[i - 1];
		for (int j = 0; j < poss[i - 1].size(); ++j)
			Seg::SetFuOne(root[i], 0, n - 1, poss[i - 1][j]);
	}
	int m = 0, q[4], LastAns = 0;
	read(m);
	for (int i = 1; i <= m; ++i) {
		read(q[0]); read(q[1]); read(q[2]); read(q[3]);
		q[0] = (q[0] + LastAns) % n;
		q[1] = (q[1] + LastAns) % n;
		q[2] = (q[2] + LastAns) % n;
		q[3] = (q[3] + LastAns) % n;
		sort(q, q + 4);
		LastAns = query(q[0], q[1], q[2], q[3]);
		printf("%d\n", LastAns);
	}
	return 0;
}