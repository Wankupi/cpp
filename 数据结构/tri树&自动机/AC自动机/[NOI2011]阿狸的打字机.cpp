#include <cstdio>
#include <vector>
#include <queue>
using std::queue;
using std::vector;
char str[100005];
int n = 0;

int tr[100005][26], len[100005], fa[100005], fail[100005];
int now = 1, root = 1, cTri = 1;
int pos[100005], cp = 0;

int head[100005], nxt[100005], to[100005], cEdge = 0; // fail tree
inline void insert(int u, int e) { nxt[++cEdge] = head[u]; head[u] = cEdge; to[cEdge] = e; }

void getFail() {
	queue<int> q;
	for (int i = 0; i < 26; ++i)
		if (tr[root][i]) {
			fail[tr[root][i]] = root;
			q.push(tr[root][i]);
		}
		else
			tr[root][i] = root;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		insert(fail[x], x);
		for (int i = 0; i < 26; ++i)
			if (tr[x][i]) {
				fail[tr[x][i]] = tr[fail[x]][i];
				q.push(tr[x][i]);
			}
			else
				tr[x][i] = tr[fail[x]][i];
	}
}
void dealString() {
	char *s = str;
	now = root;
	fa[root] = root;
	len[root] = 0;
	while (*s) {
		if ('a' <= *s && *s <= 'z') {
			if (tr[now][*s - 'a'] == 0) {
				tr[now][*s - 'a'] = ++cTri;
				fa[cTri] = now;
				len[cTri] = len[now] + 1;
			}
			now = tr[now][*s - 'a'];
		}
		else if (*s == 'P')
			pos[++cp] = now;
		else
			now = fa[now];
		++s;
	}
	getFail();
}

int dfn[100005], siz[100005], cd = 0;
void dfs1(int x) { // dfs at fail tree
	dfn[x] = ++cd;
	siz[x] = 1;
	for (int i = head[x]; i; i = nxt[i]) {
		dfs1(to[i]);
		siz[x] += siz[to[i]];
	}
}

inline int lowbit(int x) { return x & -x; }
int atr[100005];
inline void add(int p, int v) { while (p <= cd) { atr[p] += v; p += lowbit(p); } }
inline int query(int p) { int sum = 0; while (p) { sum += atr[p]; p -= lowbit(p); } return sum; }

struct Query { int pos; int id; };
vector<Query> qs[100005];
int ans[100005];
void dfs2(int x) { // dfs at tri tree
	add(dfn[x], 1);
	for (auto i : qs[x])
		ans[i.id] = query(dfn[i.pos] + siz[i.pos] - 1) - query(dfn[i.pos] - 1);
	for(int i = 0;i<26;++i) 
		if (len[tr[x][i]] > len[x]) {
			dfs2(tr[x][i]);
		}
	add(dfn[x], -1);
}
int main() {
	scanf("%s", str);
	dealString();
	dfs1(root);
	scanf("%d", &n);
	int x = 0, y = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &x, &y);
		qs[pos[y]].push_back({ pos[x],i });
	}
	dfs2(root);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}