#include <cstdio>
int const inf = 0x3f3f3f3f;
struct Node {
	int len, f;
	int fail, half;
	int son[4];
};
Node tr[100003];
int cnt = -1;
int NewNode(int Len) {
	int p = ++cnt;
	tr[p].len = Len; tr[p].f = inf, tr[p].fail = 0;
	for (int i = 0; i < 4; ++i) tr[p].son[i] = 0;
	return p;
}
int last = 1;
void init() {
	cnt = -1;
	NewNode(0); NewNode(-1);
	tr[0].fail = tr[1].fail = 1;
	tr[0].half = tr[1].half = 0;
	tr[0].f = 1;  tr[1].f = 0;
	last = 1;
}
char str[100003];
int find(int p, int x) { 
	while (str[x] != str[x - tr[p].len - 1]) p = tr[p].fail;
	return p;
}
inline int map(char c) { return c == 'A' ? 0 : (c == 'T' ? 1 : (c == 'C' ? 2 : 3)); }
inline int min(int a, int b) { return a < b ? a : b; }
void expand(int i) {
	int c = map(str[i]);
	int p = find(last, i);
	if (tr[p].son[c] == 0) {
		int np = NewNode(tr[p].len + 2);
		tr[np].fail = tr[find(tr[p].fail, i)].son[c];
		tr[p].son[c] = np;
		if (tr[np].len > 2) {
			int q = tr[p].half;
			while (str[i] != str[i - tr[q].len - 1] || (tr[q].len + 2) > tr[np].len / 2) q = tr[q].fail;
			tr[np].half = tr[q].son[c];
		}
		else tr[np].half = tr[np].fail;
		tr[np].f = tr[np].len;
		if (tr[np].len % 2 == 0) {
			tr[np].f = min(tr[np].f, tr[p].f + 1);
			tr[np].f = min(tr[np].f, tr[tr[np].half].f + tr[np].len / 2 - tr[tr[np].half].len + 1);
		}
	}
	last = tr[p].son[c];
}
int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		init();
		scanf("%s", str + 1);
		int n = 0;
		for (int i = 1; str[i]; ++i) expand(i), n = i;
		int ans = n;
		for (int i = 0; i <= cnt; ++i)
			ans = min(ans, n - tr[i].len + tr[i].f);
		printf("%d\n", ans);
	}
	return 0;
}