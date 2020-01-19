#include <cstdio>
#include <cctype>
#include <algorithm>
void read(int &x) {
	int c = getchar(); bool f = false; x = 0;
	while (!isdigit(c)) { if (c == '-') f = true; c = getchar(); }
	while (isdigit(c)) { x = (x << 1) + (x << 3) + c - '0'; c = getchar(); }
	if (f) x = -x;
}
const int maxn = 100001;
int n = 0, m = 0;
int last = 0, i = 0;
int root[maxn];
struct Node {
	int l, r;
	int fa, deep;
};
Node tree[maxn * 50];
int cnt = 0;
void Create(int &p, int L, int R) {
	p = ++cnt;
	Node &th = tree[p];
	if (L == R) {
		th.fa = L; th.deep = 1;
		th.l = th.r = 0;
		return;
	}
	int mid = (L + R) >> 1;
	Create(th.l, L, mid);
	Create(th.r, mid + 1, R);
}
void Modify(int &p, int L, int R, int x, int f,int d) {
	if (p <= last) {
		tree[++cnt] = tree[p];
		p = cnt;
	}
	if (L == R) {
		tree[p].fa = f;
		tree[p].deep = d;
		return;
	}
	int mid = (L + R) >> 1;
	if (x <= mid)	Modify(tree[p].l, L, mid, x, f,d);
	else			Modify(tree[p].r, mid + 1, R, x, f,d);
}
int query(int p, int x) {
	int mid = 0, L = 1, R = n;
	while (L != R) {
		mid = (L + R) >> 1;
		if (x <= mid)	{ p = tree[p].l; R = mid; }
		else			{ p = tree[p].r; L = mid + 1; }
	}
	return p;
}
int find(int x) {
	int me = query(root[i], x);
	return tree[me].fa == x ? me : find(tree[me].fa);
}
void merge(int a, int b) {
	int da = find(a), db = find(b);
	if(da==db) return;
	if(tree[da].deep > tree[db].deep)
		da ^= db ^= da ^= db;
	Modify(root[i], 1, n, tree[da].fa, tree[db].fa,tree[da].deep);
	if(tree[da].deep == tree[db].deep)
		Modify(root[i], 1, n, tree[db].fa, tree[db].fa, tree[db].deep + 1);
}
int main() {
	read(n); read(m);
	Create(root[0], 1, n);
	int opt = 0, a = 0, b = 0;
	for (i = 1; i <= m; ++i) {
		read(opt); read(a);
		root[i] = root[i - 1];
		if (opt == 1) {
			read(b);
			last = cnt;
			merge(a, b);
		}
		else if (opt == 2)
			root[i] = root[a];
		else {
			read(b);
			putchar(tree[find(a)].fa == tree[find(b)].fa ? '1' : '0');
			putchar('\n');
		}
	}
	return 0;
}