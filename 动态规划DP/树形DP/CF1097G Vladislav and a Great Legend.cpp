#include <cstdio>
typedef long long ll;
ll const mod = 1000000007;
inline ll pls(ll a, ll b) { return a + b < mod ? a + b : a + b - mod; }
inline ll dec(ll a, ll b) { return a >= b ? a - b : a - b + mod; }
inline int min(int a, int b) { return a < b ? a : b; }
inline int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int const maxn = 100003;
int n = 0, k = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }

ll S[203][203];
void init() {
	S[1][1] = 1;
	for (int i = 2; i <= k; ++i)
		for (int j = 1; j <= k; ++j)
			S[i][j] = pls(S[i - 1][j - 1], S[i - 1][j] * j % mod);
}
int siz[maxn];
ll dp[maxn][203], ans[203];
void dfs(int x, int f) {
	siz[x] = 1;
	dp[x][0] = 1;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs(to[i], x);
			for (int j = min(k, siz[x]); j >= 0; --j) {
				for (int p = min(siz[to[i]], k - j); p >= 0; --p) {
					ll val = dp[x][j] * dp[to[i]][p] % mod;
					dp[x][j + p] = pls(dp[x][j + p], val);
					ans[j + p] = pls(ans[j + p], val);
					dp[x][j + p + 1] = pls(dp[x][j + p + 1], val);
					ans[j + p + 1] = pls(ans[j + p + 1], val);
				}
			}
			for (int j = 1; j <= min(k, siz[to[i]]); ++j)
				dp[x][j] = pls(dp[x][j], pls(dp[to[i]][j], dp[to[i]][j - 1]));
			dp[x][0] = pls(dp[x][0], dp[to[i]][0]);
			siz[x] += siz[to[i]];
		}
}
int main() {
	//scanf("%d %d", &n, &k);
	n = read(); k = read();
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		//scanf("%d %d", &x, &y);
		x = read(); y = read();
		insert(x, y); insert(y, x);
	}
	init();
	dfs(1, 0);
	ll fact = 1, Ans = 0;
	for (int i = 1; i <= k; ++i) {
		fact = fact * i % mod;
		Ans = pls(Ans, ans[i] * fact % mod * S[k][i] % mod);
	}
	printf("%lld\n", Ans);
	return 0;
}
