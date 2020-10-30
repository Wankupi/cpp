#include <cstdio>
#include <cstring>
int const N = 200003;
int n = 0;
struct Node {
	int len;
	int fa, son[26];
	int& operator[](int x) { return son[x]; }
};
Node tr[N]; int cntSAM = 1;
int root[N];
int expand(int last, int cc) {
	int p = last, np = ++cntSAM;
	tr[np].len = tr[p].len + 1;
	for (; p && tr[p][cc] == 0; p = tr[p].fa) tr[p][cc] = np;
	if (p == 0) tr[np].fa = 1;
	else {
		int q = tr[p][cc];
		if (tr[q].len == tr[p].len + 1) tr[np].fa = q;
		else {
			int nq = ++cntSAM;
			tr[nq] = tr[q];
			tr[nq].len = tr[p].len + 1;
			tr[q].fa = tr[np].fa = nq;
			for (; p && tr[p][cc] == q; p = tr[p].fa) tr[p][cc] = nq;
		}
	}
	return np;
}

struct SegNode {
	int ls, rs, sum;
};
SegNode T[N * 19]; int cntSeg = 0;
void add(int &p, int L, int R, int x) {
	if (p == 0) p = ++cntSeg;
	if (L == R) { ++T[p].sum; return; }
	int mid = (L + R) >> 1;
	if (x <= mid) add(T[p].ls, L, mid, x);
	else add(T[p].rs, mid + 1, R, x);
	T[p].sum = T[T[p].ls].sum + T[T[p].rs].sum;
}
int merge(int x, int y, int L, int R) {
	if (x == 0 || y == 0) return x | y;
	int p = ++cntSeg;
	if (L == R) {
		T[p].sum = T[x].sum + T[y].sum;
		return p;
	}
	int mid = (L + R) >> 1;
	T[p].ls = merge(T[x].ls, T[y].ls, L, mid);
	T[p].rs = merge(T[x].rs, T[y].rs, mid + 1, R);
	T[p].sum = T[T[p].ls].sum + T[T[p].rs].sum;
	return p;
}
int query(int p, int L, int R, int l, int r) {
	if (p == 0 || l > r) return 0;
	if (l <= L && R <= r) return T[p].sum;
	int mid = (L + R) >> 1;
	if (r <= mid) return query(T[p].ls, L, mid, l, r);
	if (l > mid) return query(T[p].rs, mid + 1, R, l, r);
	return query(T[p].ls, L, mid, l, r) + query(T[p].rs, mid + 1, R, l, r);
}
int t[N], cc[N];
char str[N];

int ql = 0, qr = 0, qLen = 0;
bool dfs(int p, int i) {
	if (i == qLen + 1) {
		for (int j = 0; j < 26; ++j)
			if (tr[p][j] && query(root[tr[p][j]], 1, n, ql + i - 1, qr) > 0) {
				str[i] = char('a' + j);
				str[i + 1] = 0;
				return true;
			}
		return false;
	}
	int cc = str[i] - 'a';
	if (tr[p][cc] && query(root[tr[p][cc]], 1, n, ql + i - 1, qr) > 0 && dfs(tr[p][cc], i + 1)) return true;
	for (int j = cc + 1; j < 26; ++j)
		if (tr[p][j] && query(root[tr[p][j]], 1, n, ql + i - 1, qr) > 0) {
			str[i] = char('a' + j);
			str[i + 1] = 0;
			return true;
		}
	return false;
}

int main() {
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for (int last = 1, i = 1; i <= n; ++i) {
		last = expand(last, str[i] - 'a');
		add(root[last], 1, n, i);
	}
	for (int i = 1; i <= cntSAM; ++i) ++cc[tr[i].len];
	for (int i = 1; i <= n; ++i) cc[i] += cc[i - 1];
	for (int i = 1; i <= cntSAM; ++i) t[cc[tr[i].len]--] = i;
	for (int i = cntSAM; i >= 1; --i) {
		int x = t[i];
		if (tr[x].fa) root[tr[x].fa] = merge(root[tr[x].fa], root[x], 1, n);
	}

	int m = 0;
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %s", &ql, &qr, str + 1);
		qLen = strlen(str + 1);
		if (dfs(1, 1))
			printf("%s\n", str + 1);
		else printf("-1\n");
	}
	return 0;
}