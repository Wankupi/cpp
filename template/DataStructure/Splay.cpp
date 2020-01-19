class Splay {
public:
	Splay() :cnt(0), root(0), value{ 0 }, fa{ 0 }, son{ {0} }, siz{ 0 }, recy{ 0 } {}
	void insert(int x);
	void erase(int x);
	int getRank(int x);
	int queryRank(int k);
	int pre(int x);		// return position
	int nxt(int x);		// return position
	int find(int x);	// return position
	int getValue(int p) { return value[p]; }
private:
	int root;
	int value[100000];
	int fa[100000], son[100000][2];
	int siz[100000], recy[100000];
	int cnt;
private:
	void clear(int p) { value[p] = fa[p] = son[p][0] = son[p][1] = siz[p] = recy[p] = 0; }
	int newPoint(int x) {
		value[++cnt] = x;
		siz[cnt] = recy[cnt] = 1;
		return cnt;
	}
	void updata(int p) { if (p) { siz[p] = recy[p] + siz[son[p][0]] + siz[son[p][1]]; } }
	int get(int p) { return son[fa[p]][1] == p; }
	void connect(int x, int y, int relation) {
		if (x) fa[x] = y;
		if (y) son[y][relation] = x;
	}
	void rotate(int x) {
		int f = fa[x], ff = fa[fa[x]],
			m = get(x), n = get(fa[x]);
		connect(son[x][m ^ 1], f, m);
		connect(f, x, m ^ 1);
		connect(x, ff, n);
		updata(f);
		updata(x);
	}
	void splay(int p) {
		int f = 0;
		while (f = fa[p]) {
			if (fa[f]) rotate(get(p) == get(f) ? f : p);
			rotate(p);
		}
		root = p;
	}
};
void Splay::insert(int x) {
	if (!root) { root = newPoint(x); return; }
	int p = root;
	while (p) {
		if (value[p] == x) {
			++recy[p]; ++siz[p];
			updata(fa[p]); splay(p);
			return;
		}
		bool c = (x > value[p]);
		if (!son[p][c]) {
			son[p][c] = newPoint(x);
			fa[son[p][c]] = p;
			updata(p);
			splay(son[p][c]);
			return;
		}
		p = son[p][c];
	}
}
void Splay::erase(int x) {
	int p = find(x);
	if (recy[p] > 1) { --recy[p]; --siz[p]; return; }
	if (son[p][0] == 0) {
		root = son[p][1];
		fa[son[p][1]] = 0;
		clear(p);
	}
	else if (son[p][1] == 0) {
		root = son[p][0];
		fa[son[p][0]] = 0;
		clear(p);
	}
	else {
		int nt = pre(x);
		splay(nt);
		connect(son[p][1], root, 1);
		clear(p);
		updata(root);
	}
}
int Splay::getRank(int x) {
	int p = root, ans = 0;
	while (p) {
		if (value[p] > x) { p = son[p][0]; continue; }
		ans += siz[son[p][0]];
		if (value[p] == x) { splay(p); return ans + 1; }
		ans += recy[p];
		p = son[p][1];
	}
	return ans + 1;
}
int Splay::queryRank(int k) {
	int p = root;
	while (p) {
		if (son[p][0] && siz[son[p][0]] >= k) { p = son[p][0]; continue; }
		k -= siz[son[p][0]];
		if (k <= recy[p]) { splay(p); return value[p]; }
		k -= recy[p];
		p = son[p][1];
	}
	return 0;
}
int Splay::find(int x) {
	int p = root;
	while (p && value[p] != x) p = son[p][value[p] < x];
	splay(p);
	return p;
}
int Splay::pre(int x) {
	int p = root, ans = 0;
	while (p) {
		if (value[p] >= x) { p = son[p][0]; continue; }
		else {
			ans = p; p = son[p][1];
		}
	}
	return ans;
}
int Splay::nxt(int x) {
	int p = root, ans = 0;
	while (p) {
		if (value[p] <= x) { p = son[p][1]; continue; }
		else {
			ans = p; p = son[p][0];
		}
	}
	return ans;
}

#include <cstdio>
Splay tree;
int main() {
	int n = 0;
	scanf("%d", &n);
	int opt = 0, x = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &opt, &x);
		if (opt == 1)		tree.insert(x);
		else if (opt == 2)	tree.erase(x);
		else if (opt == 3)	printf("%d\n", tree.getRank(x));
		else if (opt == 4)	printf("%d\n", tree.queryRank(x));
		else if (opt == 5)	printf("%d\n", tree.getValue(tree.pre(x)));
		else if (opt == 6)	printf("%d\n", tree.getValue(tree.nxt(x)));
	}
	return 0;
}