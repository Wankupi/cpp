#include <cmath>
#include <cstdio>
typedef long long ll;
int n = 0, k = 0, a[19];
ll f[19][66000];
inline int lowbit(int x) { return x & -x; }
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int st = 1; st < (1 << n); ++st) {
		for (int i = 1; i <= n; ++i) {
			if (!(st & (1 << (i - 1)))) continue;
			int S = st ^ (1 << (i - 1));
			if (S == 0) f[i][st] = 1;
			for (int j = 1; j <= n; ++j)
				if ((S & (1 << (j - 1))) && abs(a[i] - a[j]) > k)
					f[i][st] += f[j][S];
		}
	}
	ll sum = 0;
	for (int i = 1; i <= n; ++i)
		sum += f[i][(1 << n) - 1];
	printf("%lld", sum);
	return 0;
}