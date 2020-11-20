#include <cstdio>
#include <vector>
using namespace std;
int const maxn = 100003, inf = 0x7fffffff;

inline int read() {
	int x = 0, c = getchar();
	while (c < '0' && c < '9')
		c = getchar();
	while ('0' <= c && c <= '9')
		x = 10 * x + c - '0', c = getchar();
	return x;
}

int n = 0, m = 0;
int value[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}

namespace Euler {
	int first[maxn], dep[maxn];
	int id[maxn << 1], cnt = 0;
	void dfs(int x, int f) {
		first[x] = ++cnt;
		id[cnt] = x;
		dep[x] = dep[f] + 1;
		for (int i = head[x]; i; i = nxt[i])
			if (to[i] != f) {
				dfs(to[i], x);
				id[++cnt] = x;
			}
	}
	int mi[17][maxn << 1];
	int lg2[maxn << 1];
	void init() {
		dfs(1, 0);
		for (int i = 1; i <= cnt; ++i)
			mi[0][i] = dep[id[i]];
		for (int j = 1; j <= 16; ++j) {
			for (int i = 1; i <= cnt - (1 << j) + 1; ++i)
				mi[j][i] = std::min(mi[j - 1][i], mi[j - 1][i + (1 << (j - 1))]);
		}
		lg2[1] = 0;
		for (int i = 2; i <= cnt; ++i) // notice 2*n
			lg2[i] = lg2[i >> 1] + 1;
	}
	inline int query(int l, int r) {
		int k = lg2[r - l + 1];
		return std::min(mi[k][l], mi[k][r - (1 << k) + 1]);
	}
	inline int dis(int x, int y) {
		if (first[x] > first[y]) std::swap(x, y);
		return dep[x] + dep[y] - 2 * query(first[x], first[y]);
	}
} // namespace Euler
using Euler::dis;
namespace PointDevideTree {
	int SizAll = 0, root = 0, s_rt = inf; // use in find_root
	bool ban[maxn];
	int maxDis[maxn], maxDisF[maxn];
	vector<int> G[maxn], T[maxn];
	int fa[maxn];
	int siz[maxn], dep[maxn];
	void find_root(int x, int f) {
		siz[x] = 1;
		dep[x] = dep[f] + 1;
		int MxSon = 0;
		for (int i = head[x]; i; i = nxt[i])
			if (!ban[to[i]] && to[i] != f) {
				find_root(to[i], x);
				siz[x] += siz[to[i]];
				if (siz[to[i]] > MxSon) MxSon = siz[to[i]];
			}
		MxSon = std::max(SizAll - siz[x], MxSon);
		if (MxSon < s_rt) {
			root = x;
			s_rt = MxSon;
		}
	}
	void getMaxDis(int x, int f, int ori) {
		siz[x] = 1;
		dep[x] = dep[f] + 1;
		maxDis[ori] = max(maxDis[ori], dep[x]);
		if (fa[ori]) maxDisF[ori] = max(maxDisF[ori], Euler::dis(x, fa[ori]));
		for (int i = head[x]; i; i = nxt[i])
			if (!ban[to[i]] && to[i] != f) {
				getMaxDis(to[i], x, ori);
				siz[x] += siz[to[i]];
			}
	}
	void solve(int x) {
		ban[x] = true;
		dep[x] = 0;
		getMaxDis(x, 0, x); // notice, dep is calc from 1
		static int sumMem = 0, sumMemF = 0;
		sumMem += maxDis[x] + 3;
		sumMemF += maxDisF[x] + 3;
		G[x].resize(maxDis[x] + 3);
		if (fa[x]) T[x].resize(maxDisF[x] + 3);
		
		// notice again that it index is count from 1 but the dis is count from 0. there should be a delta: 1.
		for (int i = head[x]; i; i = nxt[i])
			if (!ban[to[i]]) {
				SizAll = siz[to[i]];
				root = 0;
				s_rt = inf;
				find_root(to[i], x);
				fa[root] = x;
				solve(root);
			}
	}
	inline int lowbit(int x) { return x & -x; }
	void add(vector<int> &tr, int Limit, int p, int v) {
		while (p <= Limit) {
			tr[p] += v;
			p += lowbit(p);
		}
	}
	int query(vector<int> const &r, int Limit, int p) {
		int sum = 0;
		if (p > Limit) p = Limit;
		while (0 < p) {
			sum += r[p];
			p -= lowbit(p);
		}
		return sum;
	}
	void modify(int x, int v) {
		for (int y = x; y; y = fa[y]) {
			add(G[y], maxDis[y] + 1, dis(x, y) + 1, v);
			if (fa[y]) {
				add(T[y], maxDisF[y] + 1, dis(x, fa[y]) + 1, v);
			}
		}
	}
	int GetSum(int x, int k) {
		int ans = 0;
		for (int y = x; y; y = fa[y]) {
			ans += query(G[y], maxDis[y] + 1, k - dis(x, y) + 1); // do not check k - dis is positive, because query return 0.
			if (fa[y]) ans -= query(T[y], maxDisF[y] + 1, k - dis(x, fa[y]) + 1);
		}
		return ans;
	}
	void init() {
		SizAll = n; root = 0; s_rt = inf;
		find_root(1, 0);
		solve(root);
		for (int i = 1; i <= n; ++i)
			modify(i, value[i]);
	}
} // namespace PointDevideTree

int main() {
	n = read();
	m = read();
	for (int i = 1; i <= n; ++i)
		value[i] = read();
	int x = 0, y = 0, z = 0;
	for (int i = 1; i < n; ++i) {
		x = read();
		y = read();
		insert(x, y);
		insert(y, x);
	}
	Euler::init();
	PointDevideTree::init();
	int lastAns = 0;
	for (int i = 1; i <= m; ++i) {
		z = read(); x = read(); y = read();
		x ^= lastAns; y ^= lastAns;
		if (z == 0) {
			lastAns = PointDevideTree::GetSum(x, y);
			printf("%d\n", lastAns);
		}
		else {
			PointDevideTree::modify(x, y - value[x]);
			value[x] = y;
		}
	}
	return 0;
}