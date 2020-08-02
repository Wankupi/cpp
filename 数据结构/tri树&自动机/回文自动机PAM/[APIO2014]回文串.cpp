#include <cstdio>
const int maxn = 300003;
char s[maxn];
int len[maxn], fail[maxn], son[maxn][26];
long long cnt[maxn];
int cp = 0;
int last = 0;
void init() {
	len[0] = 0;
	len[1] = -1;
	fail[0] = 1;
	fail[1] = 0;
	cnt[0] = cnt[1] = 0;
	last = 1;
	cp = 1;
}
int getFa(int cur, int x) {
	while (s[x] != s[x - len[cur] - 1])
		cur = fail[cur];
	return cur;
}
int head[maxn], nxt[maxn], to[maxn], cL = 0;
inline void insert(int u, int e) {
	nxt[++cL] = head[u];
	head[u] = cL;
	to[cL] = e;
}
void expand(int i) {
	int c = s[i] - 'a';
	int f = getFa(last, i);
	if (son[f][c] == 0) {
		++cp;
		len[cp] = len[f] + 2;
		cnt[cp] = 0; // ought to be 1, add in the following
		fail[cp] = son[getFa(fail[f], i)][c];
		insert(fail[cp], cp);
		son[f][c] = cp;
	}
	last = son[f][c];
	++cnt[last];
}
long long ans = 0;
void dfs(int x) {
	for (int i = head[x]; i; i = nxt[i]) {
		dfs(to[i]);
		cnt[x] += cnt[to[i]];
	}
	if (x > 1 && cnt[x] * len[x] > ans) ans = cnt[x] * len[x];
}
int main() {
	scanf("%s", s + 1);
	init();
	for (int i = 1; s[i]; ++i)
		expand(i);
	dfs(0);
	dfs(1);
	printf("%lld", ans);
	return 0;
}