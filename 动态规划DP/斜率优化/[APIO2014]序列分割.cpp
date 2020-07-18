#include <cstdio>
typedef long long ll;
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || '9' < c)
		c = getchar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x;
}
const int maxn = 100003;
int n = 0, k = 0;
ll a[maxn], s[maxn];
ll f[2][maxn];
int from[201][maxn];
ll X[maxn], Y[maxn];
int pos[maxn], l = 1, r = 0;
inline void push(ll x, ll y, int id) {
	while (l < r && (y - Y[r - 1]) * (X[r] - X[r - 1]) <= (Y[r] - Y[r - 1]) * (x - X[r - 1]))
		--r;
	++r;
	X[r] = x;
	Y[r] = y;
	pos[r] = id;
}
inline int front(ll k) {
	while (l < r && (Y[l + 1] - Y[l]) <= k * (X[l + 1] - X[l]))
		++l;
	return pos[l];
}
int ans[203];
int main() {
	n = read();
	k = read();
	++k;
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	for (int i = 1; i <= n; ++i)
		s[i] = s[i - 1] + a[i];
	for (int j = 2; j <= k; ++j) {
		int st = j & 1;
		l = 1;
		r = 0;
		for (int i = 1; i <= j - 1; ++i)
			f[st][i] = 0;
		push(s[j - 1], -f[st ^ 1][j - 1] + s[j - 1] * s[j - 1], j - 1);
		for (int i = j; i <= n; ++i) {
			int p = front(s[i]);
			f[st][i] = f[st ^ 1][p] + s[p] * (s[i] - s[p]);
			from[j][i] = p;
			push(s[i], -f[st ^ 1][i] + s[i] * s[i], i);
		}
	}
	printf("%lld\n", f[k & 1][n]);
	for (int i = k, x = n; i >= 1; --i) {
		ans[i] = x;
		x = from[i][x];
	}
	for (int i = 1; i < k; ++i)
		printf("%d ", ans[i]);
	return 0;
}