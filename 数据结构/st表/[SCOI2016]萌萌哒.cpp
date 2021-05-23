#include <cstdio>
typedef long long ll;
inline void swap(int &a, int &b) { int c = b; b = a; a = c; }
int const maxn = 100003;
ll const mod = 1000000007;
int n = 0, m = 0;
int id[17][maxn], who[maxn * 17], cntId = 0;
int lg2[maxn];
int fa[maxn * 17], siz[maxn * 17];

inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) {
	x = find(x); y = find(y);
	if (x == y) return;
	if (siz[x] < siz[y]) swap(x, y);
	fa[y] = x;
	siz[x] += siz[y];
}

inline ll pow(ll x, int a) {
	ll r = 1;
	while (a) {
		if (a & 1) r = r * x % mod;
		x = x * x % mod;
		a >>= 1;
	}
	return r;
}

int main() {
	scanf("%d %d", &n, &m);
	lg2[1] = 0;
	for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
	for (int j = 0; j <= 16; ++j) {
		int len = (1 << j);
		for (int i = 1; i <= n - len + 1; ++i) {
			id[j][i] = ++cntId;
			who[cntId] = i;
		}
	}
	for (int i = 1; i <= cntId; ++i) { fa[i] = i; siz[i] = 1; }
	
	for (int i = 1; i <= m; ++i) {
		int l1 = 0, r1 = 0, l2 = 0, r2 = 0;
		scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
		int j = lg2[r1 - l1 + 1], len = 1 << j;
		merge(id[j][l1], id[j][l2]);
		merge(id[j][r1 - len + 1], id[j][r2 - len + 1]);
	}
	for (int j = 16; j >= 1; --j) {
		int len = (1 << j);
		for (int i = 1; i <= n - len + 1; ++i) {
			int f = who[find(id[j][i])];
			merge(id[j - 1][i], id[j - 1][f]);
			merge(id[j - 1][i + (1 << (j - 1))], id[j - 1][f + (1 << (j - 1))]);
		}
	}
	int cir = 0;
	for (int i = 1; i <= n; ++i) if (fa[id[0][i]] == id[0][i]) ++cir;
	ll ans = pow(10, cir - 1) * 9 % mod;
	printf("%ld", ans);
	return 0;
}
