#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
int const maxn = 400003, MAXCHAR = 126, MINCHAR = 33, M = MAXCHAR - MINCHAR + 1;

int k = 0, n = 0;
int ans[maxn];

struct Graph {
	int head[maxn], nxt[maxn], to[maxn], cnt = 0;
	inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
};
Graph FailTree;

int tr[maxn][M], fail[maxn], cntPoint = 0;
inline int expand(int p, int c) { if (tr[p][c] == 0) tr[p][c] = ++cntPoint; return tr[p][c]; }
void GetFail() {
	std::queue<int> q;
	for (int i = 0; i < M; ++i) if (tr[0][i]) q.push(tr[0][i]);
	while (!q.empty()) {
		int x = q.front(); q.pop();
		FailTree.insert(fail[x], x);
		for (int i = 0; i < M; ++i)
			if (tr[x][i]) { fail[tr[x][i]] = tr[fail[x]][i]; q.push(tr[x][i]); }
			else tr[x][i] = tr[fail[x]][i];
	}
}

struct Query {
	Query(int Pos1, int Pos2, int Iden) : p1(Pos1), p2(Pos2), v1(0), v2(0), id(Iden) {}
	int p1, p2, v1, v2, id;
};
std::vector<Query> qs[maxn];
struct Modification { int p1, p2; };
std::vector<Modification> modi[maxn];
int pos[maxn];
void InsertString(char *str, int len, int id) {
	pos[len + 1] = 0;
	for (int j = 1, p = 0; j <= len; ++j) p = expand(p, str[j] - MINCHAR);
	for (int j = len, p = 0; j >= 1; --j) p = expand(p, str[j] - MINCHAR), pos[j] = p;
	for (int j = 0, p = 0; j <= len - k; ++j) {
		qs[p].push_back(Query(pos[j + k + 1], j == 0 ? -1 : pos[j + k], id));
		p = tr[p][str[j + 1] - MINCHAR];
	}
}
void DealS(char *S, int len) {
	pos[len + 1] = 0;
	for (int j = len, p = 0; j >= 1; --j) p = tr[p][S[j] - MINCHAR], pos[j] = p;
	for (int j = 0, p = 0; j <= len - k; ++j) {
		modi[p].push_back(Modification{ pos[j + k + 1], pos[j + k] });
		p = tr[p][S[j + 1] - MINCHAR];
	}
}

int dfn[maxn], siz[maxn], cdfn = 0;
int TrAr1[maxn], TrAr2[maxn];
inline int lowbit(int x) { return x & -x; }
inline void add(int *t, int p, int v) { while (p <= cdfn) { t[p] += v; p += lowbit(p); } }
inline int query(int *t, int p) { int sum = 0; while (0 < p) { sum += t[p]; p -= lowbit(p); } return sum; }
inline int querySubtree(int *t, int p) { return query(t, dfn[p] + siz[p] - 1) - query(t, dfn[p] - 1); }
void dfs1(int x) {
	dfn[x] = ++cdfn; siz[x] = 1;
	for (int i = FailTree.head[x]; i; i = FailTree.nxt[i]) { dfs1(FailTree.to[i]); siz[x] += siz[FailTree.to[i]]; }
}
void dfs2(int x) {
	for (auto &q : qs[x]) {
		q.v1 = querySubtree(TrAr1, q.p1);
		if (q.p2 != -1) q.v2 = querySubtree(TrAr2, q.p2);
	}
	for (auto mo : modi[x]) {
		add(TrAr1, dfn[mo.p1], +1); add(TrAr2, dfn[mo.p2], +1);
	}
	for (int i = FailTree.head[x]; i; i = FailTree.nxt[i]) dfs2(FailTree.to[i]);
	for (auto q : qs[x]) {
		ans[q.id] += querySubtree(TrAr1, q.p1) - q.v1;
		if (q.p2 != -1) ans[q.id] -= querySubtree(TrAr2, q.p2) - q.v2;
	}
}
char s[maxn], buff[maxn];
int main() {
	scanf("%d", &k);
	scanf("%s", s + 1);
	int lenS = strlen(s + 1);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", buff + 1);
		int len = strlen(buff + 1);
		if (len > k) InsertString(buff, len, i);
		else ans[i] = lenS - len + 1;
	}
	GetFail(); DealS(s, lenS);
	dfs1(0); dfs2(0);
	for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	return 0;
}