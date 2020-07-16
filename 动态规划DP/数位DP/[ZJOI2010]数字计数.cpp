#include <cstdio>
typedef long long ll;
ll f[15], g[15];
ll cnt1[10], cnt2[10];
void query(ll x, ll *cnt) {
	ll temp = x;
	int n[15]{ 0 }, c = 0;
	while (temp) {
		n[++c] = temp % 10;
		temp /= 10;
	}
	for (int i = c; i >= 1; --i) {
		for (int j = 0; j <= 9; ++j)
			cnt[j] += n[i] * f[i - 1]; //后面位的贡献
		for (int j = 0; j < n[i]; ++j) 
			cnt[j] += g[i - 1]; //该位数字的贡献
		cnt[0] -= g[i - 1]; //这里强制要减去 这位为 0 的情况 不能与上一个for合并
		// 表示意义不同
		cnt[n[i]] += (x % g[i - 1]) + 1; // 当这一位取最大值时，这一位数字贡献
	}
}

int main() {
	ll a = 0, b = 0;
	scanf("%lld%lld", &a, &b);
	g[0] = 1;
	for (int i = 1; i <= 12; ++i) {
		f[i] = 10 * f[i - 1] + g[i - 1];
		g[i] = g[i - 1] * 10;
	}
	query(b, cnt1);
	query(a - 1, cnt2);
	for (int i = 0; i <= 9; ++i)
		printf("%lld ", cnt1[i] - cnt2[i]);
	return 0;
}