#include <cstdio>
int const maxn = 100003 << 1;
struct Node {
	int len;
	int son[26], fa;
	int &operator[](int x) { return son[x]; }
};
Node tr[maxn];
int tag[maxn], cnt = 1;
int expand(int last, int c, int w) {
	int p = last, r = 0;
	if (tr[p][c]) {
		int q = tr[p][c];
		if (tr[q].len == tr[p].len + 1)
			r = q;
		else {
			int nq = ++cnt;
			tr[nq] = tr[q];
			tr[nq].len = tr[p].len + 1;
			tr[q].fa = nq;
			for (; p && tr[p][c] == q; p = tr[p].fa)
				tr[p][c] = nq;
			r = nq;
		}
	} else {
		int np = ++cnt;
		tr[np].len = tr[p].len + 1;
		for (; p && tr[p][c] == 0; p = tr[p].fa)
			tr[p][c] = np;
		if (p == 0)
			tr[np].fa = 1;
		else {
			int q = tr[p][c];
			if (tr[q].len == tr[p].len + 1)
				tr[np].fa = q;
			else {
				int nq = ++cnt;
				tr[nq] = tr[q];
				tr[nq].len = tr[p].len + 1;
				tr[np].fa = tr[q].fa = nq;
				for (; p && tr[p][c] == q; p = tr[p].fa)
					tr[p][c] = nq;
			}
		}
		r = np;
	}
	if (tag[r] == 0)
		tag[r] = w;
	else
		tag[r] = -1;
	return r;
}
int n = 0;
char str[maxn];
int a[maxn], c[maxn];
long long ans[maxn];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str);
		int last = 1;
		for (int j = 0; str[j]; ++j)
			last = expand(last, str[j] - 'a', i);
	}
	for (int i = 1; i <= cnt; ++i)
		++c[tr[i].len];
	for (int i = 1; i <= cnt; ++i)
		c[i] += c[i - 1];
	for (int i = 1; i <= cnt; ++i)
		a[c[tr[i].len]--] = i;
	for (int i = cnt; i >= 2; --i) {
		int x = a[i];
		if (!tag[tr[x].fa])
			tag[tr[x].fa] = tag[x];
		else if (tag[tr[x].fa] != tag[x])
			tag[tr[x].fa] = -1;
		if (tag[x] != -1) ans[tag[x]] += tr[x].len - tr[tr[x].fa].len;
	}
	for (int i = 1; i <= n; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}