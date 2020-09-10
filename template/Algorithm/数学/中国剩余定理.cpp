#include <cstdio>
typedef long long ll;
int n = 0;
ll m[11], M[11], a[11];
struct Result { ll d, x, y; };
Result exgcd(ll a, ll b) {
	if (b == 0) return Result{a, 1, 0};
	Result r = exgcd(b, a % b);
	return Result{r.d, r.y, r.x - a / b * r.y};
}
int main() {
	scanf("%d", &n);
	M[0] = 1;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld%lld", m + i, a + i);
		M[0] *= m[i];
	}
	ll sum = 0;
	for (int i = 1; i <= n; ++i) {
		M[i] = M[0] / m[i];
		ll inv = (exgcd(M[i], m[i]).x + m[i]) % m[i];
		sum = (sum + a[i] * M[i] % M[0] * inv % M[0]) % M[0];
	}
	printf("%lld", sum);
	return 0;
}