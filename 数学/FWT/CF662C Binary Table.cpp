#include <algorithm>
#include <cstdio>
typedef long long ll;
int n = 0, m = 0, N = 0;
char c[100003];
int st[100003];
ll cnt[1 << 20], F[1 << 20], R[1 << 20];
inline int count1(int x) {
	int ret = 0;
	while (x) {
		if (x & 1) ++ret;
		x >>= 1;
	}
	return ret;
}
void XOR(ll *f, int opt) {
	for (int len = 1; len < N; len <<= 1)
		for (int i = 0; i < N; i += (len << 1))
			for (int j = 0; j < len; ++j) {
				ll L = f[i + j], R = f[i + len + j];
				f[i + j] = (L + R) / opt;
				f[i + j + len] = (L - R) / opt;
			}
}
int main() {
	scanf("%d %d", &n, &m);
	N = 1 << n;
	for (int i = 0; i < n; ++i) {
		scanf("%s", c);
		for (int j = 0; j < m; ++j)
			if (c[j] == '1')
				st[j] |= (1 << i);
	}
	for (int i = 0; i < N; ++i) {
		int k = count1(i);
		F[i] = std::min(k, n - k);
	}
	for (int i = 0; i < m; ++i)
		++cnt[st[i]];
	XOR(cnt, 1);
	XOR(F, 1);
	for (int i = 0; i < N; ++i)
		R[i] = cnt[i] * F[i];
	XOR(R, 2);
	ll ans = (ll)n * m + 1ll;
	for (int i = 0; i < N; ++i)
		if (R[i] < ans) ans = R[i];
	printf("%lld", ans);
	return 0;
}