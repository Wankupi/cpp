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
void create(int &p, int L, int R) {
	p = ++cnt;
	if (L == R) {
		tree[p].val = a[L];
		return;
	}
	int mid = (L + R) >> 1;
	create(tree[p].l, L, mid);
	create(tree[p].r, mid + 1, R);
}
inline int clone(int p) {
	tree[++cnt] = tree[p];
	return cnt;
}
int modify(int p, int L, int R, int x, int v) {
	p = clone(p);
	if (L == R) {
		tree[p].val = v;
	}
	else {
		int mid = (L + R) >> 1;
		if (x <= mid)	tree[p].l = modify(tree[p].l, L, mid, x, v);
		else			tree[p].r = modify(tree[p].r, mid + 1, R, x, v);
	}
	return p;
}
int query(int p, int L, int R, int x) {
	if (L == R) return tree[p].val;
	int mid = (L + R) >> 1;
	return x <= mid ? query(tree[p].l, L, mid, x) : query(tree[p].r, mid + 1, R, x);
}
int main() {
	read(n); read(m);
	for (int i = 1; i <= n; ++i) read(a[i]);
	create(root[0], 1, n);
	int b = 0, opt = 0, pos = 0, val = 0;
	for (int i = 1; i <= m; ++i) {
		read(b); read(opt);
		read(pos);
		if (opt == 1) {
			read(val);
			root[i] = modify(root[b], 1, n, pos, val);
		}
		else {
			printf("%d\n", query(root[b], 1, n, pos));
			root[i] = root[b];
		}
	}
	return 0;
}