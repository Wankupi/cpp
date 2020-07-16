#include <cstdio>
struct Node {
	int len, fa;
	int son[26];
};
Node tr[2000050];
int last = 1, cnt = 1;
int num[2000050];
void add(int c) {
	int p = last, np = last = ++cnt;
	tr[np].len = tr[p].len + 1;
	num[np] = 1;
	while (p && !tr[p].son[c]) {
		tr[p].son[c] = np;
		p = tr[p].fa;
	}
	if (!p)
		tr[np].fa = 1;
	else {
		int q = tr[p].son[c];
		if (tr[q].len == tr[p].len + 1) {
			tr[np].fa = q;
		}
		else {
			int nq = ++cnt;
			tr[nq] = tr[q];
			tr[nq].len = tr[p].len + 1;
			tr[q].fa = tr[np].fa = nq;
			while (p && tr[p].son[c] == q) {
				tr[p].son[c] = nq;
				p = tr[p].fa;
			}
		}
	}
}
char str[1000005];
inline long long max(long long a, long long b) { return a < b ? b : a; }
int d[2000050], dl[2000050], l = 1, r = 0;
int main() {
	scanf("%s", str);
	for (int i = 0; str[i] != 0; ++i)
		add(str[i] - 'a');
//	long long ans = 0;
	for (int i = 1; i <= cnt; ++i) ++d[tr[i].fa];
	for (int i = 1; i <= cnt; ++i) if (d[i] == 0) dl[++r] = i;
	while (l <= r) {
		int x = dl[l++];
//		if (num[x] > 1) ans = max(ans, num[x] * tr[x].len);
		num[tr[x].fa] += num[x];
		if (--d[tr[x].fa] == 0) dl[++r] = tr[x].fa;
	}
	printf("%lld", num[1]);
	return 0;
}