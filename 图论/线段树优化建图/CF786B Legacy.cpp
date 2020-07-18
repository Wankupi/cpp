#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;
const int maxn = 100003;
int read() {
	int x = 0, c = getchar(), f = 1;
	while (c < '0' || c>'9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int n = 0, q = 0, s = 0;
int head[maxn << 5], nxt[maxn << 5], to[maxn << 5], val[maxn << 5], cnt = 0;
inline void insert(int u, int e, int v) {
	nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v;
}
int UpTreeRoot = 0, DownTreeRoot = 0;
int lc[maxn << 5], rc[maxn << 5], c = 0;
void buildUpTree(int &p, int L, int R) {
	if (L == R) { p = L; return; }
	if (p == 0) p = ++c;
	int mid = (L + R) >> 1;
	buildUpTree(lc[p], L, mid);
	buildUpTree(rc[p], mid + 1, R);
	insert(lc[p], p, 0);
	insert(rc[p], p, 0);
}
void buildDownTree(int &p, int L, int R) {
	if (L == R) { p = L; return; }
	if (p == 0) p = ++c;
	int mid = (L + R) >> 1;
	buildDownTree(lc[p], L, mid);
	buildDownTree(rc[p], mid + 1, R);
	insert(p, lc[p], 0);
	insert(p, rc[p], 0);
}
void AddPoToSq(int p, int L, int R, int l, int r, int fr, int w) {
	if (l <= L && R <= r) {
		insert(fr, p, w);
		return;
	}
	int mid = (L + R) >> 1;
	if (l <= mid) AddPoToSq(lc[p], L, mid, l, r, fr, w);
	if (r > mid) AddPoToSq(rc[p], mid + 1, R, l, r, fr, w);
}
void AddSqToPo(int p, int L, int R, int l, int r, int fr, int w) {
	if (l <= L && R <= r) {
		insert(p, fr, w);
		return;
	}
	int mid = (L + R) >> 1;
	if (l <= mid) AddSqToPo(lc[p], L, mid, l, r, fr, w);
	if (r > mid) AddSqToPo(rc[p], mid + 1, R, l, r, fr, w);
}
ll dis[maxn << 5];
bool in[maxn << 5];
void spfa() {
	memset(dis, 0x3f, sizeof dis);
	dis[s] = 0;
	queue<int> q;
	q.push(s); in[s] = true;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		in[x] = false;
		for (int i = head[x]; i; i = nxt[i])
			if (dis[to[i]] > dis[x] + val[i]) {
				dis[to[i]] = dis[x] + val[i];
				if (!in[to[i]]) {
					q.push(to[i]);
					in[to[i]] = true;
				}
			}
	}
}
int main() {
	n = read(); q = read(); s = read();
	c = n;
	buildUpTree(UpTreeRoot, 1, n);
	buildDownTree(DownTreeRoot, 1, n);
	int opt = 0, v = 0, u = 0, w = 0, l = 0, r = 0;
	for (int i = 1; i <= q; ++i) {
		opt = read();
		if (opt == 1) {
			v = read(); u = read(); w = read();
			insert(v, u, w);
		}
		else if (opt == 2) {
			v = read(); l = read(); r = read(); w = read();
			AddPoToSq(DownTreeRoot, 1, n, l, r, v, w);
		}
		else {
			v = read(); l = read(); r = read(); w = read();
			AddSqToPo(UpTreeRoot, 1, n, l, r, v, w);
		}
	}
	spfa();
	for (int i = 1; i <= n; ++i) printf("%lld ", dis[i] == 0x3f3f3f3f3f3f3f3f ? -1 : dis[i]);
	return 0;
}