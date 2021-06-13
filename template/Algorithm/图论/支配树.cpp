#include <cstdio>
#include <queue>
int const maxn = 200003, maxm = 300003;

template<int N, int M>
struct Graph {
	int head[N], nxt[M], to[M], cnt;
	void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
	void clear(int n) { cnt = 0; for (int i = 0; i <= n; ++i) head[i] = 0;}
};

int n = 0, m = 0;

Graph<maxn, maxm> G, F;
Graph<maxn, maxn> T;

int fa[maxn], dfn[maxn], idfn[maxn], cdfn = 0;
int semi[maxn], idom[maxn];

void dfs(int x) {
	dfn[x] = ++cdfn; idfn[cdfn] = x;
	for (int i = G.head[x]; i; i = G.nxt[i])
		if (!dfn[G.to[i]]) {
			fa[G.to[i]] = x;
			dfs(G.to[i]);
		}
}

inline int min_dfn(int x, int y) { return dfn[x] < dfn[y] ? x : y; }

namespace ADT {
	int fa[maxn], val[maxn];
	inline void init() {
		for (int i = 1; i <= n; ++i) fa[i] = i;
		// val is 0, and dfn[0] is put bigger than n.
	}
	int find(int x) {
		if (fa[x] == x) return x;
		int y = fa[x];
		fa[x] = find(fa[x]);
		if (dfn[semi[val[x]]] > dfn[semi[val[y]]]) val[x] = val[y];
		return fa[x];
	}
	inline void merge(int x, int y) { // x <-- y
		x = find(x); y = find(y);
		fa[y] = x;
	}
};

int deg[maxn], siz[maxn];

int main() {
	scanf("%d %d", &n, &m);
	int x = 0, y = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		G.insert(x, y);
		F.insert(y, x);
	}

	dfs(1);
	dfn[0] = n + 1; // prepare for comparation
	ADT::init();

	for (int i = n; i >= 1; --i) {
		x = idfn[i];
		for (int j = F.head[x]; j; j = F.nxt[j]) { // get semi[x]
			y = F.to[j];
			if (dfn[y] < dfn[x]) semi[x] = min_dfn(semi[x], y);
			else {
				ADT::find(y);
				semi[x] = min_dfn(semi[x], semi[ADT::val[y]]);
			}
		}
		for (int j = T.head[x]; j; j = T.nxt[j]) { // work for the "y"s which semi[y] = x
			y = T.to[j];
			ADT::find(y);
			int z = ADT::val[y];
			if (dfn[semi[z]] == dfn[x]) idom[y] = x; // equal to idom[y]=semi[y]
			else idom[y] = z; // coorect later
		}

		ADT::val[x] = x;
		ADT::merge(fa[x], x);
		T.insert(semi[x], x); // a query.
	}
	for (int i = 2; i <= n; ++i) {
		x = idfn[i];
		if (idom[x] != semi[x]) idom[x] = idom[idom[x]];
	}

	for (int i = n; i >= 1; --i) {
		x = idfn[i];
		++siz[x];
		if (idom[x]) siz[idom[x]] += siz[x];
	}

	for (int i = 1; i <= n; ++i) printf("%d ", siz[i]);
	return 0;
}