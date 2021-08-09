#include <cstdio>
typedef long long ll;

int const V = 100000;
int a[4], d[4];
ll f[100003];

int main() {
	f[0] = 1;
	for (int i = 0; i < 4; ++i) {
		scanf("%d", a + i);
		for (int j = a[i]; j <= V; ++j)
			f[j] += f[j - a[i]];
	}
	int n = 0;
	scanf("%d", &n);
	for (int t = 1; t <= n; ++t) {
		for (int i = 0; i < 4; ++i)
			scanf("%d", d + i);
		int s = 0; ll res = 0;
		scanf("%d", &s);
		for (int S = 0; S < 16; ++S) {
			int cnt = 0, r = s;
			for (int i = 0; i < 4 && r >= 0; ++i)
				if ((S >> i) & 1) {
					r -= a[i] * (d[i] + 1);
					cnt ^= 1;
				}
			if (r < 0) continue;
			if (cnt & 1) res -= f[r];
			else res += f[r];
		}
		printf("%lld\n", res);
	}
	return 0;
}