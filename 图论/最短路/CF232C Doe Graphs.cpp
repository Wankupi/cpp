#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int n = 0, T = 0;
ll D[1003], g[1003]; // D: the size of D(n), g: the distance from 1 to |D(n)|
ll x1[1003], xn[1003], Y1[1003], Yn[1003];
void getDisPre(ll x, int N, ll (&t1)[1003], ll (&tn)[1003]) {
	if (N == 0) { t1[0] = tn[0] = 0; return; }
	if (N == 1) { t1[1] = (x == 2); tn[1] = (x == 1); return; }
	if (x <= D[N - 1]) {
		getDisPre(x, N - 1, t1, tn);
		t1[N] = min(t1[N - 1], tn[N - 1] + 2);
		tn[N] = min(t1[N - 1], tn[N - 1]) + g[N - 2] + 1;
	}
	else {
		getDisPre(x - D[N - 1], N - 2, t1, tn);
		t1[N] = t1[N - 2] + 1;
		tn[N] = tn[N - 2];
	}
}
ll dis(ll x, ll y, ll N) {
	if (N <= 1) return x != y;
	if (x <= D[N - 1] && y <= D[N - 1])
		return min(min(min(x1[N - 1] + Y1[N - 1], xn[N - 1] + Yn[N - 1]), min(x1[N - 1] + Yn[N - 1] + 2, xn[N - 1] + Y1[N - 1] + 2)), dis(x, y, N - 1));
	else if (x <= D[N - 1])
		return min(x1[N - 1], xn[N - 1]) + 1 + Y1[N - 2];
	else return dis(x - D[N - 1], y - D[N - 1], N - 2);
}
int main() {
	scanf("%d %d", &T, &n);
	if (n > 80) n = 80;
	D[0] = 1;
	D[1] = 2;
	for (int i = 2; i <= n; ++i)
		D[i] = D[i - 1] + D[i - 2];
	g[0] = 0;
	g[1] = 1;
	g[2] = 1;
	for (int i = 3; i <= n; ++i)
		g[i] = g[i - 2] + 1;
	for (int t = 1; t <= T; ++t) {
		ll x = 0, y = 0;
		scanf("%lld %lld", &x, &y);
		if (x > y) swap(x, y);
		getDisPre(x, n, x1, xn);
		getDisPre(y, n, Y1, Yn);
		printf("%lld\n", dis(x, y, n));
	}
	return 0;
}