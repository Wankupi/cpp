#include <algorithm>
#include <cctype>
#include <cstdio>
void read(int &x) {
	char c = getchar(); bool f = false; x = 0;
	while (!isdigit(c)) { if (c == '-') f = true; c = getchar(); }
	while (isdigit(c)) { x = (x << 1) + (x << 3) + c - '0'; c = getchar(); }
	if (f) x = -x;
}
const int maxn = 200001;
int n = 0, m = 0;
struct Data { int p, v; } d[maxn];
bool operator<(const Data &l, const Data &r) { return l.v < r.v; }
bool operator==(const Data &l, const Data &r) { return l.v == r.v; }
int id[maxn];
int root[maxn];
struct Node { int l, r, c; };
Node tree[maxn << 5];
int cnt = 0;
void create(int &p,int L,int R) {
	p = ++cnt;
	if(L==R) return;
	int mid = (L + R) >> 1;
	create(tree[p].l, L, mid);
	create(tree[p].r, mid + 1, R);
}
void add(int &p, int L, int R, int x) {
	tree[++cnt] = tree[p];
	p = cnt;
	if (L == R) { ++tree[p].c; return; }
	int mid = (L + R) >> 1;
	x <= mid ? add(tree[p].l, L, mid, x) : add(tree[p].r, mid + 1, R, x);
	tree[p].c = tree[tree[p].l].c + tree[tree[p].r].c;
}
int query(int p1,int p2,int L,int R,int k) {
	if(L==R)  return L;
	int mid = (L + R) >> 1;
	Node &q1 = tree[p1], &q2 = tree[p2];
	if(tree[q1.l].c - tree[q2.l].c >= k)
		return query(q1.l, q2.l, L, mid, k);
	else
		return query(q1.r, q2.r, mid + 1, R, k - tree[q1.l].c + tree[q2.l].c);
}
int main() {
	read(n); read(m);
	for (int i = 1; i <= n; ++i)
		read(d[i].v), d[i].p = i;
	std::sort(d + 1, d + n + 1);
	for (int i = 1; i <= n;++i)
		id[d[i].p] = i;
	create(root[0], 1, n);
	for (int i = 1; i <= n;++i)
		add(root[i] = root[i - 1], 1, n, id[i]);
	int l = 0, r = 0, k = 0;
	for (int i = 1; i <= m;++i) {
		read(l); read(r); read(k);
		printf("%d\n", d[query(root[r], root[l - 1], 1, n, k)].v);
	}
	return 0;
}