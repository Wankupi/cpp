#include <cstdio>
#include <cstring>
typedef long long ll;
ll const mod = 998244353;
inline ll pls(ll a, ll b) { return a + b < mod ? a + b : a + b - mod; }
inline int max(int a, int b) { return a < b ? b : a; }
int n = 0, m = 0;
char s[2003];
int ch[2003][26], fail[2003], maxOut[2003];
ll f[2003][2003];
ll pow(ll x, ll b) {
	ll r = 1;
	while (b) {
		if (b & 1) r = r * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return r;
}
int main() {
	scanf("%d", &m);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	fail[0] = fail[1] = 0;
	for (int i = 2; i <= n; ++i) {
		fail[i] = fail[i - 1];
		while (fail[i] && s[fail[i] + 1] != s[i]) fail[i] = fail[fail[i]];
		if (s[fail[i] + 1] == s[i]) ++fail[i];
	}
	for (int i = 0; i <= n; ++i) {
		maxOut[i] = max(maxOut[fail[i]], s[i + 1] - 'a');
		for (int j = 0; j < 26; ++j) {
			if (s[i + 1] - 'a' == j) ch[i][j] = i + 1;
			else ch[i][j] = ch[fail[i]][j];
		}
	}
	f[0][0] = 1;
	for (int i = 0; i < m; ++i)
		for (int p = 0; p <= n; ++p)
			for (int j = maxOut[p]; j < 26; ++j)
				f[i + 1][ch[p][j]] = pls(f[i + 1][ch[p][j]], f[i][p]);
	ll ans = 0;
	for (int p = 0; p <= n; ++p) {
		int x = p;
		for (int step = 0; step < m; ++step) {
			ans = pls(ans, (25ll - maxOut[x]) * f[m - step - 1][p] % mod);
			x = ch[x][maxOut[x]];
			if (x == 0) break;
		}
		if (x == p && x != 0) ans = pls(ans, 1);
	}
	ll All = pow(26, m);
	ans = (All - ans + mod) % mod;
	printf("%lld", ans);
	return 0;
}