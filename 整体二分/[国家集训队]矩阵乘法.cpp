#include <cstdio>
int n = 0, q = 0;
struct Data {
	static int lowbit(int x) { return x & -x; }
	int tr[503][503];
	void add(int y, int x, int v) {
		for (int i = y; i <= n; i += lowbit(i))
			for (int j = x; j <= n; j += lowbit(j))
				tr[i][j] += v;
	}
	int query(int y, int x) {
		int sum = 0;
		for (int i = y; i; i -= lowbit(i))
			for (int j = x; j; j -= lowbit(j))
				sum += tr[i][j];
		return sum;
	}
	int query(int x1, int y1, int x2, int y2) { return query(y2, x2) - query(y2, x1 - 1) - query(y1 - 1, x2) + query(y1 - 1, x1 - 1); }
} data;
struct Query {
	int x1, y1, x2, y2, k, id, type;
};
Query opt[310003], q1[310003], q2[310003];
int cnt = 0;
int ans[60003];
void solve(int L, int R, int ql, int qr) {
	if (ql > qr) return;
	if (L == R) {
		for (int i = ql; i <= qr; ++i)
			if (opt[i].type == 2)
				ans[opt[i].id] = L;
		return;
	}
	int mid = (L + R) >> 1;
	int cL = 0, cR = 0;
	for (int i = ql; i <= qr; ++i)
		if (opt[i].type == 1) {
			if (opt[i].k <= mid) {
				data.add(opt[i].y1, opt[i].x1, 1);
				q1[++cL] = opt[i];
			}
			else q2[++cR] = opt[i];
		}
		else {
			int cn = data.query(opt[i].x1, opt[i].y1, opt[i].x2, opt[i].y2);
			if (cn >= opt[i].k)
				q1[++cL] = opt[i];
			else {
				opt[i].k -= cn;
				q2[++cR] = opt[i];
			}
		}
	for (int i = 1; i <= cL; ++i) if (q1[i].type == 1) data.add(q1[i].y1, q1[i].x1, -1);
	for (int i = 1; i <= cL; ++i) opt[ql + i - 1] = q1[i];
	for (int i = 1; i <= cR; ++i) opt[ql + cL + i - 1] = q2[i];
	solve(L, mid, ql, ql + cL - 1);
	solve(mid + 1, R, ql + cL, qr);
}
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }
int main() {
	scanf("%d%d", &n, &q);
	int minV = 0x7fffffff, maxV = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			++cnt;
			opt[cnt].x1 = j;
			opt[cnt].y1 = i;
			opt[cnt].type = 1;
			scanf("%d", &opt[cnt].k);
			minV = min(minV, opt[cnt].k);
			maxV = max(maxV, opt[cnt].k);
		}
	}
	for (int i = 1; i <= q; ++i) {
		++cnt;
		scanf("%d%d%d%d%d", &opt[cnt].y1, &opt[cnt].x1, &opt[cnt].y2, &opt[cnt].x2, &opt[cnt].k);
		opt[cnt].id = i;
		opt[cnt].type = 2;
	}
	solve(minV, maxV, 1, cnt);
	for (int i = 1; i <= q; ++i)
		printf("%d\n", ans[i]);
	return 0;
}