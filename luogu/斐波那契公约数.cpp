#include <cstdio>
typedef long long ll;
struct Sq{ ll a[2][2]; };
Sq operator* (const Sq &l,const Sq &r) {
	Sq ret;
	ret.a[0][0] = ret.a[0][1] = ret.a[1][0] = ret.a[1][1] = 0;
	for (int i = 0; i != 2;++i)
		for (int j = 0; j != 2;++j)
			for (int k = 0; k != 2;++k)
				(ret.a[i][j] += l.a[i][k] * r.a[k][j]) %= 100000000;
	return ret;
}
ll gcd(ll a,ll b) { return b == 0 ? a : gcd(b, a % b); }
Sq row(Sq x,int a) {
	Sq ret;
	ret.a[0][0] = ret.a[1][1] = 1; ret.a[1][0] = ret.a[0][1] = 0;
	while(a) {
		if(a&1)
			ret = ret * x;
		x = x * x;
		a >>= 1;
	}
	return ret;
}
Sq A;
int main() {
	ll n = 0, m = 0;
	scanf("%lld%lld", &n, &m);
	ll d = gcd(n, m);
	A.a[0][0] = A.a[0][1] = A.a[1][0] = 1;
	Sq ans = row(A, d-1);
	printf("%lld", ans.a[0][0]);
	return 0;
}