#include <cstdio>
#include <cstring>
const int maxn = 203;
int n = 0, m = 0, k = 0;
char map[maxn][maxn];
int t[maxn], d[maxn];
int f[maxn][maxn];
inline int max(int a, int b) { return a < b ? b : a; }
int q[maxn], val[maxn], l = 1, r = 0;
inline void push(int id, int v) {
	while (l <= r && val[r] < v) --r;
	++r;
	q[r] = id; val[r] = v;
}
inline void popL(int limit) { while (l <= r && q[l] < limit) ++l; }
inline void popR(int limit) { while (l <= r && q[l] > limit) ++l; }
inline void clear() { l = 1; r = 0; }
void Left(int time) {
	for (int Line = 1; Line <= n; ++Line) {
		clear();
		for (int i = m; i >= 1; --i) {
			if (map[Line][i] == 'x') {
				clear();
				continue;
			}
			if (f[Line][i] != -1) push(i, f[Line][i] + i);
			popR(i + time);
			if (l <= r) f[Line][i] = val[l] - i;
		}
	}
}
void Right(int time) {
	for (int Line = 1; Line <= n; ++Line) {
		clear();
		for (int i = 1; i <= m; ++i) {
			if (map[Line][i] == 'x') {
				clear();
				continue;
			}
			if (f[Line][i] != -1) push(i, f[Line][i] - i);
			popL(i - time);
			if (l <= r) f[Line][i] = val[l] + i;
		}
	}
}
void Up(int time) {
	for (int Row = 1; Row <= m; ++Row) {
		clear();
		for (int i = n; i >= 1; --i) {
			if (map[i][Row] == 'x') {
				clear();
				continue;
			}
			if (f[i][Row] != -1) push(i, f[i][Row] + i);
			popR(i + time);
			if (l <= r) f[i][Row] = val[l] - i;
		}
	}
}
void Down(int time) {
	for (int Row = 1; Row <= m; ++Row) {
		clear();
		for (int i = 1; i <= n; ++i) {
			if (map[i][Row] == 'x') {
				clear();
				continue;
			}
			if (f[i][Row] != -1) push(i, f[i][Row] - i);
			popL(i - time);
			if (l <= r) f[i][Row] = val[l] + i;
		}
	}
}
int main() {
	int x0 = 0, y0 = 0, Begin = 0, End = 0;
	scanf("%d %d %d %d %d\n", &n, &m, &y0, &x0, &k);
	for (int i = 1; i <= n; ++i) scanf("%s\n", map[i] + 1);
	for (int i = 1; i <= k; ++i) {
		scanf("%d %d %d", &Begin, &End, d + i);
		t[i] = End - Begin + 1;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) f[i][j] = -1;
	f[y0][x0] = 0;
	for (int i = 1; i <= k; ++i) {
		if (d[i] == 1) Up(t[i]);
		else if (d[i] == 2) Down(t[i]);
		else if (d[i] == 3) Left(t[i]);
		else Right(t[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			ans = max(ans, f[i][j]);
	}
	printf("%d", ans);
	return 0;
}