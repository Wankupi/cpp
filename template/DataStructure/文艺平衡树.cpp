#include <cstdio>
#include <algorithm>
using std::swap;
const int maxn = 100003;
int n = 0;
struct Node {
	int fa, son[2];
	int id, cnt;
	int lazy;
};
Node tr[maxn];
int ct = 0, root = 0;
//int ID[maxn];
int NewNode(int val, int f) {
	++ct;
	tr[ct].fa = f;
	tr[ct].id = val;
	tr[ct].lazy = 0;
	tr[ct].cnt = 1;
	return ct;
}
inline void pushDown(int x) {
	if (x && tr[x].lazy == 1) {
		swap(tr[x].son[0], tr[x].son[1]);
		if (tr[x].son[0]) tr[tr[x].son[0]].lazy ^= 1;
		if (tr[x].son[1]) tr[tr[x].son[1]].lazy ^= 1;
		tr[x].lazy = 0;
	}
};
inline void update(int x) {
	tr[x].cnt = tr[tr[x].son[0]].cnt + tr[tr[x].son[1]].cnt + 1;
}
int Create(int L, int R, int f) {
	if (L > R) return 0;
	int mid = (L + R) >> 1;
	int p = NewNode(mid, f);
	if (L == R) return p;
	tr[p].son[0] = Create(L, mid - 1, p);
	tr[p].son[1] = Create(mid + 1, R, p);
	update(p);
	return p;
}
inline int iden(int x) { return tr[tr[x].fa].son[1] == x; }
inline void connect(int s, int f, int re) {
	if (s) tr[s].fa = f;
	if (f) tr[f].son[re] = s;
}

void rotate(int x) {
	int f = tr[x].fa; int z = tr[f].fa;
	pushDown(z); pushDown(f); pushDown(x);
	int m = iden(x), n = iden(f);
	connect(tr[x].son[m ^ 1], f, m);
	connect(x, z, n);
	connect(f, x, m ^ 1);
	update(f);
	update(x);
}
inline void splay(int x, int top) {
	for (; tr[x].fa != top; rotate(x))
		if (tr[tr[x].fa].fa != top)
			rotate(iden(tr[x].fa) == iden(x) ? tr[x].fa : x);
	if (top == 0) root = x;
}
int find(int k) {
	int p = root;
	while (p) {
		pushDown(p);
		if (tr[tr[p].son[0]].cnt >= k) p = tr[p].son[0];
		else {
			k -= tr[tr[p].son[0]].cnt + 1;
			if (!k) break;
			p = tr[p].son[1];
		}
	}
	return p;
}
void reverse(int L, int R) {
	int LL = find(L);
	splay(LL, 0);
	int RR = find(R + 2);
	splay(RR, LL);
	tr[tr[RR].son[0]].lazy ^= 1;
}

void output(int p) {
	pushDown(p);
	//printf(" [ ");
	if (tr[p].son[0]) output(tr[p].son[0]);
	if (tr[p].id > 0 && tr[p].id <= n) printf("%d ", tr[p].id);
	if (tr[p].son[1]) output(tr[p].son[1]);
	//printf(" ] ");
}
int main() {
	int m = 0, l = 0, r = 0;
	scanf("%d%d", &n, &m);
	root = Create(0, n + 1, 0);
	//output(root);
	//printf("\n");
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &l, &r);
		reverse(l, r);
	}
	output(root);
	return 0;
}