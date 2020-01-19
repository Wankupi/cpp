//因为多次check 会慢
#include <cstdio>
#include <cctype>
void read(int &x) {
	int c = getchar(); bool f = false; x = 0;
	while (!isdigit(c)) { if (c == '-') f = true; c = getchar(); }
	while (isdigit(c)) { x = (x << 1) + (x << 3) + c - '0'; c = getchar(); }
	if (f) x = -x;
}
const int maxn = 100000001;
int n = 0, m = 0;
int a[1000001];
int root[maxn], cnt = 0;
struct Node {
	int l, r, val;
};
Node tree[maxn];
inline void New(int &p,int v) {
	tree[p = ++cnt].val = v;
}
inline void check(int p,int L,int R) {
	if(L==R) return;
	int mid = (L + R) >> 1;
	if(!tree[p].l) New(tree[p].l, L == mid ? a[L] : 0);
	if(!tree[p].r) New(tree[p].r, mid + 1 == R ? a[R] : 0);
}
inline void clone(int &p) {
	tree[++cnt] = tree[p];
	p = cnt;
}
void modify(int &p, int L, int R, int x, int v) {
	check(p, L, R); clone(p);
	if (L == R) tree[p].val = v;
	else {
		int mid = (L + R) >> 1;
		if (x <= mid)	modify(tree[p].l, L, mid, x, v);
		else			modify(tree[p].r, mid + 1, R, x, v);
	}
}
int query(int p, int L, int R, int x) {
	check(p, L, R);
	if (L == R) return tree[p].val;
	int mid = (L + R) >> 1;
	return x <= mid ? query(tree[p].l, L, mid, x) : query(tree[p].r, mid + 1, R, x);
}
int main() {
	read(n); read(m);
	for (int i = 1; i <= n; ++i) read(a[i]);
	int b = 0, opt = 0, pos = 0, val = 0;
	for (int i = 1; i <= m; ++i) {
		read(b); read(opt); read(pos);
		root[i] = root[b];
		if (opt == 1) {
			read(val);
			modify(root[i], 1, n, pos, val);
		}
		else printf("%d\n", query(root[b], 1, n, pos));
	}
	return 0;
}