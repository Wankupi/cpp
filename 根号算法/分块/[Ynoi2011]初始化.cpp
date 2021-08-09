#include <cstdio>

int const mod = 1000000007;
int const maxn = 200003, Block = 450, nB = maxn / Block + 3;

inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while ('0' <= c && c <= '9') { x = 10 * x + c - '0'; c = getchar(); }
	return x;
}
inline int pls(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
inline int dec(int a, int b) { return a < b ? a - b + mod : a - b; }

int n = 0, m = 0, cB = 0;
int a[maxn];

int L[nB], R[nB], id[maxn];
int sum[nB];
int sl[Block + 3][Block + 3], sr[Block + 3][Block + 3];

void init() {
	cB = (n + Block - 1) / Block;
	for (int i = 1; i <= cB; ++i) {
		L[i] = (i - 1) * Block + 1;
		R[i] = i * Block;
		if (R[i] > n) R[i] = n;
		for (int j = L[i]; j <= R[i]; ++j) {
			id[j] = i;
			sum[i] = pls(sum[i], a[j]);
		}
	}
}

void modify(int x, int y, int z) {
	if (x <= Block) {
		for (int i = y; i <= x; ++i) sl[x][i] = pls(sl[x][i], z);
		for (int i = y; i >= 1; --i) sr[x][i] = pls(sr[x][i], z);
	}
	else {
		for (int i = y; i <= n; i += x) {
			a[i] = pls(a[i], z);
			sum[id[i]] = pls(sum[id[i]], z);
		}
	}
}

int query(int l, int r) {
	int res = 0;
	if (id[l] == id[r]) {
		for (int i = l; i <= r; ++i) res = pls(res, a[i]);
	}
	else {
		for (int i = l; i <= R[id[l]]; ++i) res = pls(res, a[i]);
		for (int i = L[id[r]]; i <= r; ++i) res = pls(res, a[i]);
		for (int i = id[l] + 1; i < id[r]; ++i) res = pls(res, sum[i]);
	}
	for (int x = 1; x <= Block; ++x) {
		int il = (l - 1) / x + 1, ir = (r - 1) / x + 1;
		int _l = (l - 1) % x + 1, _r = (r - 1) % x + 1;
		if (il == ir)
			res = pls(res, dec(sl[x][_r], sl[x][_l - 1]));
		else {
			long long C = ir - il - 1;
			res = pls(res, sr[x][_l]);
			res = pls(res, sl[x][_r]);
			res = pls(res, sl[x][x] * C % mod);
		}
	}
	return res;
}

int main() {
	//freopen("t.in", "r", stdin);
	n = read(); m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	init();
	int opt = 0, x = 0, y = 0, z = 0;
	for (int t = 1; t <= m; ++t) {
		scanf("%d %d %d", &opt, &x, &y);
		if (opt == 1) {
			scanf("%d", &z);
			modify(x, y, z);
		}
		else printf("%d\n", query(x, y));
	}
	return 0;
}
