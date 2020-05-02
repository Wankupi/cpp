#include <cstdio>
#include <cstring>
inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
struct edge { int x, y; };
bool operator<(const edge&lhs, const edge&rhs) { return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x; }
int n = 0, m = 0;
edge ed[10005];
int rank[205];
int fa[2000];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) {
	fa[find(y)] = find(x);
}
void clear() {
	memset(ed, 0, sizeof(ed));
	memset(rank, 0, sizeof(rank));
}
bool banana(edge& a, edge& b) {
	if (a.x == b.x || a.y == b.y || a.x == b.y || a.y == b.x) return false;
	if (a.x < b.x && a.y < b.y && b.x < a.y) return true;
	if (a.x > b.x && a.y > b.y && a.x < b.y) return true;
	return false;
}
bool _main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
		scanf("%d%d", &ed[i].x, &ed[i].y);
	int x = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		rank[x] = i;
	}
	if (m > 3 * n + 6) return false;
	for (int i = 1; i <= m; ++i) {
		ed[i].x = rank[ed[i].x];
		ed[i].y = rank[ed[i].y];
		if (ed[i].x > ed[i].y) swap(ed[i].x, ed[i].y);
	}
	for (int i = 1; i <= 2 * m; ++i) fa[i] = i;
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j < i; ++j)
			if (banana(ed[i], ed[j])) {
				if (find(i) == find(j)) return false;
				merge(i, j + m);
				merge(i + m, j);
			}
	return true;
}
int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		clear();
		if (_main())
			printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}