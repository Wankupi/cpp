#include <algorithm>
#include <cstdio>
using namespace std;
using ll = long long;
int n = 0, E = 0, T = 0;
int x[100003];

ll f[100003];
int q[100003], ql = 1, qr = 0;
ll val[100003];
int main() {
	scanf("%d %d %d", &n, &E, &T);
	for (int i = 1; i <= n; ++i)
		scanf("%d", x + i);
	int l = 1;
	ll mxF = 0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= n; ++i) {
		while (2 * (x[i] - x[l]) >= T) {
			mxF = min(mxF, f[l - 1] - 2 * x[l] - x[l - 1]);
			++l;
		}
		while (ql <= qr && val[qr] > f[i - 1] - x[i - 1])
			--qr;
		q[++qr] = i;
		val[qr] = f[i - 1] - x[i - 1];

		while (ql <= qr && (x[i] - x[q[ql]]) * 2 >= T)
			++ql;
		f[i] = x[i] + val[ql] + T;
		if (l > 1) f[i] = min(f[i], 3ll * x[i] + mxF);
	}
	ll ans = f[n] + E - x[n];
	printf("%lld\n", ans);
	return 0;
}