#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
int const maxn = 100003;
inline int read() {
	int c = getchar(), x = 0;
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) { x = 10 * x + c - '0'; c = getchar(); }
	return x;
}
int n = 0, k = 0;
ll a[maxn], s[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int fa[maxn], son[maxn];
int q[maxn];
ll solve() {
	q[q[0] = 1] = 1;
	for (int k = 1; k <= n; ++k) {
		int x = q[k];
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != fa[x]) {
				q[++q[0]] = to[i];
				fa[to[i]] = x;
			}
	}
	for (int k = n; k >= 1; --k) {
		int x = q[k];
		s[x] += a[x];
		if (fa[x] && s[fa[x]] < s[x]) {
			s[fa[x]] = s[x];
			son[fa[x]] = x;
		}
	}
	int c = 0;
	for (int k = 1; k <= n; ++k) {
		int x = q[k];
		if (son[fa[x]] != x || x == 1) a[++c] = s[x];
	}
	ll ans = 0;
	if (k < c) nth_element(a + 1, a + k, a + c + 1, greater<ll>());
	for (int i = 1; i <= k && i <= c; ++i) ans += a[i];
	return ans;
}
void clear() {
	cnt = 0;
	memset(head, 0, sizeof(int) * (n + 1));
	memset(s, 0, sizeof(ll) * (n + 1));
}
int main() {
	int T = read();
	int x = 0, y = 0;
	for (int t = 1; t <= T; ++t) {
		n = read(); k = read();
		for (int i = 1; i <= n; ++i) a[i] = read();
		for (int i = 1; i < n; ++i) {
			x = read(); y = read();
			insert(x, y); insert(y, x);
		}
		ll ans = solve();
		printf("Case #%d: %lld\n", t, ans);
		clear();
	}
	return 0;
}