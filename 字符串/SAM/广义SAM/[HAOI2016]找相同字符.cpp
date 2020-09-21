#include <cstdio>
int const maxn = 200003;
struct Node {
	int son[26], fa;
	int len;
	int &operator[](int x) { return son[x]; }
};
Node tr[maxn << 3];
int siz[2][maxn << 3], cnt = 1;
int expand(int p, int c, int which) { // p is last
	if (tr[p][c]) {
		int q = tr[p][c];
		if (tr[q].len == tr[p].len + 1) {
			siz[which][q] = 1;
			return q;
		}
		else {
			int nq = ++cnt;
			tr[nq] = tr[q];
			tr[nq].len = tr[p].len + 1;
			siz[which][nq] = 1;
			tr[q].fa = nq;
			for (; p && tr[p][c] == q; p = tr[p].fa)
				tr[p][c] = nq;
			return nq;
		}
	}
	int np = ++cnt;
	siz[which][np] = 1;
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
			tr[q].fa = tr[np].fa = nq;
			for (; p && tr[p][c] == q; p = tr[p].fa)
				tr[p][c] = nq;
		}
	}
	return np;
}
char str[maxn];
int t[maxn << 3], a[maxn << 3];
int main() {
	scanf("%s", str);
	int last = 1;
	for (int i = 0; str[i]; ++i)
		last = expand(last, str[i] - 'a', 0);
	scanf("%s", str);
	last = 1;
	for (int i = 0; str[i]; ++i)
		last = expand(last, str[i] - 'a', 1);
	for (int i = 1; i <= cnt; ++i)
		++t[tr[i].len];
	for (int i = 1; i <= cnt; ++i)
		t[i] += t[i - 1];
	for (int i = 1; i <= cnt; ++i)
		a[t[tr[i].len]--] = i;
	for (int i = cnt; i >= 1; --i) {
		int f = tr[a[i]].fa;
		siz[0][f] += siz[0][a[i]];
		siz[1][f] += siz[1][a[i]];
	}
	long long ans = 0;
	for (int i = 1; i <= cnt; ++i) {
		ans += (long long)siz[0][i] * siz[1][i] * (tr[i].len - tr[tr[i].fa].len);
	}
	printf("%lld", ans);
	return 0;
}