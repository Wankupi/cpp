#include <cstdio>
#include <algorithm>
int const maxn = 100001, bit = 17;
int n = 0;
int c[maxn]; //color 0 is white, 1 is black
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insertEdge(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }

int tr[maxn << 7][2], cntTri = 0;
bool cover[maxn << 7]; int tag[maxn << 7];

inline void TAG(int p, int dep, int v) {
	if (dep == -1) return;
	tag[p] ^= v;
	if ((v >> dep) & 1) std::swap(tr[p][0], tr[p][1]); 
}
inline void pushdown(int p, int dep) {
	if (dep == -1) return;
	if (tag[p] == 0) return;
	if (tr[p][0]) TAG(tr[p][0], dep - 1, tag[p]);
	if (tr[p][1]) TAG(tr[p][1], dep - 1, tag[p]);
	tag[p] = 0;
}
void insert(int &p, int x, int dep) {
	if (p == 0) p = ++cntTri;
	if (dep == -1) { cover[p] = true; return; }
	pushdown(p, dep);
	int c = (x >> dep) & 1;
	insert(tr[p][c], x, dep - 1);
	cover[p] = (tr[p][0] != 0 && tr[p][1] != 0 && cover[tr[p][0]] && cover[tr[p][1]]);
}
inline void XORwith(int p, int v) { if (p == 0) return; TAG(p, bit, v); }
int merge(int x, int y, int dep) {
	if (x == 0 || y == 0) return x | y;
	if (cover[x]) return x; // for the leaf's [cover] must be true, don't check dep == -1
	if (cover[y]) return y;
	pushdown(x, dep);
	pushdown(y, dep);
	tr[x][0] = merge(tr[x][0], tr[y][0], dep - 1);
	tr[x][1] = merge(tr[x][1], tr[y][1], dep - 1);
	cover[x] = (tr[x][0] != 0 && tr[x][1] != 0 && cover[tr[x][0]] && cover[tr[x][1]]);
	return x;
}
int mex(int p) {
	if (p == 0) return 0;
	int r = 0;
	for (int j = bit; j >= 0; --j) {
		if (tr[p][0] == 0) break;
		if (!cover[tr[p][0]]) p = tr[p][0];
		else {
			r |= (1 << j);
			p = tr[p][1];
			if (p == 0) break;
		}
	}
	return r;
}
int sg[maxn];
int root[maxn];
void dfs(int x, int f) {
	int SgSum = 0;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs(to[i], x);
			SgSum ^= sg[to[i]];
		}
	if (c[x] == 0) insert(root[x], SgSum, bit);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			XORwith(root[to[i]], SgSum ^ sg[to[i]]);
			root[x] = merge(root[x], root[to[i]], bit);
		}
	sg[x] = mex(root[x]);
}
bool ok[maxn];
void getAns(int x, int f, int v) {
	for (int i = head[x]; i; i = nxt[i]) if (to[i] != f) v ^= sg[to[i]];
	ok[x] = (c[x] == 0 && v == 0);
	for (int i = head[x]; i; i = nxt[i]) if (to[i] != f) getAns(to[i], x, v ^ sg[to[i]]);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", c + i);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		insertEdge(x, y); insertEdge(y, x);
	}
	dfs(1, 0);
	if (sg[1] == 0) puts("-1");
	else {
		getAns(1, 0, 0);
		for (int i = 1; i <= n; ++i)
			if (ok[i]) printf("%d ", i);
	}
	return 0;
}