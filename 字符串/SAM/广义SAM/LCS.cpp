#include <cstdio>
int const maxn = 250003;
struct Node {
	int len;
	int son[26], fa;
};
Node tr[maxn << 2];
int siz[2][maxn << 2];
int cnt = 1;
int expand(int last, int c, int W) {
	int p = last;
	if (tr[p].son[c]) {
		int q = tr[p].son[c];
		if (tr[q].len == tr[p].len + 1) {
			++siz[W][q];
			return q;
		} else {
			int nq = ++cnt;
			tr[nq] = tr[q];
			tr[nq].len = tr[p].len + 1;
			siz[W][nq] = 1;
			tr[q].fa = nq;
			for (; p && tr[p].son[c] == q; p = tr[p].fa)
				tr[p].son[c] = nq;
			return nq;
		}
	}
	int np = ++cnt;
	tr[np].len = tr[p].len + 1;
	siz[W][np] = 1;
	for (; p && tr[p].son[c] == 0; p = tr[p].fa)
		tr[p].son[c] = np;
	if (p == 0)
		tr[np].fa = 1;
	else {
		int q = tr[p].son[c];
		if (tr[q].len == tr[p].len + 1)
			tr[np].fa = q;
		else {
			int nq = ++cnt;
			tr[nq] = tr[q];
			tr[nq].len = tr[p].len + 1;
			tr[q].fa = tr[np].fa = nq;
			for (; p && tr[p].son[c] == q; p = tr[p].fa)
				tr[p].son[c] = nq;
		}
	}
	return np;
}

char str[maxn];
int c[maxn << 2], a[maxn << 2];
int main() {
	int last = 1;
	scanf("%s", str);
	for (int i = 0; str[i]; ++i)
		last = expand(last, str[i] - 'a', 0);
	last = 1;
	scanf("%s", str);
	for (int i = 0; str[i]; ++i)
		last = expand(last, str[i] - 'a', 1);
	for (int i = 1; i <= cnt; ++i)
		++c[tr[i].len];
	for (int i = 1; i <= cnt; ++i)
		c[i] += c[i - 1];
	for (int i = 1; i <= cnt; ++i)
		a[c[tr[i].len]--] = i;
	for (int i = cnt; i >= 1; --i) {
		siz[0][tr[i].fa] += siz[0][i];
		siz[1][tr[i].fa] += siz[1][i];
	}
	int ans = 0;
	for (int i = 1; i <= cnt; ++i)
		if (siz[0][i] && siz[1][i] && tr[i].len > ans) ans = tr[i].len;
	printf("%d\n", ans);
	return 0;
}