#include <cstdio>
#include <cstring>
typedef long long ll;
inline ll min(ll a, ll b) { return a < b ? a : b; }
inline ll max(ll a, ll b) { return a < b ? b : a; }
inline int max(int a, int b) { return a < b ? b : a; }
int n = 0, d = 0, k = 0;
int x[500001], s[500001];
ll f[500001];
int dl[500001], l = 1, r = 0;
inline void push(int p) {
	while (l <= r && f[p] >= f[dl[r]])
		--r;
	dl[++r] = p;
}
bool check(int g) {
	ll ans = 0;
	memset(f, -0x3f, sizeof f);
	f[0] = 0;
	l = 1; r = 0;
	int mx = d + g, mi = max(d - g, 1);
	int j = 0;
	for (int i = 1; i <= n; ++i) {
		while (x[i] - x[j] >= mi) push(j++);
		while (l <= r && x[i] - x[dl[l]] > mx) ++l;
		if (l <= r) f[i] = s[i] + f[dl[l]];
		ans = max(ans, f[i]);
	}
	return ans >= k;
}
int main() {
	scanf("%d%d%d", &n, &d, &k);
	ll sum = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", x + i, s + i);
		if (s[i] > 0) sum += s[i];
	}
	if (sum < k) {
		printf("-1\n");
		return 0;
	}
	int L = 0, R = x[n], mid = 0;
	while (L <= R) {
		mid = (L + R) >> 1;
		if (check(mid)) R = mid - 1;
		else L = mid + 1;
	}
	printf("%d", R + 1);
	return 0;
}