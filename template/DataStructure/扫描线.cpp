#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int n = 0;
struct Square {
	int x1, y1, x2, y2;
};
Square sq[100003];
int xs[200003], cx = 0; // 记录所有的x值，离散化
struct Line {
	int y, l, r, val;
};
inline bool operator<(const Line &lhs, const Line &rhs) {
	return lhs.y == rhs.y ? lhs.val < rhs.val : lhs.y < rhs.y;
}
Line lin[200003];
const int maxn = 800007;
int t[maxn], len[maxn]; // 这个节点被 完全覆盖 了多少次， 它被覆盖的总长度是多少。

inline void pushUp(int p, int L, int R) {
	if (L == R) len[p] = 0;
	else len[p] = len[p << 1] + len[p << 1 | 1];
}
void modify(int p, int L, int R, Line li) {
	if (li.l <= L && R <= li.r) {
		t[p] += li.val;
		if (t[p]) len[p] = xs[R+1] - xs[L];
		else pushUp(p, L, R);
		return;
	}
	int mid = (L + R) >> 1;
	if (li.l <= mid) modify(p << 1, L, mid, li);
	if (li.r > mid) modify(p << 1 | 1, mid + 1, R, li);
	if (t[p] == 0) pushUp(p, L, R);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d%d", &sq[i].x1, &sq[i].y1, &sq[i].x2, &sq[i].y2);
		xs[++cx] = sq[i].x1;
		xs[++cx] = sq[i].x2;
	}
	sort(xs + 1, xs + cx + 1);
	cx = unique(xs + 1, xs + cx + 1) - xs - 1;
	for (int i = 1; i <= n; ++i) {
		int nL = lower_bound(xs + 1, xs + cx + 1, sq[i].x1) - xs,
			nR = lower_bound(xs + 1, xs + cx + 1, sq[i].x2) - xs - 1; // 变块 important
		lin[i * 2 - 1] = Line{ sq[i].y1, nL, nR, 1 };
		lin[i * 2] = Line{ sq[i].y2, nL, nR, -1 };
	}
	sort(lin + 1, lin + 2 * n + 1);
	ll ans = 0, lastY = 0;
	for (int i = 1, j = 1; i <= 2 * n; i = j) {
		ans += (long long)len[1] * (lin[i].y - lastY);
		lastY = lin[i].y;
		while (lin[i].y == lin[j].y) {
			modify(1, 1, cx, lin[j]);
			++j;
		}
	}
	printf("%lld", ans);
	return 0;
}