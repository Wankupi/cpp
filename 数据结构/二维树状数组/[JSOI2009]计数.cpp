#include <cstdio>
// typedef long long ll;
int n = 0, m = 0;
int a[303][303];
inline int lowbit(int x) { return x & -x; }
int tr[101][303][303];
inline void Add(int c, int x, int y, int v) {
	for (int i = x; i <= n; i += lowbit(i))
		for (int j = y; j <= m; j += lowbit(j))
			tr[c][i][j] += v;
}
inline int query(int c,int x, int y) {
	int sum = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		for (int j = y; j > 0; j -= lowbit(j))
			sum += tr[c][i][j];
	return sum;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int y = 1; y <= n; ++y)
		for (int x = 1; x <= m; ++x) {
			scanf("%d", &a[y][x]);
			Add(a[y][x], y, x, 1);
		}
	int q = 0;
	scanf("%d", &q);
	int opt = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, c = 0;
	for (int i = 1; i <= q; ++i) {
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d %d %d", &x1, &y1, &c);
			Add(a[x1][y1], x1, y1, -1);
			a[x1][y1] = c;
			Add(a[x1][y1], x1, y1, +1);
		}
		else {
			scanf("%d %d %d %d %d", &x1, &x2, &y1, &y2, &c);
			int ans = query(c,x2, y2) - query(c,x1 - 1, y2) - query(c,x2, y1 - 1) + query(c,x1 - 1, y1 - 1);
			printf("%d\n", ans);
		}
	}
	return 0;
}