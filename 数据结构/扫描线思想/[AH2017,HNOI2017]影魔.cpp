#include <algorithm>
#include <cstdio>
#include <cctype>
void read(int &x) {
	int c = getchar(); bool f = false; x = 0;
	while (!isdigit(c)) { if (c == '-') f = true; c = getchar(); }
	while (isdigit(c)) { x = (x << 1) + (x << 3) + c - '0'; c = getchar(); }
	if (f) x = -x;
}
const int N = 200003;
typedef long long ll;
int n = 0, m = 0, p1 = 0, p2 = 0;
inline int lowbit(int x) { return x & -x; }
class TreeArrey {
public:
	void add(int p, ll x) { while (p <= N) { tree[p] += x; p += lowbit(p); } }
	ll query(int p) { ll ret = 0; while (p) { ret += tree[p]; p -= lowbit(p); } return ret; }
	ll query(int l, int r) { return query(r) - query(l - 1); }
	ll tree[N + 1];
};
TreeArrey b, bi;
inline void add(int l, int r, ll x) {
	b.add(l, x);		b.add(r + 1, -x);
	bi.add(l, x * l);	bi.add(r + 1, -x * (r + 1ll));
}
inline ll query(int p) { return (p + 1ll) * b.query(p) - bi.query(p); }
inline ll query(int l, int r) { return query(r) - query(l - 1); }

int a[N];
int st[N], top = 0, cL[N], cR[N];
struct Query { int l, r, key, id; };
inline bool operator<(const Query &lhs, const Query &rhs) { return lhs.key < rhs.key; }
Query que[N << 1];
struct Oper {
	Oper() {}
	Oper(int L, int R, int Val, int Key) : l(L), r(R), v(Val), key(Key) {}
	int l, r, v, key;
};
inline bool operator<(const Oper &lhs, const Oper &rhs) { return lhs.key < rhs.key; }
Oper opts[N << 2];
int cntOpt = 0;

long long ans[N];
int main() {
	read(n); read(m); read(p1); read(p2);
	for (int i = 1; i <= n; ++i) read(a[i]);
	for (int i = 1; i <= m; ++i) {
		read(que[i].l); read(que[i].r); que[i].id = i;
		que[i + m] = que[i];
		que[i].key = que[i].l - 1;
		que[i + m].key = que[i].r;
		ans[i] = (long long)(que[i].r - que[i].l) * p1;
	}
	for (int i = 1; i <= n; ++i) {
		while (top > 0 && a[st[top]] < a[i]) cR[st[top--]] = i;
		cL[i] = st[top];
		st[++top] = i;
	}
	while (top) cR[st[top--]] = n + 1;
	for (int i = 1; i <= n; ++i) {
		if (cL[i] >= 1 && cR[i] <= n) opts[++cntOpt] = Oper(cL[i], cL[i], p1, cR[i]);
		if (cR[i] <= n && cL[i] + 1 <= i - 1) opts[++cntOpt] = Oper(cL[i] + 1, i - 1, p2, cR[i]);
		if (cL[i] >= 1 && i + 1 <= cR[i] - 1) opts[++cntOpt] = Oper(i + 1, cR[i] - 1, p2, cL[i]);
	}
	std::sort(que + 1, que + 2 * m + 1);
	std::sort(opts + 1, opts + cntOpt + 1);
	for (int i = 1, cur = 1; i <= 2 * m; ++i) {
		while (cur <= cntOpt && opts[cur].key <= que[i].key) {
			if (opts[cur].l >= 1 && opts[cur].r >= opts[cur].l)
				add(opts[cur].l, opts[cur].r, opts[cur].v);
			++cur;
		}
		ans[que[i].id] += (que[i].key == que[i].r ? +1 : -1) * query(que[i].l, que[i].r);
	}

	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}