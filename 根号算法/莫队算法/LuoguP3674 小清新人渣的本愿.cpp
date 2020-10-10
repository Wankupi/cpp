#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
using namespace std;
int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int n = 0, m = 0, block = 0, N = 100000;
int a[100003];
struct Query {
	int opt, l, r, x, id;
};
inline bool operator<(const Query &lhs, const Query &rhs) { return (lhs.l / block) == (rhs.l / block) ? lhs.r < rhs.r : lhs.l < rhs.l; }
Query q[100003];
int cnt[100003];
bitset<100005> s1, s2, ans;
inline void add(int x) { if (cnt[x]++ == 0) s1[x] = s2[N - x] = true; }
inline void del(int x) { if (--cnt[x] == 0) s1[x] = s2[N - x] = false; }
int main() {
	n = read(); m = read();
	block = int(sqrt(n)) + 1;
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
	}
	for (int i = 1; i <= m; ++i) {
		q[i].opt = read(); q[i].l = read();
		q[i].r = read(); q[i].x = read();
		q[i].id = i;
	}
	sort(q + 1, q + m + 1);
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
		else
			for (int k = 1; k <= sqrt(q[i].x); ++k)
				if (q[i].x % k == 0 && s1[k] && s1[q[i].x / k]) {
					ans[q[i].id] = true;
					break;
				}
	}
	for (int i = 1; i <= m; ++i) puts(ans[i] ? "hana" : "bi");
	return 0;
}