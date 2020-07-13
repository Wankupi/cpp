#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;
int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int n = 0, m = 0, block = 0, N = 100000, mN = 0;
int a[100003];
struct Query {
	int opt, l, r, x, id;
};
inline bool operator<(const Query &lhs, const Query &rhs) { return (lhs.l / block) == (rhs.l / block) ? lhs.r < rhs.r : lhs.l < rhs.l; }
inline bool cmp2(const Query &lhs, const Query &rhs) { return lhs.x < rhs.x; }
Query q[100003], q2[100003];
int cnt[100003], cc = 0;
bitset<100005> s1, s2, ans;
inline void add(int x) { if (cnt[x]++ == 0) s1[x] = s2[N - x] = true; }
inline void del(int x) { if (--cnt[x] == 0) s1[x] = s2[N - x] = false; }
int pre[100003], lef[100003];
inline int max(int a, int b) { return a < b ? b : a; }
int main() {
	n = read(); m = read();
	block = int(sqrt(n)) + 1;
	for (int i = 1; i <= n; ++i) {
		a[i] = read(); if (mN < a[i]) mN = a[i];
	}
	for (int i = 1; i <= m; ++i) {
		q[i].opt = read(); q[i].l = read();
		q[i].r = read(); q[i].x = read();
		q[i].id = i;
		if (q[i].opt == 4 && q[i].x < 500) q2[++cc] = q[i];
	}
	sort(q + 1, q + m + 1);
	sort(q2 + 1, q2 + cc + 1, cmp2);
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i) {
		while (r < q[i].r) add(a[++r]);
		while (q[i].r < r) del(a[r--]);
		while (q[i].l < l) add(a[--l]);
		while (l < q[i].l) del(a[l++]);
		if (q[i].opt == 1)
			ans[q[i].id] = (s1 & (s1 << q[i].x)).any() || (s1 & (s1 >> q[i].x)).any();
		else if (q[i].opt == 2)
			ans[q[i].id] = (s1 & (s2 >> (N - q[i].x))).any(); // detail important. only exist "Zheng = Fan + x - N"
		else if (q[i].opt == 3) {
			for (int k = 1; k <= sqrt(q[i].x); ++k)
				if (q[i].x % k == 0 && s1[k] && s1[q[i].x / k]) {
					ans[q[i].id] = true;
					break;
				}
		}
		else if (q[i].x >= 500) {
			for (int k = 1; k * q[i].x <= mN; ++k)
				if (s1[k] && s1[k * q[i].x]) {
					ans[q[i].id] = true;
					break;
				}
		}
	}
	int X = 0;
	for (int i = 1; i <= cc; ++i) {
		if (q2[i].x == 0) {
			ans[q2[i].id] = false;
			continue;
		}
		if (q2[i].x == 1) {
			ans[q2[i].id] = true;
			continue;
		}
		if (q2[i].x != X) {
			X = q2[i].x;
			memset(pre, 0, sizeof pre);
			for (int i = 1; i <= n; ++i) {
				pre[a[i]] = i;
				lef[i] = lef[i - 1];
				if (a[i] * X <= mN)
					lef[i] = max(lef[i], pre[a[i] * X]);
				if (a[i] % X == 0)
					lef[i] = max(lef[i], pre[a[i] / X]);
			}
		}
		ans[q2[i].id] = lef[q2[i].r] >= q2[i].l;
	}
	for (int i = 1; i <= m; ++i) puts(ans[i] ? "yuno" : "yumi");
	return 0;
}