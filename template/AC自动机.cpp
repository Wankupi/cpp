#include <cstdio>
#include <queue>
using namespace std;
int n = 0;
char T[200010], S[2000010];
int tri[2000000][26], fail[2000000], cnt = 0;
int strCnt[2000000], ind[2000000];
int pos[200001];
bool in[2000000];
int insert(char *s) { // add a string on tri tree
	int p = 0;
	while (*s != 0) {
		int c = *s++ - 'a';
		if (!tri[p][c]) tri[p][c] = ++cnt;
		p = tri[p][c];
	}
	return p;
}
int head[2000000], nxt[2000000], to[2000000], Adcnt = 0;
// add an edge.
inline void insert(int u, int e) { nxt[++Adcnt] = head[u]; head[u] = Adcnt; to[Adcnt] = e; }
void getFail() {
	queue<int> q;
	for (int i = 0; i != 26; ++i)
		if (tri[0][i]) {
			fail[tri[0][i]] = 0;
			q.push(tri[0][i]);
			insert(0, tri[0][i]);
		}
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = 0; i != 26; ++i) {
			if (tri[x][i]) {
				fail[tri[x][i]] = tri[fail[x]][i];
				q.push(tri[x][i]);
				insert(tri[fail[x]][i], tri[x][i]);
			}
			else tri[x][i] = tri[fail[x]][i];
			++ind[tri[fail[x]][i]];
		}
	}
}
void search(char *s) {
	int p = 0;
	char c = 0;
	while (c = *s++) {
		c -= 'a';
		p = tri[p][c];
		++strCnt[p];
	}
}
void dfs(int x) {
	for (int i = head[x]; i; i = nxt[i]) {
		dfs(to[i]);
		strCnt[x] += strCnt[to[i]];
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", T);
		pos[i] = insert(T);
	}
	scanf("%s", S);
	getFail();
	search(S);
	dfs(0);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", strCnt[pos[i]]);
	return 0;
}