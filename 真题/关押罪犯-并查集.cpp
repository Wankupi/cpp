#include <cstdio>
#include <algorithm>
using namespace std;
struct Line {
	int u = 0;
	int e = 0;
	int v = 0;
	bool operator<(const Line &rhs) const {
		return v > rhs.v;
	}
};
Line b[100005];
int fa[20001];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(y)] = find(x); }
int enemy[20001];
int main() {
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1; i <= m; ++i)
		scanf("%d%d%d", &b[i].u, &b[i].e, &b[i].v);
	sort(b + 1, b + m + 1);
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		x = find(b[i].u); y = find(b[i].e);
		if (x == y) {
			printf("%d", b[i].v);
			return 0;
		}
		if (enemy[x]) merge(y, enemy[x]);
		else enemy[x] = y;
		if (enemy[y]) merge(x, enemy[y]);
		else enemy[y] = x;
	}
	putchar('0');
	return 0;
}