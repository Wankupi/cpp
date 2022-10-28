#include <cstdio>
#include <cstring>
int const maxn = 1000005, mod = 1000000007;

int fa[maxn], len[maxn], son[maxn][26], cnt = 1;
int d[maxn], pre[maxn];
int last = 1;
int f[maxn], sf[maxn];

void init() { len[1] = -1; pre[0] = fa[0] = f[0] = 1; cnt = last = 1; }

char s[maxn];
void expand(int x) {
	int p = last, c = s[x] - 'a';
	while (s[x - len[p] - 1] != s[x]) p = fa[p];
	if (!son[p][c]) {
	int np = last = ++cnt;
	len[np] = len[p] + 2;
	int z = fa[p];
	while (s[x - len[z] - 1] != s[x]) z = fa[z];
	fa[np] = son[z][c];
	son[p][c] = np;
	d[np] = len[np] - len[fa[np]];
	if (d[np] == d[fa[np]]) pre[np] = pre[fa[np]];
	else pre[np] = fa[np];
	}
	last = son[p][c];
	p = last;
	while (p > 1) {
		sf[p] = f[x - len[pre[p]] - d[p]];
		if (pre[p] != fa[p]) sf[p] = (sf[p] + sf[fa[p]]) % mod;
		if (x % 2 == 0)
			f[x] = (f[x] + sf[p]) % mod;
		p = pre[p];
	}
}

char str[maxn];
int main() {
	scanf("%s", str + 1);
	int n = strlen(str + 1);
	for (int i = 1; i <= n; ++i) {
		if (i & 1) s[i] = str[(i + 1) / 2];
		else s[i] = str[n - (i + 1) / 2 + 1];
	}
	s[0] = '#';
	init();
	for (int i = 1; i <= n; ++i) expand(i);
	printf("%d\n", f[n]);
	return 0;
}