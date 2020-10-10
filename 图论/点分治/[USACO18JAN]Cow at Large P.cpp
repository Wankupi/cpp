#include <cstdio>
#include <algorithm>
using namespace std;
int const maxn = 70003, inf = 0x3f3f3f3f;
int n = 0;
int deg[maxn]; // degree
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int g[maxn]; // the min dis to leaf
int t[maxn]; // temp array
void calc_G() {
	int l = 1, r = 0;
	for (int i = 1; i <= n; ++i) if (deg[i] == 1) t[++r] = i;
	while (l <= r) {
		int x = t[l++];
		for (int i = head[x]; i; i = nxt[i])
			if (g[to[i]] == 0 && deg[to[i]] != 1) { g[to[i]] = g[x] + 1; t[++r] = to[i]; }
	}
}
bool ban[maxn];
int siz[maxn], dis[maxn];
int SizeAll = 0, rt = 0, RtSiz = inf;
void find_root(int x, int f) {
	siz[x] = 1;
	int mxSubtrSiz = 0;
	for (int i = head[x]; i; i = nxt[i])
		if (!ban[to[i]] && to[i] != f) {
			find_root(to[i], x);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > mxSubtrSiz) mxSubtrSiz = siz[to[i]];
		}
	if (SizeAll - siz[x] > mxSubtrSiz) mxSubtrSiz = SizeAll - siz[x];
	if (mxSubtrSiz < RtSiz) { rt = x; RtSiz = mxSubtrSiz; }
}

void getDis(int x, int f) {
	for (int i = head[x]; i; i = nxt[i])
		if (!ban[to[i]] && to[i] != f) {
			dis[to[i]] = dis[x] + 1;
			getDis(to[i], x);
		}
}

bool cmpByDis(int x, int y) { return dis[x] < dis[y]; }
struct GD { GD() {} GD(int SortKey_G_D, int Value) : key(SortKey_G_D), val(Value) {} int key, val; };
inline bool operator<(GD const &lhs, GD const &rhs) { return lhs.key < rhs.key; }
GD q[maxn];
int cntD = 0;
void addForCalc(int x, int f) {
	t[++cntD] = x;
	q[cntD] = GD(g[x] - dis[x], 2 - deg[x]);
	for (int i = head[x]; i; i = nxt[i]) if (!ban[to[i]] && to[i] != f) addForCalc(to[i], x);
}

int ans[maxn];

void Calc(int x, int f, int op) {
	cntD = 0;
	addForCalc(x, f);
	sort(t + 1, t + cntD + 1, cmpByDis); // distance down order
	sort(q + 1, q + cntD + 1);
	int sum = 0;
	for (int i = 1, j = 1; i <= cntD; ++i) {
		while (j <= cntD && dis[t[i]] >= q[j].key) sum += q[j++].val;
		ans[t[i]] += op * sum;
	}
}

void solve(int x) {
	ban[x] = true;
	dis[x] = 0;
	getDis(x, 0);
	Calc(x, 0, +1);
	for (int i = head[x]; i; i = nxt[i])
		if (!ban[to[i]]) {
			Calc(to[i], x, -1);
			SizeAll = siz[to[i]], rt = 0, RtSiz = inf;
			find_root(to[i], x);
			solve(rt);
		}
}

int main() {
	scanf("%d", &n);
	int x = 0, y = 0;
	for (int i = 1;  i < n; ++i) {
		scanf("%d %d", &x, &y);
		insert(x, y); insert(y, x);
		++deg[x]; ++deg[y];
	}
	calc_G();
	SizeAll = n; rt = 0, RtSiz = inf;
	find_root(1, 0);
	solve(rt);
	for (int i = 1; i <= n; ++i) printf("%d\n", deg[i] == 1 ? 1 : ans[i]);
	return 0;
}