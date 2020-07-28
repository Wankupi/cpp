#include <cstdio>
int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
const int maxn = 500000;
int delta = 0, minVal = 0;
int root = 0;
int delCnt = 0;
int fa[maxn], ch[maxn][2];
int siz[maxn]; // 子树计数
int val[maxn], count[maxn]; // 该点权值 计数
int cT = 0;
inline void update(int x) { siz[x] = (ch[x][0] ? siz[ch[x][0]] : 0) + (ch[x][1] ? siz[ch[x][1]] : 0) + count[x]; }
inline void connect(int s, int f, int relation) {
	if (s != 0) fa[s] = f;
	if (f != 0) ch[f][relation] = s;	
}
void rotate(int x) {
	int f = fa[x]; int z = fa[f];
	int m = ch[f][1] == x, n = (ch[z][1] == f);
	connect(ch[x][m ^ 1], f, m);
	connect(x, z, n);
	connect(f, x, m ^ 1);
	update(f);
	update(x);
}
inline void splay(int x, int top) {
	for (; fa[x] != top; rotate(x))
		if (fa[fa[x]] != top)
			rotate((ch[fa[x]][1] == x) == (ch[fa[fa[x]]][1] == fa[x]) ? fa[x] : x);
	if (top == 0) root = x;
}
void insert(int v);
int pre(int v);
void erase(int v);
int rank(int k);

int main() {
	int n = 0;
	n = read();
	minVal = read();
	int opt = 0, x = 0;
	for (int i = 1; i <= n; ++i) {
		do opt = getchar(); while (opt != 'I' && opt != 'A' && opt != 'S' && opt != 'F');
		x = read();
		if (opt == 'I') {
			if (x >= minVal) insert(x - delta);
		}
		else if (opt == 'A') delta += x;
		else if (opt == 'S') {
			delta -= x;
			erase(minVal - delta);
		}
		else {
			int r = rank(x);
			printf("%d\n", r == -1 ? -1 : (val[r] + delta));
		}
	}
	printf("%d", delCnt);
	return 0;
}
void insert(int v) {
	if (root == 0) {
		root = ++cT;
		siz[root] = count[root] = 1;
		val[root] = v;
		return;
	}
	int p = root;
	while (val[p] != v) {
		int c = (val[p] < v);
		if (!ch[p][c]) {
			ch[p][c] = ++cT;
			fa[ch[p][c]] = p;
			val[ch[p][c]] = v;
		}
		p = ch[p][c];
	}
	++siz[p];
	++count[p];
	splay(p, 0);
}

int pre(int v) { //不包括相等
	int p = root, ans = 0;
	while (p) {
		if (val[p] < v) { ans = p; p = ch[p][1]; }
		else p = ch[p][0];
	}
	if (ans) splay(ans, 0);
	return ans;
}

inline void erase(int v) {
	int p = pre(v);
	if (p) {
		fa[ch[p][1]] = 0;
		root = ch[p][1];
		delCnt += siz[ch[p][0]] + count[p];
		// ch[p][1] = 0; 应该不会影响答案
	}
}

int rank(int k) {
	int p = root;
	if (siz[p] < k) return -1;
	while (p) {
		if (siz[ch[p][1]] >= k) { p = ch[p][1]; continue; }
		if (count[p] >= k - siz[ch[p][1]]) break;
		k -= siz[ch[p][1]] + count[p];
		p = ch[p][0];
	}
	splay(p, 0);
	return p;
}

