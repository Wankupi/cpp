#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;
int const maxn = 100003;

inline int read() {
	int x = 0, c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) { x = 10 * x + c - '0'; c = getchar(); }
	return x;
}

int n = 0, m = 0;
int day = 0;

namespace trie {
	struct Node {
		int son[2];
		int siz;
	};
	Node tr[maxn * 120];
	int cnt = 0;
	void insert(int &rt, int x) {
		tr[++cnt] = tr[rt];
		int p = rt = cnt;
		for (int j = 17; ~j; --j) {
			int c = (x >> j) & 1;
			tr[++cnt] = tr[tr[p].son[c]];
			tr[p].son[c] = cnt;
			p = tr[p].son[c];
			++tr[p].siz;
		}
	}
	int query(int p1, int p2, int x) {
		int Ans = 0;
		for (int j = 17; ~j; --j) {
			int c = ((x >> j) & 1) ^ 1;
			if (tr[tr[p2].son[c]].siz - tr[tr[p1].son[c]].siz > 0) {
				p1 = tr[p1].son[c]; p2 = tr[p2].son[c];
				Ans |= (1 << j);
			}
			else {
				p1 = tr[p1].son[c ^ 1]; p2 = tr[p2].son[c ^ 1];
			}
		}
		return Ans;
	}
}


struct Query {
	int l, r, x, id;
};
vector<Query> qs[maxn << 2];
int ans[maxn], qId = 0;

struct Goods { int id, time, v; };
Goods a[maxn], t1[maxn], t2[maxn];

void addQuery(int p, int L, int R, int l, int r, Query const &q) {
	if (l > r) return;
	if (l <= L && R <= r) { qs[p].push_back(q); return; }
	int mid = (L + R) >> 1;
	if (l <= mid) addQuery(p << 1, L, mid, l, r, q);
	if (r > mid) addQuery(p << 1 | 1, mid + 1, R, l, r, q);
}

int rt[maxn];
int pos[maxn];

void calc(int l, int r, vector<Query> &v) {
	if (!v.size()) return;
	trie::cnt = 0;
	int top = 0;
	for (int i = l; i <= r; ++i) {
		if (pos[top] != a[i].id) {
			++top;
			rt[top] = rt[top - 1];
			pos[top] = a[i].id;
		}
		trie::insert(rt[top], a[i].v);
	}
	for (Query const &q : v) {
		int L = upper_bound(pos + 1, pos + top + 1, q.l - 1) - pos - 1,
			R = upper_bound(pos + 1, pos + top + 1, q.r) - pos - 1;
		if (L >= R) continue;
		ans[q.id] = max(ans[q.id], trie::query(rt[L], rt[R], q.x));
	}
}

void solve(int p, int L, int R, int l, int r) {
	if (l > r) return;
	calc(l, r, qs[p]);
	if (L == R) return;
	int cL = 0, cR = 0;
	int mid = (L + R) >> 1;
	for (int i = l; i <= r; ++i)
		if (a[i].time <= mid)
			t1[++cL] = a[i];
		else
			t2[++cR] = a[i];
	for (int i = 1; i <= cL; ++i) a[l + i - 1] = t1[i];
	for (int i = 1; i <= cR; ++i) a[l + cL + i - 1] = t2[i];
	solve(p << 1, L, mid, l, l + cL - 1);
	solve(p << 1 | 1, mid + 1, R, l + cL, r);
}

int main() {
	n = read(); m = read();
	for (int i = 1; i <= n; ++i) {
		rt[i] = rt[i - 1];
		trie::insert(rt[i], read());
	}
	for (int i = 1; i <= m; ++i) {
		int opt = read();
		if (opt == 0) {
			int s = read(), v = read();
			++day;
			a[day] = Goods{ s, day, v };
		}
		else {
			int l = read(), r = read(), x = read(), d = read();
			Query q = Query{ l, r, x, ++qId };
			ans[qId] = trie::query(rt[l - 1], rt[r], x);
			addQuery(1, 1, m, max(1, day - d + 1), day, q);
		}
	}
	sort(a + 1, a + day + 1, [](Goods const& A, Goods const &B) { return A.id < B.id; });
	solve(1, 1, m, 1, day);
	for (int i = 1; i <= qId; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}