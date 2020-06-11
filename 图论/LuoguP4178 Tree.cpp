// 点分治
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 40003, inf = 0x7fffffff;
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }

int n = 0, k = 0;
int ans = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 1;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }

bool vis[maxn];
int rt = 0, msrt = 0, S = 0;//msrt : max size of root's subtree
int dis[maxn], siz[maxn];

void getRoot(int x, int f) {
	siz[x] = 1;
	int mxSsiz = 0;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f && !vis[to[i]]) {
			getRoot(to[i], x);
			siz[x] += siz[to[i]];
			mxSsiz = max(mxSsiz, siz[to[i]]);
		}
	mxSsiz = max(mxSsiz, S - siz[x]);
	if (mxSsiz < msrt) {
		rt = x;
		msrt = mxSsiz;
	}
}
int tmp[maxn], cc = 0;
void getDis(int x, int f) {
	tmp[++cc] = dis[x];
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f && !vis[to[i]]) {
			dis[to[i]] = dis[x] + val[i];
			getDis(to[i], x);
		}
}

int solve(int x, int val) {
	dis[x] = val;
	cc = 0;
	getDis(x, x);
	sort(tmp + 1, tmp + cc + 1);
	int l = 1, r = cc, ret = 0;
	while (l < r) {
		if (tmp[l] + tmp[r] <= k) {
			ret += r - l; // 不加1 因为不能自己和自己配对，只能和 [l+1,r] 配对
			++l;
		}
		else --r;
	}
	return ret;
}

void Divid(int x) {
	vis[x] = true;
	ans += solve(x, 0);
	for (int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]) {
			ans -= solve(to[i], val[i]);
		}
	getRoot(x, 0);
	for (int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]) {
			S = siz[to[i]];
			msrt = inf;
			rt = 0;
			getRoot(to[i], x);
			Divid(to[i]);
		}
}
int main() {
	scanf("%d", &n);
	int a = 0, b = 0, c = 0;
	for (int i = 1; i != n; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		insert(a, b, c); insert(b, a, c);
	}
	scanf("%d", &k);
	msrt = inf;
	S = n;
	getRoot(1, 0);
	Divid(rt);
	printf("%d", ans);
	return 0;
}