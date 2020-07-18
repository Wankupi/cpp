#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
inline void swap(int &a, int &b) { int c = a; a = b; b = c; }
const int maxn = 500003;
int n = 0, m = 0;
struct Point {
	int x, y;
	int p; // -2 -1 0 +*
	int id;
};
inline bool operator<(const Point &lhs, const Point &rhs) {
	return lhs.x == rhs.x ? (lhs.y == rhs.y ? lhs.p > rhs.p :lhs.y < rhs.y) : lhs.x < rhs.x;
}
Point po[maxn];
int cnt = 0;
int ys[maxn], Y = 0;
ll tr[maxn];
inline int lowbit(int x) { return x & -x; }
inline void add(int p, int x) {
	while (p <= Y) {
		tr[p] += x;
		p += lowbit(p);
	}
}
inline ll query(int p) {
	ll sum = 0;
	while (p) {
		sum += tr[p];
		p -= lowbit(p);
	}
	return sum;
}
ll ans[maxn];
int main() {
	cnt = n = read(); m = read();
	for (int i = 1; i <= n; ++i) {
		po[i].x = read(); po[i].y = read(); po[i].p = read();
		po[i].id = 0;
		ys[++Y] = po[i].y;
	}
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	for (int i = 1; i <= m; ++i) {
		x1 = read(); y1 = read(); x2 = read(); y2 = read();
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		po[++cnt] = Point{ x1 - 1,y1 - 1,-1,i };
		po[++cnt] = Point{ x2,y2,-1,i };
		po[++cnt] = Point{ x1 - 1, y2,-2,i };
		po[++cnt] = Point{ x2, y1 - 1,-2,i };
		ys[++Y] = y1 - 1;
		ys[++Y] = y2;
	}
	sort(ys + 1, ys + Y + 1);
	Y = unique(ys + 1, ys + Y + 1) - ys - 1;
	for (int i = 1; i <= cnt; ++i)
		po[i].y = lower_bound(ys + 1, ys + Y + 1, po[i].y) - ys;
	sort(po + 1, po + cnt + 1);

	for (int i = 1; i <= cnt; ++i) {
		if (po[i].p >= 0) {
			add(po[i].y, po[i].p);
		}
		else {
			ans[po[i].id] += (po[i].p == -1 ? +1 : -1) * query(po[i].y);
		}
	}
	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}