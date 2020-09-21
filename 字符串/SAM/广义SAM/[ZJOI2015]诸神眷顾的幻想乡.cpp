#include <cstdio>
#include <queue>
int const maxn = 100003;
int n = 0, C = 0;
int a[maxn], d[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int trie[maxn << 5][10], cntTrie = 1;
inline int TrieInsert(int p, int c) {
	if (trie[p][c] == 0) trie[p][c] = ++cntTrie;
	return trie[p][c];
}
void dfs(int x, int f, int p) {
	p = TrieInsert(p, a[x]);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f)
			dfs(to[i], x, p);
}
struct Node {
	int son[10];
	int fa;
	int len;
	int &operator[](int x) { return son[x]; }
};
Node sam[maxn << 6];
int cntSAM = 1;
int expand(int last, int c) {
	int p = last, np = ++cntSAM;
	sam[np].len = sam[p].len + 1;
	for (; p && sam[p][c] == 0; p = sam[p].fa) sam[p][c] = np;
	if (p == 0) sam[np].fa = 1;
	else {
		int q = sam[p][c];
		if (sam[q].len == sam[p].len + 1) sam[np].fa = q;
		else {
			int nq = ++cntSAM;
			sam[nq] = sam[q];
			sam[nq].len = sam[p].len + 1;
			sam[q].fa = sam[np].fa = nq;
			for (; p && sam[p][c] == q; p = sam[p].fa) sam[p][c] = nq;
		}
	}
	return np;
}
int pos[maxn << 5];
void build() {
	std::queue<int> q;
	q.push(1);
	pos[1] = 1;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < C; ++i)
			if (trie[x][i]) {
				pos[trie[x][i]] = expand(pos[x], i);
				q.push(trie[x][i]);
			}
	}
}
int main() {
	scanf("%d %d", &n, &C);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		insert(x, y);
		insert(y, x);
		++d[x];
		++d[y];
	}
	for (int i = 1; i <= n; ++i)
		if (d[i] == 1) dfs(i, 0, 1);
	build();
	long long ans = 0;
	for (int i = 1; i <= cntSAM; ++i)
		ans += sam[i].len - sam[sam[i].fa].len;
	printf("%lld\n", ans);
	return 0;
}