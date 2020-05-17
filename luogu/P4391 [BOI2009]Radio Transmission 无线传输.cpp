#include <cstdio>
int n = 0;
char s[1000007];
int nxt[1000007];
int main() {
	scanf("%d%s", &n, s + 1);
	nxt[1] = 0;
	for (int i = 2; i <= n; ++i) {
		nxt[i] = nxt[i - 1];
		while (nxt[i] > 0 && s[i] != s[nxt[i] + 1])
			nxt[i] = nxt[nxt[i]];
		if (s[i] == s[nxt[i] + 1]) ++nxt[i];
	}
	printf("%d", n - nxt[n]);
	return 0;
}