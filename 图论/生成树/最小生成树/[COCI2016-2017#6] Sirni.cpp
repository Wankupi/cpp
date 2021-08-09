#include <algorithm>
#include <cctype>
#include <cstdio>
#include <vector>
using namespace std;

int const maxn = 100003;
inline int read() {
	int x = 0, c = getchar();
	while (!isdigit(c))
		c = getchar();
	while (isdigit(c)) {
		x = 10 * x + c - '0';
		c = getchar();
	}
	return x;
}

int n = 0;

int p[maxn], Mx = 0;

//int right[maxn];
//int getRigth(int x) { return right[x] == x ? x : right[x] = getRigth(right[x]); }

int fa[maxn], siz[maxn];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) {
	x = find(x); y = find(y);
	if (siz[x] < siz[y]) swap(x, y);
	fa[y] = x;
	siz[x] += siz[y];
}

struct Edge {
	int x, y;
	int v;
};
bool operator<(Edge const &lhs, Edge const &rhs) { return lhs.v < rhs.v; }
vector<Edge> q;

inline void addEdges(int id) {
	int x = p[id];
	for (int y = x; y <= Mx; y += x) {
		int k = lower_bound(p + id + 1, p + n + 1, y) - p;
		if (k <= n && p[k] / x == y / x) q.push_back(Edge{ id, k, p[k] % p[id] });
	}
}

int main() {
	n = read();
	for (int i = 1; i <= n; ++i)
		p[i] = read();
	sort(p + 1, p + n + 1);
	n = unique(p + 1, p + n + 1) - p - 1;
	Mx = p[n];
	for (int i = 1; i <= n + 1; ++i) {
		fa[i] = i;
		siz[i] = 1;
	}
	long long ans = 0;
	for (int i = 1; i <= n; ++i)
		addEdges(i);
	sort(q.begin(), q.end());
	for (auto e : q) {
		int yy = find(e.y), xx = find(e.x);
		if (yy != xx) {
			ans += e.v;
			merge(xx, yy);
		}
	}
	printf("%lld", ans);
	return 0;
}