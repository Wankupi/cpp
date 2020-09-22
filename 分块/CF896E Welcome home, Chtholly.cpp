#include <cmath>
#include <cstdio>
using namespace std;
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9')
		x = 10 * x + c - '0', c = getchar();
	return x;
}
int const N = 100003, S = 320;
int n = 0, m = 0, block = 0;
int a[N], last[N];
int id[N];
int fa[N], siz[N], val[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int merge(int x, int y) { // 有向合并
	x = find(x);
	y = find(y);
	if (x == y) return y;
	fa[x] = y;
	siz[y] += siz[x];
	return y;
}
struct BCJ {
	int valRt[N];
	void add(int v, int pos) {
		if (!valRt[v])
			valRt[v] = pos;
		else
			valRt[v] = merge(pos, valRt[v]);
	}
	void combine(int x, int y) { // x -> y
		if (!valRt[x]) return;
		if (!valRt[y])
			valRt[y] = valRt[x];
		else
			valRt[y] = merge(valRt[x], valRt[y]);
		valRt[x] = 0;
		val[valRt[y]] = y;
	}
};
BCJ g[S];
int mx[S], l[S], r[S], tag[S];

void reGet(int k) {
	for (int i = l[k]; i <= r[k]; ++i)
		a[i] = val[find(i)] - tag[k];
	for (int i = l[k]; i <= r[k]; ++i)
		fa[i] = siz[i] = g[k].valRt[a[i] + tag[k]] = 0;
	tag[k] = 0;
}
void build(int k) {
	mx[k] = 0;
	for (int i = l[k]; i <= r[k]; ++i) {
		fa[i] = i, siz[i] = 1;
		val[i] = a[i];
		if (a[i] > mx[k]) mx[k] = a[i];
		g[k].add(a[i], i);
	}
}

void init() {
	for (int k = 1; r[k - 1] != n; ++k) {
		l[k] = r[k - 1] + 1;
		r[k] = l[k] + block - 1;
		if (r[k] > n) r[k] = n;
		for (int i = l[k]; i <= r[k]; ++i) id[i] = k;
		build(k);
	}
}

inline int query(int k, int L, int R, int x) {
	int ret = 0;
	for (int i = L; i <= R; ++i)
		if (val[find(i)] - tag[k] == x) ++ret;
	return ret;
}
inline int query(int k, int x) {
	if (x + tag[k] > 100000) return 0;
	return siz[g[k].valRt[x + tag[k]]];
}
inline void modify(int k, int L, int R, int x) {
	reGet(k);
	for (int i = L; i <= R; ++i)
		if (a[i] > x) a[i] -= x;
	build(k);
}
inline void modify(int k, int x) {
	if (mx[k] <= x) return;
	if (mx[k] <= 2 * x) {
		for (int v = x + 1; v <= mx[k]; ++v)
			g[k].combine(v + tag[k], v - x + tag[k]);
		mx[k] = x; // ?????
	}
	else {
		for (int v = 1; v <= x; ++v)
			g[k].combine(v + tag[k], v + x + tag[k]);
		tag[k] += x;
		mx[k] -= x;
	}
}
int Query(int L, int R, int x) {
	int bl = id[L], br = id[R];
	if (bl == br)
		return query(bl, L, R, x);
	else {
		int sum = 0;
		sum += query(bl, L, r[bl], x);
		sum += query(br, l[br], R, x);
		for (int i = bl + 1; i < br; ++i)
			sum += query(i, x);
		return sum;
	}
}
void Modify(int L, int R, int x) {
	int bl = id[L], br = id[R];
	if (bl == br)
		modify(bl, L, R, x);
	else {
		modify(bl, L, r[bl], x);
		modify(br, l[br], R, x);
		for (int i = bl + 1; i < br; ++i)
			modify(i, x);
	}
}
int main() {
	n = read();
	m = read();
	block = int(ceil(sqrt(n)));
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	init();
	int opt = 0, L = 0, R = 0, x = 0;
	for (int i = 1; i <= m; ++i) {
		opt = read();
		L = read();
		R = read();
		x = read();
		if (opt == 1)
			Modify(L, R, x);
		else 
			printf("%d\n", Query(L, R, x));
	}
	return 0;
}