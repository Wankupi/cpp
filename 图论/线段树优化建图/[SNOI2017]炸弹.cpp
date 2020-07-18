// 区间 到 点 连边
// PC : RE 爆栈
// luogu without O2 : TLE
// Loj : AC
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const int maxn = 500003, maxP = maxn << 2, maxL = maxn << 4;
const ll mod = 1000000007;
ll read() {
	ll x = 0;
	int c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int n = 0;
ll x[maxn], r[maxn];
int head[maxP], nxt[maxL], to[maxL], cnt = 0; // cnt ： 边计数器
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int UpTreeRoot = 0;
int lc[maxP], rc[maxP], c = 0; // c : 点计数器 must be set n before create Tree
void buildUpTree(int &p, int L, int R) {
	if (L == R) { p = L; return; }
	if (p == 0) p = ++c;
	int mid = (L + R) >> 1;
	buildUpTree(lc[p], L, mid);
	buildUpTree(rc[p], mid + 1, R);
	insert(lc[p], p);
	insert(rc[p], p);
}
void AddSqToPo(int p, int L, int R, int l, int r, int To) {
	if (l <= L && R <= r) {
		insert(p, To);
		return;
	}
	int mid = (L + R) >> 1;
	if (l <= mid) AddSqToPo(lc[p], L, mid, l, r, To);
	if (r > mid) AddSqToPo(rc[p], mid + 1, R, l, r, To);
}
int dfn[maxP], low[maxP], cdfn = 0, st[maxP], up = 0;
bool inSt[maxP];
int id[maxP], L[maxP], R[maxP], scc = 0;
void tarjan(int x) {
	dfn[x] = low[x] = ++cdfn;
	st[++up] = x;
	inSt[x] = true;
	for (int i = head[x]; i; i = nxt[i]) {
		if (!dfn[to[i]]) {
			tarjan(to[i]);
			low[x] = min(low[x], low[to[i]]);
		}
		else if (inSt[to[i]])
			low[x] = min(low[x], dfn[to[i]]);
	}
	if (dfn[x] == low[x]) {
		int y = 0;
		++scc;
		R[scc] = 0;
		L[scc] = n + 1;
		do {
			y = st[up--];
			inSt[y] = false;
			id[y] = scc;
			if (y <= n) {
				R[scc] = max(R[scc], y);
				L[scc] = min(L[scc], y);
			}
		} while (y != x);
	}
}
int head2[maxP], nxt2[maxL], to2[maxL], cnt2 = 0;
inline void insert2(int u, int e) { nxt2[++cnt2] = head2[u]; head2[u] = cnt2; to2[cnt2] = e; }
int d[maxP];
void topu() {
	for (int x = 1; x <= c; ++x) {
		for (int i = head[x]; i; i = nxt[i])
			if (id[to[i]] != id[x]) {
				++d[id[to[i]]];
				insert2(id[x], id[to[i]]);
			}
	}
	queue<int> q;
	for (int x = 1; x <= scc; ++x)
		if (d[x] == 0) q.push(x);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = head2[x]; i; i = nxt2[i]) {
			int y = to2[i];
			R[y] = max(R[y], R[x]);
			L[y] = min(L[y], L[x]);
			if (--d[y] == 0) q.push(y);
		}
	}
}
int main() {
	c = n = int(read());
	for (int i = 1; i <= n; ++i) {
		x[i] = read(); r[i] = read();
	}
	buildUpTree(UpTreeRoot, 1, n);
	for (int i = 1; i <= n; ++i) {
		int L = lower_bound(x + 1, x + n + 1, x[i] - r[i]) - x;
		int R = upper_bound(x + 1, x + n + 1, x[i] + r[i]) - x - 1;
		AddSqToPo(UpTreeRoot, 1, n, L, R, i);
	}
	for (int i = c; i >= 1; --i)
		if (!dfn[i]) {
			tarjan(i);
		}
	topu();
	ll sum = 0;
	for (int i = 1; i <= n; ++i)
		(sum += i * (R[id[i]] * 1ll - L[id[i]] + 1) % mod) %= mod;
	printf("%lld", sum);
	return 0;
}