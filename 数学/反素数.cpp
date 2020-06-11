#include <cstdio>
typedef long long ll;
ll n = 0;
ll prime[15] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
int c[15];
ll ans = 1, cnt = 1;
void dfs(int t, ll now, ll m) {
	if (now > n) return;
	if (m > cnt || (m == cnt && now < ans)) {
		ans = now;
		cnt = m;
	}
	ll muti = 1;
	for (int i = 1; i <= c[t - 1] && muti * now <= n; ++i) {
		muti *= prime[t];
		c[t] = i;
		dfs(t + 1, now * muti, m * (i + 1));
	}
}
int main() {
	scanf("%lld", &n);
	c[0] = 30;
	dfs(1, 1, 1);
	printf("%lld", ans);
	return 0;
}