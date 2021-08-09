#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
ll const inf = 0x7fffffffffffffff;
int n = 0, m = 0;
ll ans = inf, ansA = inf, ansB = inf;
struct Edge { int u, e, a, b; ll v; };
inline bool operator<(Edge const &lhs, Edge const &rhs) { return lhs.v < rhs.v; }
Edge a[10003];
struct Point { ll x, y; };

int fa[201];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
Point MST() {
	for (int i = 0; i < n; ++i) fa[i] = i;
	sort(a + 1, a + m + 1);
	ll sumA = 0, sumB = 0;
	for (int i = 1; i <= m; ++i) {
		if (find(a[i].u) == find(a[i].e)) continue;
		fa[find(a[i].u)] = find(a[i].e);
		sumA += a[i].a; sumB += a[i].b;
	}
	if (sumA * sumB < ans) { ans = sumA * sumB; ansA = sumA; ansB = sumB; }
	return Point{sumA, sumB};
}
void solve(Point A, Point B) {
	for (int i = 1; i <= m; ++i)
		a[i].v = (A.y - B.y) * a[i].a + (B.x - A.x) * a[i].b;
	Point C = MST();
	if ((C.x - A.x) * (B.y - A.y) - (B.x - A.x) * (C.y - A.y) > 0) {
		solve(A, C);
		solve(C, B);
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i)
		scanf("%d %d %d %d", &a[i].u, &a[i].e, &a[i].a, &a[i].b);
	for (int i = 1; i <= m; ++i) a[i].v = a[i].a;
	Point A = MST();
	for (int i = 1; i <= m; ++i) a[i].v = a[i].b;
	Point B = MST();
	solve(A, B);
	printf("%lld %lld", ansA, ansB);
	return 0;
}