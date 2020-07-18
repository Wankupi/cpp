#include <cstdio>
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' && '9' < c)
		c = getchar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x;
}
const int maxn = 2000003;
int n = 0, c = 0, m = 0;
int x[maxn];
int last[maxn], pre[maxn];
int head[maxn], nxt[maxn], L[maxn], idi[maxn], cnt = 0;
inline void insert(int r, int l, int identity) {
	nxt[++cnt] = head[r];
	head[r] = cnt;
	L[cnt] = l;
	idi[cnt] = identity;
}
inline int lowbit(int x) { return x & -x; }
int tr[maxn];
inline void add(int p, int v) {
	while (p <= n) {
		tr[p] += v;
		p += lowbit(p);
	}
}
inline int query(int p) {
	int res = 0;
	while (p) {
		res += tr[p];
		p -= lowbit(p);
	}
	return res;
}
int ans[maxn];
int main() {
	n = read(); c = read(); m = read();
	for (int i = 1; i <= n; ++i) {
		x[i] = read();
		pre[i] = last[x[i]];
		last[x[i]] = i;
	}
	int l = 0, r = 0;
	for (int i = 1; i <= m; ++i) {
		l = read(); r = read();
		insert(r, l, i);
	}
	for (int i = 1; i <= n; ++i) {
		add(pre[pre[i]] + 1, 1);
		add(pre[i] + 1, -1);
		for (int j = head[i]; j; j = nxt[j])
			ans[idi[j]] = query(L[j]);
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}