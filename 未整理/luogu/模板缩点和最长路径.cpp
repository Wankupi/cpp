#include <cstdio>
using namespace std;
constexpr int maxP = 10001, maxLine = 100001;
int a[maxP];
int head1[maxP], nxt1[maxLine], to1[maxLine], cnt1 = 0;
inline void insert1(int u, int e) { nxt1[++cnt1] = head1[u]; head1[u] = cnt1; to1[cnt1] = e; }
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }
int dfn[maxP], low[maxP], nick[maxP], num = 0, id = 0;
int stack[maxP], up = 0;
bool vis[maxP];
int w[maxP], dis[maxP];
void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	stack[++up] = x; vis[x] = true;
	int y = 0;
	for (int i = head1[x]; i; i = nxt1[i]) {
		y = to1[i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		}
		else if (vis[y])
			low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] == low[x]) {
		++id;
		do {
			y = stack[up--];
			nick[y] = id;
			vis[y] = false;
			w[id] += a[y];
		} while (y != x);
	}
}
int head2[maxP], nxt2[maxLine], to2[maxLine], cnt2 = 0;
inline void insert2(int u, int e) { nxt2[++cnt2] = head2[u]; head2[u] = cnt2; to2[cnt2] = e;}
int in[maxP], out[maxP];
int dl[maxP], l = 0, r = 0;
int main() {
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	int u = 0, v = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &u, &v);
		insert1(u, v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i);
	for (int x = 1; x <= n; ++x) {
		for (int i = head1[x]; i; i = nxt1[i]) {
			if (nick[x] != nick[to1[i]]) {
				insert2(nick[x], nick[to1[i]]);
				++in[nick[to1[i]]];
				++out[nick[x]];
			}
		}
	}
	int ans = 0;
	for (int x = 1; x <= id; ++x)
		if (in[x] == 0) dl[r++] = x;
	while (l != r) {
		v = dl[l++];
		for (int i = head2[v]; i; i = nxt2[i]) {
			dis[to2[i]] = max(dis[to2[i]], dis[v] + w[v]);
			if ((--in[to2[i]]) == 0)
				dl[r++] = to2[i];
		}
		if (!out[v]) ans = max(ans, w[v] + dis[v]);
	}
	printf("%d", ans);
	return 0;
}