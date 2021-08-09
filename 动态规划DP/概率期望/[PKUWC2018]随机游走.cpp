#include <cstdio>

typedef long long ll;
int const mod = 998244353;
inline int pls(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
inline int dec(int a, int b) { return a < b ? a - b + mod : a - b; }
inline int pow(int x, int b) {
	int r = 1;
	while (b) {
		if (b & 1) r = ll(r) * x % mod;
		x = ll(x) * x % mod;
		b >>= 1;
	}
	return r;
}
inline int inv(int x) { return pow(x, mod - 2); }

int n = 0, Q = 0, X = 0;
int S = 0;

int d[18];
int head[18], nxt[39], to[39], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}

struct Res {
	int a, b;
};
Res operator+(Res const &A, Res const &B) { return Res{pls(A.a, B.a), pls(A.b, B.b)}; }

Res dfs(int x, int fa) {
	if ((S >> x) & 1) return Res{0, 0};
	if (!head[x]) return Res{1, 1};
	Res r{0, 0};
	for (int i = head[x]; i; i = nxt[i]) {
		if (to[i] == fa) continue;
		r = r + dfs(to[i], x);
	}
	r = Res{inv(dec(d[x], r.a)), pls(d[x], r.b)};
	r.b = ll(r.b) * r.a % mod;
	return r;
}

int f[1 << 18];

int main() {
	freopen("t.out", "w", stdout);
	scanf("%d %d %d", &n, &Q, &X);
	--X;
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		--x; --y;
		++d[x]; ++d[y];
		insert(x, y);
		insert(y, x);
	}
	for (S = 1; S < (1 << n); ++S) {
		f[S] = dfs(X, X).b;
		int c = 0;
		for (int i = 0; i < n; ++i) if ((S >> i) & 1) c ^= 1;
		if ((c & 1) == 0 && f[S] > 0) f[S] = mod - f[S];
	}
	for (int len = 1; len < (1 << n); len <<= 1)
		for (int l = 0; l < (1 << n); l += len << 1)
			for (int i = 0; i < len; ++i)
				f[l + len + i] = pls(f[l + len + i], f[l + i]);
	for (int i = 1; i <= Q; ++i) {
		scanf("%d", &y);
		S = 0;
		for (int j = 1; j <= y; ++j) {
			scanf("%d", &x);
			S |= (1 << (x - 1));
		}
		printf("%d\n", f[S]);
	}
	return 0;
}