#include <cstdio>
#include <algorithm>
typedef long long ll;
int const maxn = 1000003;
ll const inf = 0x3f3f3f3f3f3f3f3f;
int n = 0, q = 0;

struct Global {
	inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
	void dfs1(int x, int y);
	void dfs2(int x, int t);
	int lca(int x, int y);
	inline int dis(int x, int y) { return dep[x] + dep[y] - 2 * dep[lca(x, y)]; }
	
	int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
	int fa[maxn], son[maxn], top[maxn], dep[maxn], siz[maxn];
	int dfn[maxn];
};
struct Virtual {
	inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
	struct Result {
		long long Maxlen, Minlen, siz;
	};
	Result dfs(int x);
	int head[maxn], nxt[maxn], to[maxn], val[maxn], cnt = 0;
};
Global glo;
Virtual vir;
ll MinVal = inf, MxVal = 0, SumVal = 0;
int s[maxn], t = 0, root = 0;
bool chosen[maxn];
int st[maxn], top = 0;
inline bool cmp(int x, int y) { return glo.dfn[x] < glo.dfn[y]; }
void CreateVirtualTree() {
	std::sort(s + 1, s + t + 1, cmp);
	int (&dfn)[maxn] = glo.dfn;
	vir.cnt = 0;
	root = st[top = 1] = s[1];
	for (int i = 2; i <= t; ++i) {
		int lca = glo.lca(st[top], s[i]);
		while (top > 1 && dfn[lca] <= dfn[st[top - 1]]) {
			vir.insert(st[top - 1], st[top], glo.dis(st[top - 1], st[top]));
			--top;
		}
		if (st[top] != lca) {
			vir.insert(lca, st[top], glo.dis(lca, st[top]));
			st[top] = lca;
			if (top == 1) root = lca;
		}
		st[++top] = s[i];
	}
	while (--top > 0) vir.insert(st[top], st[top + 1], glo.dis(st[top], st[top + 1]));
}

int main() {
	scanf("%d", &n);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		glo.insert(x, y);
		glo.insert(y, x);
	}
	glo.dfs1(1, 0);
	glo.dfs2(1, 1);
	scanf("%d", &q);
	for (int T = 1; T <= q; ++T) {
		scanf("%d", &t);
		for (int i = 1; i <= t; ++i) scanf("%d", s + i);
		MinVal = inf;
		SumVal = MxVal = 0;
		CreateVirtualTree();
		for (int i = 1; i <= t; ++i) chosen[s[i]] = true;
		vir.dfs(root);
		for (int i = 1; i <= t; ++i) chosen[s[i]] = false;

		printf("%lld %lld %lld\n", SumVal, MinVal, MxVal);
	}
	return 0;
}

void Global::dfs1(int x, int f) {
	siz[x] = 1;
	dep[x] = dep[f] + 1;
	fa[x] = f;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x]) {
			dfs1(to[i], x);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
		}
}

void Global::dfs2(int x, int t) {
	dfn[x] = ++dfn[0];
	top[x] = t;
	if (son[x]) dfs2(son[x], t);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x] && to[i] != son[x])
			dfs2(to[i], to[i]);
}

inline int Global::lca(int x, int y) {
	while (top[x] != top[y]) dep[top[x]] > dep[top[y]] ? (x = fa[top[x]]) : (y = fa[top[y]]);
	return dep[x] > dep[y] ? y : x;
}

Virtual::Result Virtual::dfs(int x) {
	Result res;
	res.siz = chosen[x];
	res.Maxlen = 0;
	res.Minlen = inf;
	long long Mx = 0, ciMax = 0;
	long long Mi = inf, ciMin = inf;
	for (int i = head[x]; i; i = nxt[i]) {
		Result r = dfs(to[i]);
		r.Maxlen += val[i];
		r.Minlen += val[i];
		if (r.Maxlen > Mx) { ciMax = Mx; Mx = r.Maxlen; }
		else if (r.Maxlen > ciMax) { ciMax = r.Maxlen; }
		if (r.Minlen < Mi) { ciMin = Mi; Mi = r.Minlen; }
		else if (r.Minlen < ciMin) { ciMin = r.Minlen; }
		res.siz += r.siz;
		SumVal += (long long)val[i] * r.siz * (t - r.siz);
	}
	MinVal = std::min(MinVal, Mi + ciMin);
	MxVal = std::max(MxVal, Mx + ciMax);
	if (chosen[x]) {
		MinVal = std::min(MinVal, Mi);
		MxVal = std::max(MxVal, Mx);
		res.Minlen = 0;
	}
	else res.Minlen = Mi;
	res.Maxlen = Mx;
	head[x] = 0;
	return res;
}
