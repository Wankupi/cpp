#include <algorithm>
#include <cstdio>

using ll = long long;

int const maxn = 100003;
int const block = 500;
int const maxBlocks = maxn / block + 3;

inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9') {
		x = 10 * x + c - '0';
		c = getchar();
	}
	return x;
}

int n = 0, m = 0;

int L[maxBlocks], R[maxBlocks], cnt_block = 0;
int belong[maxn];

int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}

int w[maxn];
int dfn[maxn], cdfn = 0;
int siz[maxn];
void dfs(int x, int fa) {
	dfn[x] = ++cdfn;
	siz[x] = 1;
	for (int i = head[x]; i; i = nxt[i]) {
		if (to[i] == fa) continue;
		dfs(to[i], x);
		siz[x] += siz[to[i]];
	}
}

int chain[maxBlocks][maxn]; // be init in dfs2

int block_id_dfs2 = 0;
int count_nodes_in_range_dfs2 = 0;
void dfs2(int x, int fa) {
	if (L[block_id_dfs2] <= x && x <= R[block_id_dfs2])
		++count_nodes_in_range_dfs2;
	chain[block_id_dfs2][x] = count_nodes_in_range_dfs2;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa)
			dfs2(to[i], x);
	if (L[block_id_dfs2] <= x && x <= R[block_id_dfs2])
		--count_nodes_in_range_dfs2;
}

struct Array {
	ll tr[maxn];
	ll S[maxBlocks];
	ll s[maxBlocks][block + 1];
	void init() {
		for (int i = 1; i <= cnt_block; ++i) {
			S[i] = tr[R[i]];
			for (int j = L[i]; j <= R[i]; ++j)
				s[i][j - L[i] + 1] = tr[j] - tr[L[i] - 1];
		}
	}
	void add(int p, ll v) {
		int pid = (p + block - 1) / block;
		for (int j = p; j <= R[pid]; ++j)
			s[pid][j - L[pid] + 1] += v;
		for (int i = pid; i <= cnt_block; ++i)
			S[i] += v;
	}
	ll query(int l, int r) {
		int lid = (l + block - 1) / block, rid = (r + block - 1) / block;
		if (lid == rid) return s[lid][r - L[lid] + 1] - s[lid][l - L[lid]];
		ll ret = 0;
		if (r != R[rid]) {
			ret += s[rid][r - L[rid] + 1];
			--rid;
		}
		if (l != L[lid]) {
			ret += s[lid][R[lid] - L[lid] + 1] - s[lid][l - L[lid]];
			++lid;
		}
		ret += S[rid] - S[lid - 1];
		return ret;
	}
};
Array sum;

ll total[maxBlocks];

void prepare() {
	cnt_block = (n + block - 1) / block;
	for (int i = 1; i <= cnt_block; ++i) {
		L[i] = R[i - 1] + 1;
		R[i] = L[i] + block - 1;
		if (R[i] > n) R[i] = n;
		for (int j = L[i]; j <= R[i]; ++j)
			belong[j] = i;
	}
	dfs(to[head[0]], 0);
	for (int i = 1; i <= cnt_block; ++i) {
		block_id_dfs2 = i;
		dfs2(to[head[0]], 0);
	}
	for (int i = 1; i <= n; ++i)
		sum.tr[dfn[i]] = w[i];
	for (int i = 1; i <= n; ++i)
		sum.tr[i] += sum.tr[i - 1];

	for (int i = 1; i <= cnt_block; ++i) {
		for (int j = L[i]; j <= R[i]; ++j)
			total[i] += sum.tr[dfn[j] + siz[j] - 1] - sum.tr[dfn[j] - 1];
	}

	sum.init();
}

void modify(int x, int y) {
	ll delta = y - w[x];
	w[x] = y;
	sum.add(dfn[x], delta);
	for (int i = 1; i <= cnt_block; ++i)
		total[i] += delta * chain[i][x];
}

ll query(int l, int r) {
	int lid = (l + block - 1) / block, rid = (r + block - 1) / block;
	ll ret = 0;
	auto add_range = [&ret](int l, int r) {
		for (int i = l; i <= r; ++i)
			ret += sum.query(dfn[i], dfn[i] + siz[i] - 1);
	};
	if (lid == rid) {
		add_range(l, r);
		return ret;
	}
	if (l != L[lid])
		add_range(l, R[lid++]);
	if (r != R[lid])
		add_range(L[rid--], r);
	for (int i = lid; i <= rid; ++i)
		ret += total[i];
	return ret;
}

int main() {
	n = read();
	m = read();
	for (int i = 1; i <= n; ++i)
		w[i] = read();
	for (int i = 1; i <= n; ++i) {
		int u = read(), v = read();
		insert(u, v);
		insert(v, u);
	}
	prepare();
	for (int i = 1; i <= m; ++i) {
		int opt = read(), x = read(), y = read();
		if (opt == 1)
			modify(x, y);
		else
			printf("%lld\n", query(x, y));
	}
	return 0;
}
