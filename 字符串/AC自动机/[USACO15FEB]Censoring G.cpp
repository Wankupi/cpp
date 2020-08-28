#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int const maxn = 100003;
int tr[maxn][26], cnt = 0;
int fail[maxn], Len[maxn];
bool isEnd[maxn];
int insert(char *s) {
	int p = 0;
	while (*s) {
		int c = *s++ - 'a';
		if (tr[p][c] == 0) tr[p][c] = ++cnt;
		Len[tr[p][c]] = Len[p] + 1;
		p = tr[p][c];
	}
	isEnd[p] = true;
	return p;
}
void GetFail() {
	queue<int> q;
	for (int i = 0; i < 26; ++i)
		if (tr[0][i]) q.push(tr[0][i]);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < 26; ++i)
			if (tr[x][i]) {
				fail[tr[x][i]] = tr[fail[x]][i];
				q.push(tr[x][i]);
			}
			else
				tr[x][i] = tr[fail[x]][i];
	}
}
char S[maxn], t[maxn];
int End[maxn];
int last[maxn][21], nxt[maxn], at[maxn];
int main() {
	scanf("%s", S + 1);
	int n = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", t);
		End[i] = insert(t);
	}
	GetFail();
	int len = strlen(S + 1), p = 0;
	nxt[0] = 1;
	last[1][0] = 0;
	for (int i = 1; i <= len; ++i) {
		int c = S[i] - 'a';
		p = tr[p][c];
		at[i] = p;
		for (int j = 1; j <= 19; ++j)
			last[i][j] = last[last[i][j - 1]][j - 1];
		if (isEnd[p]) {
			int y = i, k = Len[p];
			for (int j = 19; ~j; --j)
				if ((k >> j) & 1)
					y = last[y][j];
			p = at[y];
			last[i + 1][0] = y;
			nxt[y] = i + 1;
		}
		else {
			last[i + 1][0] = i;
			nxt[i] = i + 1;
		}
	}
	for (int i = nxt[0]; i <= len; i = nxt[i])
		putchar(S[i]);
	putchar('\n');
	return 0;
}