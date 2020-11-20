#include <cstdio>
typedef long long ll;
void read(ll &x) {
	x = 0; int c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	x *= f;
}
ll n = 0;
ll x[1000001], s[1000001];
ll a = 0, b = 0, c = 0;
ll f[1000001];
inline ll Y(ll X) { return -f[X] - a * s[X] * s[X] + b * s[X]; }
ll q[1000001], l = 1, r = 1;
ll front(ll k) {
	while (l < r && Y(q[l + 1]) - Y(q[l]) <=
		k * (s[q[l + 1]] - s[q[l]]))
		++l;
	return q[l];
}
void push(ll X) {
	while (l < r && (Y(X) - Y(q[r - 1])) * (s[q[r]] - s[q[r - 1]]) <=
		(Y(q[r]) - Y(q[r - 1])) * (s[X] - s[q[r - 1]]))
		--r;
	q[++r] = X;
}
int main() {
	read(n); read(a); read(b); read(c);
	for (ll i = 1; i <= n; ++i) {
		read(x[i]); s[i] = s[i - 1] + x[i];
	}
	for (ll i = 1; i <= n; ++i) {
		ll j = front(-2 * a * s[i]);
		f[i] = f[j] + a * s[i] * s[i] + a * s[j] * s[j] - 2 * a * s[i] * s[j]
			+ b * s[i] - b * s[j] + c;
		push(i);
	}
	printf("%lld", f[n]);
	return 0;
}