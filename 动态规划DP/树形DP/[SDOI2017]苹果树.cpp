#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
int const maxn = 20003, maxk = 500003, NK = 25020003;
inline int read() {
	int x = 0, c = 0;
	while (c < '0' || '9' < c) c = getchar();
	while ('0' <= c && c <= '9') x = 10 * x + c - '0', c = getchar();
	return x;
}
int n = 0, k = 0;
int a[maxn], v[maxn], fa[maxn];
int head[maxn], nxt[maxn];
inline void add(int u, int e) { nxt[e] = head[u]; head[u] = e; }
int F[NK], G[NK];
inline int index(int i, int j) { return (i - 1) * (k + 1) + j; }
int ans = 0;
inline void bag(int *f, int A, int V) {
	if (A <= 0) return;
	static int q[maxk], p[maxk];
	int ql = 1, qr = 0;
	for (int i = 0; i <= k; ++i) {
		f[i] -= i * V;
		while (ql <= qr && f[q[qr]] <= f[i]) --qr;
		q[++qr] = i;
		while (ql <= qr && i - q[ql] > A) ++ql;
		p[i] = f[q[ql]] + i * V;
	}
	memcpy(f, p, (k + 1) * sizeof(int));
}
void dfsL(int x) {
	bag(F + index(x, 0), a[x] - 1, v[x]);
	for (int i = head[x]; i; i = nxt[i]) {
		memcpy(F + index(i, 0), F + index(x, 0), (k + 1) * sizeof(int));
		dfsL(i);
		for (int j = 1; j <= k; ++j)
			F[index(x, j)] = max(F[index(x, j)], F[index(i, j - 1)] + v[i]);
	}
}
void dfsR(int x, int sum) {
	sum += v[x];
	for (int i = head[x]; i; i = nxt[i]) {
		memcpy(G + index(i, 0), G + index(x, 0), (k + 1) * sizeof(int));
		dfsR(i, sum);
		for (int j = 1; j <= k; ++j)
			G[index(x, j)] = max(G[index(x, j)], G[index(i, j - 1)] + v[i]);
	}
	if (head[x] == 0) {
		for (int j = 0; j <= k; ++j)
			ans = max(ans, F[index(x, j)] + G[index(x, k - j)] + sum);
	}
	bag(G + index(x, 0), a[x] - 1, v[x]);
}
int main() {
	int T = read();
	while (T--) {
		n = read(); k = read();
		ans = 0;
		int const rt = 1;
		for (int i = 1; i <= n; ++i) head[i] = 0;
		for (int i = 1; i <= n; ++i) {
			fa[i] = read(); a[i] = read(); v[i] = read();
			if (fa[i] != 0)
				add(fa[i], i);
		}
		memset(F + index(rt, 0), 0, (k + 1) * sizeof(int));
		memset(G + index(rt, 0), 0, (k + 1) * sizeof(int));
		dfsL(rt);
		for (int i = 1; i <= n; ++i) head[i] = 0;
		for (int i = n; i >= 1; --i) if (fa[i] != 0) add(fa[i], i);
		dfsR(rt, 0);
		printf("%d\n", ans);
	}
	return 0;
}