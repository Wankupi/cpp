#include <cstdio>
#include <cstring>

int const maxP = 20000000;
int n = 0, m = 0, A = 0, B = 0;
int head[71], nxt[407], to[407], val[407], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }

int vis[71], cId = 0;
int stack[71], top = 0;
void dfs1(int x) {
	vis[x] = 100;
	stack[++top] = x;
	for (int i = head[x]; i; i = nxt[i])
		if (val[i] == A && vis[to[i]] == 0) 
			dfs1(to[i]);
}
void dfs2(int x, int t) {
	vis[x] = t;
	for (int i = head[x]; i; i = nxt[i])
		if (val[i] == A && vis[to[i]] == 100) dfs2(to[i], t);
}
int dis[maxP];
int q1[maxP], q2[maxP], l1 = 1, r1 = 0, l2 = 1, r2 = 0;
inline int at(int st, int p) { return st * n + p - 1; }
int main() {
	scanf("%d %d %d %d", &n, &m, &A, &B);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &x, &y, &z);
		insert(x, y, z);
		insert(y, x, z);
	}
	for (int i = 1; i <= n; ++i)
		if (vis[i] == 0) {
			top = 0;
			dfs1(i);
			if (top > 3) { ++cId; while (top) vis[stack[top--]] = cId; }
		}
	for (int i = 1; i <= n; ++i) if (vis[i] == 100) { static int nId = 100; dfs2(i, ++nId); }
	memset(dis, 0x7f, sizeof dis);
	dis[at(0, 1)] = 0;
	q2[l1 = r1 = 1] = q2[l2 = r2 = 1] = at(0, 1);
	while (l1 <= r1 || l2 <= r2) {
		int S = 0;
		if (l1 > r1) S = q2[l2++];
		else if (l2 > r2) S = q1[l1++];
		else S = dis[q1[l1]] < dis[q2[l2]] ? q1[l1++] : q2[l2++];
		x = S % n + 1; int st = S / n;
		for (int i = head[x]; i; i = nxt[i]) {
			if (vis[to[i]] <= cId && ((st >> (vis[to[i]] - 1)) & 1)) continue;
			if (vis[to[i]] == vis[x] && val[i] == B) continue;
			int nS = (vis[x] <= cId && vis[to[i]] != vis[x]) ? (st | (1 << (vis[x] - 1))) : st;
			nS = at(nS, to[i]);
			if (dis[nS] > dis[S] + val[i]) {
				dis[nS] = dis[S] + val[i];
				if (val[i] == A) q1[++r1] = nS;
				else q2[++r2] = nS;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		int ans = 0x7fffffff;
		for (int s = 0; s < (1 << cId); ++s) if (dis[at(s, i)] < ans) ans = dis[at(s, i)];
		printf("%d ", ans);
	}
	return 0;
}