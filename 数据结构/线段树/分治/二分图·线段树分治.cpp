#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 100003;
inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
int n = 0, m = 0, k = 0;
struct Line {
	int x, y;
};
vector<Line> tr[maxn << 2];
void add(int p, int L, int R, int l, int r, Line line) {
	if (l <= L && R <= r) { tr[p].push_back(line); return; }
	int mid = (L + R) >> 1;
	if (l <= mid) add(p << 1, L, mid, l, r, line);
	if (r > mid) add(p << 1 | 1, mid + 1, R, l, r, line);
}
int fa[maxn << 1], siz[maxn << 1];
int ds[maxn << 1], df[maxn << 1], dsiz[maxn << 1], top = 0;
inline int find(int x) { while (fa[x] != x) x = fa[x]; return x; }
void merge(int x, int y) {
	x = find(x); y = find(y);
	if (siz[x] > siz[y]) swap(x, y);
	fa[x] = y;
	siz[y] += siz[x];
	++top;
	df[top] = y;
	ds[top] = x;
	dsiz[top] = siz[x];
}
void dfs(int p, int L, int R) {
	int lastTop = top;
	bool crash = false;
	for (auto li : tr[p]) {
		if (find(li.x) == find(li.y)) { crash = true; break; }
		merge(li.x, li.y + n);
		merge(li.x + n, li.y);
	}
	if (crash) for (int i = L; i <= R; ++i) puts("No");
	else {
		if (L == R) puts("Yes");
		else {
			int mid = (L + R) >> 1;
			dfs(p << 1, L, mid);
			dfs(p << 1 | 1, mid + 1, R);
		}
	}
	while (top > lastTop) {
		siz[df[top]] -= dsiz[top];
		fa[ds[top]] = ds[top];
		--top;
	}
}
int main() {
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= 2 * n; ++i)
		fa[i] = i, siz[i] = 1;
	int x = 0, y = 0, l = 0, r = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d %d", &x, &y, &l, &r);
		if (l != r) add(1, 1, k, l + 1, r, Line{ x, y });
	}
	dfs(1, 1, k);
	return 0;
}