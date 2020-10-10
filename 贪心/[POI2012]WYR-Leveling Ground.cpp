#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
struct Result {
	Result(ll D, ll X, ll Y) : d(D), x(X), y(Y) {}
	ll d, x, y;
};
Result exgcd(ll a, ll b) {
	if (b == 0) return Result(a, 1, 0);
	Result r = exgcd(b, a % b);
	return Result(r.d, r.y, r.x - r.y * (a / b));
}
int n = 0, A = 0, B = 0, d = 0;
ll a[100003], X[1000003], Y[1000003];
int main() {
	scanf("%d %d %d", &n, &A, &B);
	Result S = exgcd(A, B);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", a + i);
		if (a[i] % S.d != 0) { puts("-1"); return 0; }
	}
	++n;
	for (int i = n; i >= 1; --i) a[i] = a[i] - a[i - 1];
	ll dA = A / S.d, dB = B / S.d;
	for (int i = 1; i <= n; ++i) {
		ll x = X[i] = (S.x * (a[i] / S.d) % dB + dB) % dB; // now x is min positive
		ll y = Y[i] = (a[i] - x * A) / B;
		x -= dB; y += dA;
		if (abs(x) + abs(y) < abs(X[i]) + abs(Y[i])) X[i] = x, Y[i] = y;

		y = (S.y * (a[i] / S.d) % dA + dA) % dA;
		x = (a[i] - y * B) / A;
		if (abs(x) + abs(y) < abs(X[i]) + abs(Y[i])) X[i] = x, Y[i] = y;
		y -= dA; x += dB;
		if (abs(x) + abs(y) < abs(X[i]) + abs(Y[i])) X[i] = x, Y[i] = y;
	}

	ll sumX = 0;
	for (int i = 1; i <= n; ++i) sumX += X[i];
	sumX /= dB;
	if (sumX < 0) {
		swap(A, B); swap(dA, dB);
		swap(X, Y);
		sumX = -sumX;
	}
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>> > q;
	for (int i = 1;i <= n; ++i)
		q.push(make_pair(abs(X[i] - dB) + abs(Y[i] + dA) - abs(X[i]) - abs(Y[i]), i));
	while (sumX--) {
		int i = q.top().second;
		q.pop();
		X[i] -= dB; Y[i] += dA;
		q.push(make_pair(abs(X[i] - dB) + abs(Y[i] + dA) - abs(X[i]) - abs(Y[i]), i));
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i) ans += abs(X[i]) + abs(Y[i]);
	ans /= 2;
	printf("%lld", ans);
	return 0;
}