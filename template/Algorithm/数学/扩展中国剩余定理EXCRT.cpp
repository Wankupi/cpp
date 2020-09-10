#include <cstdio>
typedef long long ll;
inline ll muti(ll a, ll b, ll mod) {
	ll r = 0;
	while (b) {
		if (b & 1) r = (r + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return r;
}
struct Result {
	Result(ll D, ll X, ll Y) { d = D, x = X, y = Y; }
	ll d, x, y;
};
Result gcd(ll a, ll b) {
	if (b == 0) return Result(a, 1, 0);
	Result r = gcd(b, a % b);
	return Result(r.d, r.y, r.x - (a / b) * r.y);
}
ll b1 = 0, a1 = 0;
void combine(ll b2, ll a2) {
	Result r = gcd(a1, a2);
	r.x = (r.x % (a2 / r.d) + a2 / r.d) % (a2 / r.d);
	ll m = a1 / r.d * a2;
	//ll x = ((r.x * (b2 - b1) / r.d) * a1 + b1) % m;
	ll x = (muti(muti((b2 - b1) / r.d, r.x, m), a1, m) + b1) % m; //注意muti函数中调用的顺序，避免第二个为负数
	a1 = m;
	b1 = (x % a1 + a1) % a1;
}
int main() {
	int n = 0;
	scanf("%d", &n);
	ll a = 0, b = 0;
	scanf("%lld%lld", &a1, &b1);
	for (int i = 2; i <= n; ++i) {
		scanf("%lld%lld", &a, &b);
		combine(b, a);
	}
	printf("%lld", b1);
	return 0;
}