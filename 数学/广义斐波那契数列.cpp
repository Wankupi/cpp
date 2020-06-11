#include <iostream>
typedef long long ll;
ll m = 0;
struct Sq{ ll a[2][2]; };
Sq operator* (const Sq &l,const Sq &r) {
	Sq ret;
	ret.a[0][0] = ret.a[0][1] = ret.a[1][0] = ret.a[1][1] = 0;
	for (int i = 0; i != 2;++i)
		for (int j = 0; j != 2;++j)
			for (int k = 0; k != 2;++k)
				(ret.a[i][j] += (l.a[i][k] * r.a[k][j]) % m) %= m;
	return ret;
}
Sq A, B;
Sq row(Sq x,int a) {
	Sq ret = B;
	while(a) {
		if(a&1) ret = ret * x;
		x = x * x;
		a >>= 1;
	}
	return ret;
}
int main() {
	int p = 0, q = 0, a1 = 0, a2 = 0;
	ll n = 0;
	std::cin >> p >> q >> a1 >> a2 >> n >> m;
	A.a[0][0] = p; A.a[1][0] = q; A.a[0][1] = 1; A.a[1][1] = 0;
	B.a[0][0] = a2; B.a[0][1] = a1;
	B.a[1][0] = B.a[1][1] = 0;
	std::cout << row(A, n - 2).a[0][0];
	return 0;
}