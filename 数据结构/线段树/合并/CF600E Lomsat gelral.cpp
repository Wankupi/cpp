#include <cstdio>
int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
const int maxn = 100003, maxP = maxn * 35;
int n = 0;
int a[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }

int root[maxn];
struct Res {
	Res(int t = 0, long long s = 0) { tic = t; sum = s; }
	int tic;
	long long sum;
};
Res dat[maxP];
int lc[maxP], rc[maxP], c = 0;
inline Res pushUp(int A, int B) {
	if (A == 0) return dat[B];
	if (B == 0) return dat[A];
	if (dat[A].tic > dat[B].tic) return dat[A];
	if (dat[B].tic > dat[A].tic) return dat[B];
	return Res(dat[A].tic, dat[A].sum + dat[B].sum);
}
void Add(int &p, int L, int R, int x) {
	if (p == 0) p = ++c;
	if (L == R) { dat[p].tic = 1; dat[p].sum = L; return; }
	int mid = (L + R) >> 1;
	if (x <= mid) Add(lc[p], L, mid, x);
	else Add(rc[p], mid + 1, R, x);
	dat[p] = pushUp(lc[p], rc[p]);
}
int Combine(int p1, int p2, int L, int R) {
	if (p1 == 0) return p2;
	if (p2 == 0) return p1;
	if (L == R)
		dat[p1].tic += dat[p2].tic;
	else {
		int mid = (L + R) >> 1;
		lc[p1] = Combine(lc[p1], lc[p2], L, mid);
		rc[p1] = Combine(rc[p1], rc[p2], mid + 1, R);
		dat[p1] = pushUp(lc[p1], rc[p1]);
	}
	return p1;
}
long long ans[maxn];
void dfs(int x, int f) {
	Add(root[x], 1, n, a[x]);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs(to[i], x);
			root[x] = Combine(root[x], root[to[i]], 1, n);
		}
	ans[x] = dat[root[x]].sum;
}
int main() {
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		x = read(); y = read();
		insert(x, y);
		insert(y, x);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i)
		printf("%lld ", ans[i]);
	return 0;
}