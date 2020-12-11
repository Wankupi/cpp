int n;
char s[100000];
int nxt[100000];
void kmp() {
	nxt[1] = 0;
	for (int i = 2; i <= n; ++i) {
		nxt[i] = nxt[i - 1];
		while (nxt[i] && s[i] != s[nxt[i] + 1]) nxt[i] = nxt[nxt[i]];
		if (s[i] == s[nxt[i] + 1]) ++nxt[i];
	}
}