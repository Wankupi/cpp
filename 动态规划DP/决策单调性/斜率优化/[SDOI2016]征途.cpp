#include <cstdio>
typedef long long ll;
const int maxn = 3003;
int n = 0, m = 0;
int s[maxn];
ll f[2][maxn];
ll x[maxn], y[maxn], pos[maxn], l = 0, r = 0;
void push(ll X, ll Y, int p) {
	while (l < r && (y[r] - y[r - 1]) * (X - x[r - 1]) >= (Y - y[r - 1]) * (x[r] - x[r - 1]))
		--r;
	++r;
	x[r] = X;
	y[r] = Y;
	pos[r] = p;
}
int front(ll K) {
	while (l < r && (y[l + 1] - y[l]) <= K * (x[l + 1] - x[l]))
		++l;
	return pos[l];
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", s + i);
		s[i] += s[i - 1];
	}
	for (int i = 1; i <= n; ++i)
		f[1][i] = s[i] * s[i];
	for (int j = 2; j <= m; ++j) {
		l = r = 1;
		x[1] = y[1] = 0;
		for (int i = 1; i <= n; ++i) {
			int k = front(2 * s[i]);
			f[j & 1][i] = f[(j & 1) ^ 1][k] + (s[i] - s[k]) * (s[i] - s[k]);
			push(s[i], f[(j & 1) ^ 1][i] + s[i] * s[i], i);
		}
	}
	ll ans = f[m & 1][n] * m - s[n] * s[n];
	printf("%lld", ans);
	return 0;
}