// 在线
#include <cstdio>
#include <queue>
int const maxn = 1000003;
struct SAM {
	static const int maxP = maxn << 1;
	struct Node {
		int son[26];
		int fa, len;
		int &operator[](int x) { return son[x]; }
	};
	Node tr[maxP];
	int cnt = 1;
	int expand(int last, int c) {
		int p = last;
		if (tr[p][c]) {
			int q = tr[p][c];
			if (tr[q].len == tr[p].len + 1) return q;
			else {
				int nq = ++cnt;
				tr[nq] = tr[q];
				tr[nq].len = tr[p].len + 1;
				tr[q].fa = nq;
				for (; p && tr[p][c] == q; p = tr[p].fa) tr[p][c] = nq;
				return nq;
			}
		}
		int np = ++cnt;
		tr[np].len = tr[p].len + 1;
		for (; p && tr[p][c] == 0; p = tr[p].fa) tr[p][c] = np;
		if (p == 0) tr[np].fa = 1;
		else {
			int q = tr[p][c];
			if (tr[q].len == tr[p].len + 1) tr[np].fa = q;
			else {
				int nq = ++cnt;
				tr[nq] = tr[q];
				tr[nq].len = tr[p].len + 1;
				tr[q].fa = tr[np].fa = nq;
				for (; p && tr[p][c] == q; p = tr[p].fa) tr[p][c] = nq;
			}
		}
		return np;
	}
};
SAM sam;
char str[maxn];
int d[maxn];
int main() {
	int n = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str);
		int last = 1;
		for (int j = 0; str[j]; ++j)
			last = sam.expand(last, str[j] - 'a');
	}
	long long ans = 0;
	for (int i = 2; i <= sam.cnt; ++i)
		ans += sam.tr[i].len - sam.tr[sam.tr[i].fa].len;
	printf("%lld", ans);
	return 0;
}