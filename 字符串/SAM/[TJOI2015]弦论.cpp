#include <cstdio>
int const maxn = 500005;
int t = 0, k = 0;
char str[maxn];
struct Node {
	int son[26];
	int fa;
	int len;
};
Node tr[maxn << 1];
int cnt = 1, last = 1;
int a[maxn << 1], c[maxn << 1];
long long siz[maxn << 1], sum[maxn << 1];
void add(int c) {
	c -= 'a';
	int p = last, np = ++cnt;
	tr[np].len = tr[p].len + 1;
	siz[np] = 1;
	last = np;
	for (; p && tr[p].son[c] == 0; p = tr[p].fa)
		tr[p].son[c] = np;
	if (p == 0)
		tr[np].fa = 1;
	else {
		int q = tr[p].son[c];
		if (tr[p].len + 1 == tr[q].len)
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
}

void pre() {
	for (int i = 1; i <= cnt; ++i)
		++c[tr[i].len];
	for (int i = 1; i <= cnt; ++i)
		c[i] += c[i - 1];
	for (int i = 1; i <= cnt; ++i)
		a[c[tr[i].len]--] = i;
	if (t == 1)
		for (int i = cnt; i >= 1; --i)
			siz[tr[a[i]].fa] += siz[a[i]];
	else
		for (int i = 1; i <= cnt; ++i)
			siz[i] = 1;
	siz[1] = 0;
	for (int i = cnt; i >= 1; --i) {
		int x = a[i];
		sum[x] = siz[x];
		for (int j = 0; j < 26; ++j)
			if (tr[x].son[j])
				sum[x] += sum[tr[x].son[j]];
	}
}
void solve() {
	if (k > sum[1]) {
		printf("-1");
		return;
	}
	int p = 1;
	while (k > 0) {
		int j = 0;
		while (k > sum[tr[p].son[j]]) {
			k -= sum[tr[p].son[j]];
			++j;
		}
		p = tr[p].son[j];
		k -= siz[p];
		putchar('a' + j);
	}
}
int main() {
	scanf("%s\n%d %d", str, &t, &k);
	for (int i = 0; str[i]; ++i)
		add(str[i]);
	pre();
	solve();
	return 0;
}