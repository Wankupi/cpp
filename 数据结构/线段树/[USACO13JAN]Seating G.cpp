#include <cstdio>
#include <algorithm>
using namespace std;
int const maxn = 500003;
int n = 0, m = 0;
struct Node {
	int mx, lem, rem, len;
	void set(int v) {
		if (v == 1) mx = lem = rem = 0;
		else mx = lem = rem = len;
	}
};
inline Node operator+(Node const &lhs, Node const &rhs) {
	Node r;
	r.mx = max(max(lhs.mx, rhs.mx), lhs.rem + rhs.lem);
	r.lem = lhs.lem + (lhs.lem == lhs.len) * rhs.lem;
	r.rem = rhs.rem + (rhs.rem == rhs.len) * lhs.rem;
	r.len = lhs.len + rhs.len;
	return r;
}
Node tr[maxn << 2];
int lazy[maxn << 2];
void Create(int p, int L, int R) {
	if (L == R) {
		tr[p].mx = tr[p].lem = tr[p].rem = tr[p].len = 1;
		return;
	}
	int mid = (L + R) >> 1;
	Create(p << 1, L, mid);
	Create(p << 1 | 1, mid + 1, R);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}
void pushDown(int p) {
	if (lazy[p] == 0) return;
	tr[p << 1].set(lazy[p]);
	tr[p << 1 | 1].set(lazy[p]);
	lazy[p << 1] = lazy[p << 1 | 1] = lazy[p];
	lazy[p] = 0;
}
void set(int p, int L, int R, int l, int r, int v) {
	if (l <= L && R <= r) {
		tr[p].set(v);
		lazy[p] = v;
		return;
	}
	pushDown(p);
	int mid = (L + R) >> 1;
	if (l <= mid) set(p << 1, L, mid, l, r, v);
	if (r > mid) set(p << 1 | 1, mid + 1, R, l, r, v);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}
int find_pos(int p, int L, int R, int a) {
	if (a >= tr[p].len) return L;
	pushDown(p);
	int mid = (L + R) >> 1;
	if (tr[p << 1].mx >= a) return find_pos(p << 1, L, mid, a);
	else if (tr[p << 1].rem + tr[p << 1 | 1].lem >= a)
		return mid - tr[p << 1].rem + 1;
	else
		return find_pos(p << 1 | 1, mid + 1, R, a);
}
int main() {
	scanf("%d %d", &n, &m);
	Create(1, 1, n);
	int failCnt = 0;
	int opt = 0, a = 0, b = 0;
	for (int i = 1; i <= m; ++i) {
		do opt = getchar(); while (opt != 'A' && opt != 'L');
		if (opt == 'A')  {
			scanf("%d", &a);
			if (tr[1].mx >= a) {
				int pos = find_pos(1, 1, n, a);
				set(1, 1, n, pos, pos + a - 1, 1);
			}
			else ++failCnt;
		}
		else {
			scanf("%d %d", &a, &b);
			set(1, 1, n, a, b, -1);
		}
	}
	printf("%d", failCnt);
	return 0;
}
