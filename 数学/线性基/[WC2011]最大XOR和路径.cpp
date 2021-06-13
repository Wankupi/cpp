#include <cstdio>
typedef long long ll;
int const maxn = 50003, maxm = 200003;

int n = 0, m = 0;
int head[maxn], nxt[maxm], to[maxm], cnt = 1;
ll val[maxm];
inline void insert(int u, int e, ll v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }

ll base[64];
inline void add(ll x) {
	for (int j = 63; ~j && x; --j)
		if ((x >> j) & 1) {
			if (base[j]) x ^= base[j];
			else { base[j] = x; x = 0; }
		}
}
inline ll query_max(ll x) {
	for (int j = 63; ~j; --j)
		if (((x >> j) & 1) == 0 && base[j])
			x ^= base[j];
	return x;
}

bool vis[maxn];
ll s[maxn];
void dfs(int x, int fr) {
	vis[x] = true;
	for (int i = head[x]; i; i = nxt[i]) {
		if (i == fr) continue;
		if (vis[to[i]])
			add(s[x] ^ s[to[i]] ^ val[i]);
		else {
			s[to[i]] = s[x] ^ val[i];
			dfs(to[i], i ^ 1);
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	int x = 0, y = 0; ll z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %lld", &x, &y, &z);
		insert(x, y, z);
		insert(y, x, z);
	}
	dfs(1, 0);
	ll ans = query_max(s[n]);
	printf("%lld", ans);
	return 0;
}