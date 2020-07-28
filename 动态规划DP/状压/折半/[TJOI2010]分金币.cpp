#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const ll inf = 0x7fffffffffffffff;
int n = 0, A = 0, B = 0;
int v[32];
int cnt[70000], c[16];
ll g[16][65540], sum[70000], sA = 0, sB = 0; // 一组和 - 二组和
void clear() {
	memset(c, 0, sizeof c);
	sA = sB = 0;
}
inline ll min(ll a, ll b) { return a < b ? a : b; }
inline ll ABS(ll x) { return x < 0 ? -x : x; }
ll getAAAAAAA(int t, ll s) {
	if (t == 0) return ABS(-sA + s);
	int L = 1, R = c[t], mid = 0;
	while (L <= R) {
		mid = (L + R) >> 1;
		if (g[t][mid] + s >= 0) R = mid - 1;
		else L = mid + 1;
	}
	++R;
	ll ret = inf;
	if (R <= c[t]) ret = min(ret, ABS(g[t][R] + s));
	if (R >= 2) ret = min(ret, ABS(g[t][R - 1] + s));
	return ret;
}
ll search(int t, ll s) { // find the min value of | g[t+-1?][k] + s |
	if (A == B) return getAAAAAAA(t, s);
	ll ret = inf;
	/*
	B = A + 1
	1.
	B - t + t = B
	t + A - t = A
	2. (1): (t - 1) + B - t = B - 1 = A
	   (2): (A - (t - 1)) + t = A + 1
	*/
	if (t <= A) ret = min(ret, getAAAAAAA(t, s));
	ret = min(ret, getAAAAAAA(t - 1, s));
	return ret;
}
int main() {
	int T = 0;
	scanf("%d", &T);
	for (int _T = 1; _T <= T; ++_T) {
		scanf("%d", &n);
		A = n / 2;
		B = n - A;
		for (int i = 1; i <= n; ++i)
			scanf("%d", v + i);
		for (int i = 1; i <= A; ++i) sA += v[i];
		for (int i = 1; i <= B; ++i) sB += v[A + i];
		for (int st = 1; st < (1 << A); ++st) {
			int u = A - 1; while (!((st >> u) & 1)) --u;
			int fr = st ^ (1 << u);
			cnt[st] = cnt[fr] + 1;
			sum[st] = sum[fr] + v[u + 1];
			g[cnt[st]][++c[cnt[st]]] = 2 * sum[st] - sA; // sum[st] - (sA - sum[st])
		}
		g[0][c[0] = 1] = -sA;
		for (int i = 1; i <= A; ++i)
			sort(g[i] + 1, g[i] + c[i] + 1);
		ll ans = inf;
		for (int st = 1; st < (1 << B); ++st) {
			int u = B - 1; while (!((st >> u) & 1)) --u;
			int fr = st ^ (1 << u);
			cnt[st] = cnt[fr] + 1;
			sum[st] = sum[fr] + v[A + u + 1];
			ans = min(ans, search(cnt[st], sB - 2 * sum[st])); // (sB - sum[st]) - sum[st]
		}
		ans = min(ans, ABS(sA - sB));
		printf("%lld\n", ans);
		clear();
	}
	return 0;
}