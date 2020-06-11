#include <iostream>
#include <cstdio>
typedef long long ll;
char n1[1000001], n2[1000001];
ll phi(ll x) {
	ll n = 1;
	for (ll i = 2; i * i <= x; ++i)
		if (x % i == 0) {
			x /= i; n *= i - 1;
			while (x % i == 0) n *= i, x /= i;
		}
	if (x != 1) n *= x - 1;
	return n;
}
bool read(char *s, ll c, ll &x) {
	x = 0; bool sign = false;
	while (*s >= '0' && *s <= '9') {
		x = x * 10 + *s - '0';
		if (x > c) { x %= c; sign = true; }
		++s;
	}
	return sign;
}
ll row(ll x, ll a, ll mod) {
	ll ret = 1;
	while (a) {
		if (a & 1) ret = (ret * x) % mod;
		x = (x * x) % mod;
		a >>= 1;
	}
	return ret;
}
int main() {
	ll c = 0;
	std::cin >> n1 >> n2 >> c;
	ll pc = phi(c), b = 0, n = 0;
	read(n1, c, b);
	bool sign = read(n2, pc, n);
	n = (n - 1 + pc) % pc + (sign ? pc : 0);
	ll ans = row(b, n, c);
	ans = ((b - 1) * ans) % c;
	std::cout << (ans ? ans : c);
	return 0;
}