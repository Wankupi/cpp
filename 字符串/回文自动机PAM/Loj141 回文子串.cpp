#include <cstdio>
int const maxn = 100003, N = 400003;

long long ans = 0;

unsigned char s[N << 1];
int l = 0, r = 0;
int fa[N], len[N], son[N][27], dep[N], cnt = 1;
int lastL = 0, lastR = 0;
void init() { fa[0] = 1; len[1] = -1; cnt = 1; l = 400002; r = l - 1; }

void pushR(unsigned char c) {
	s[++r] = c;
	int p = lastR;
	while (s[r - len[p] - 1] != s[r]) p = fa[p];
	if (!son[p][c]) {
		int np = ++cnt;
		len[np] = len[p] + 2;
		int k = fa[p];
		while (s[r - len[k] - 1] != s[r]) k = fa[k];
		fa[np] = son[k][c]; dep[np] = dep[son[k][c]] + 1;
		son[p][c] = np;
	}
	lastR = son[p][c];
	if (len[lastR] == r - l + 1) lastL = lastR;
	ans += dep[lastR];

}
void pushL(unsigned char c) {
	s[--l] = c;
	int p = lastL;
	while (s[l + len[p] + 1] != s[l]) p = fa[p];
	if (!son[p][c]) {
		int np = ++cnt;
		len[np] = len[p] + 2;
		int k = fa[p];
		while (s[l + len[k] + 1] != s[l]) k = fa[k];
		fa[np] = son[k][c]; dep[np] = dep[son[k][c]] + 1;
		son[p][c] = np;
	}
	lastL = son[p][c];
	if (len[lastL] == r - l + 1) lastR = lastL;
	ans += dep[lastL];
}


char tmp[maxn];
int main() {
	init();
	scanf("%s", tmp);
	for (int i = 0; tmp[i]; ++i) pushR(tmp[i] - 'a' + 1);
	int m = 0;
	scanf("%d", &m);
	while (m--) {
		int opt = 0;
		scanf("%d", &opt);
		if (opt == 1) { scanf("%s", tmp); for (int i = 0; tmp[i]; ++i) pushR(tmp[i] - 'a' + 1); }
		else if (opt == 2) { scanf("%s", tmp); for (int i = 0; tmp[i]; ++i) pushL(tmp[i] - 'a' + 1); }
		else {
			printf("%lld\n", ans);
		}
	}
	return 0;
}