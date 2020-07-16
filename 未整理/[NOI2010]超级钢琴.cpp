#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
int read() {
	int x = 0, f = 1, c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while ('0' <= c && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
inline int min(int a, int b) { return a < b ? a : b; }

int n = 0, k = 0, L = 0, R = 0;
ll s[500001];
int lg2[500001], mx[20][500001];
inline int query(int l, int r) {
	int k = lg2[r - l + 1];
	return s[mx[k][l]] >= s[mx[k][r - (1 << k) + 1]] ? mx[k][l] : mx[k][r - (1 << k) + 1];
}
struct DATA {
	DATA(int _le, int _l, int _r) { left = _le; l = _l; r = _r; p = query(l, r); }
	int left;
	int l, r;
	int p;
};
inline bool operator<(const DATA &lhs, const DATA &rhs) { return s[lhs.p] - s[lhs.left - 1] < s[rhs.p] - s[rhs.left - 1]; }
priority_queue<DATA> q;
int main() {
	n = read(); k = read(); L = read(); R = read();
	lg2[0] = -1;
	for (int i = 1; i <= n; ++i) {
		s[i] = s[i - 1] + read();
		mx[0][i] = i;
		lg2[i] = lg2[i / 2] + 1;
	}
	for (int j = 1; j <= 19; ++j)
		for (int i = 0; i <= n - (1 << j) + 1; ++i)
			mx[j][i] = (s[mx[j - 1][i]] >= s[mx[j - 1][i + (1 << (j - 1))]] ? mx[j - 1][i] : mx[j - 1][i + (1 << (j - 1))]);
	for (int i = 1; i <= n - L + 1; ++i) q.push(DATA(i, i + L - 1, min(i + R - 1, n)));
	ll ans = 0;
	for (int t = 1; t <= k; ++t) {
		DATA x = q.top(); q.pop();
		ans += s[x.p] - s[x.left - 1];
		if (x.p > x.l) q.push(DATA(x.left, x.l, x.p - 1));
		if (x.p < x.r) q.push(DATA(x.left, x.p + 1, x.r));
	}
	printf("%lld", ans);
	return 0;
}