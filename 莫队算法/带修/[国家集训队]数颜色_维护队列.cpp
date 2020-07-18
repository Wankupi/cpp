#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x;
}
const int maxn = 133350;
int n = 0, m = 0, block = 0;
int a[maxn], b[maxn];
struct Modify {
	int pos;
	int from, to;
};
Modify change[maxn];
struct Query {
	int id;
	int l, r, t;
};
inline bool operator<(const Query &lhs, const Query &rhs) { return (lhs.l / block) == (rhs.l / block) ? (lhs.r / block == rhs.r / block ? lhs.t < rhs.t : lhs.r < rhs.r) : lhs.l < rhs.l; }
Query qu[maxn];
int A = 0, B = 0;
int ans[maxn];
int l = 1, r = 0, time = 0, ANS = 0;
int tong[1000001];
inline void Add(int x) { if (++tong[x] == 1) ++ANS; }
inline void Remove(int x) { if (--tong[x] == 0) --ANS; }
inline void TimeAhead(int k) {
	Modify &ch = change[k];
	a[ch.pos] = ch.to;
	if (l <= ch.pos && ch.pos <= r) {
		Remove(ch.from);
		Add(ch.to);
	}
}
inline void timeBack(int k) {
	Modify &ch = change[k];
	a[ch.pos] = ch.from;
	if (l <= ch.pos && ch.pos <= r) {
		Remove(ch.to);
		Add(ch.from);
	}
}
int main() {
	n = read(); m = read();
	block = ceil(exp(log(n) * 2.0 / 3.0));
	for (int i = 1; i <= n; ++i) a[i] = b[i] = read();
	int opt = 0, x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		do opt = getchar(); while (opt != 'Q' && opt != 'R');
		x = read(); y = read();
		if (opt == 'Q') {
			++B;
			qu[B].id = B;
			qu[B].l = x; qu[B].r = y; qu[B].t = A;
		}
		else {
			++A;
			change[A].pos = x;
			change[A].from = b[x];
			b[x] = change[A].to = y;
		}
	}
	sort(qu + 1, qu + B + 1);
	for (int i = 1; i <= B; ++i) {
		while (r < qu[i].r) Add(a[++r]);
		while (r > qu[i].r) Remove(a[r--]);
		while (qu[i].l < l) Add(a[--l]);
		while (l < qu[i].l) Remove(a[l++]);
		while (time < qu[i].t) TimeAhead(++time);
		while (qu[i].t < time) timeBack(time--);
		ans[qu[i].id] = ANS;
	}
	for (int i = 1; i <= B; ++i) printf("%d\n", ans[i]);
	return 0;
}