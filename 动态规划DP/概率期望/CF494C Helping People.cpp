#include <cstdio>
#include <algorithm>
using namespace std;
struct Operation {
	int l, r, mx;
	double p;
};
bool operator<(Operation const &lhs, Operation const &rhs) { return lhs.l == rhs.l ? lhs.r > rhs.r : lhs.l < rhs.l; }

int n = 0, m = 0;
int a[100003], lg2[100003], rmq[17][100003];
Operation o[5003];
int head[5003], nxt[5003], to[5003], cntEdge = 0;
inline void insert(int u, int e) { nxt[++cntEdge] = head[u]; head[u] = cntEdge; to[cntEdge] = e; }
inline int getMax(int l, int r) {
	int len = r - l + 1, k = lg2[len];
	return std::max(rmq[k][l], rmq[k][r - (1 << k) + 1]);
}
double f[5003][5003];
void dfs(int x) {
	for (int i = head[x]; i; i = nxt[i]) dfs(to[i]);
	f[x][0] = 1 - o[x].p;
	for (int i = head[x]; i; i = nxt[i])
		if (o[x].mx - o[to[i]].mx <= m)
			f[x][0] *= f[to[i]][o[x].mx - o[to[i]].mx];
	for (int j = 1; j <= m; ++j) {
		double p1 = o[x].p, p2 = 1 - o[x].p;
		for (int i = head[x]; i; i = nxt[i]) {
			if (j + o[x].mx - o[to[i]].mx - 1 <= m) p1 *= f[to[i]][j + o[x].mx - o[to[i]].mx - 1];
			if (j + o[x].mx - o[to[i]].mx <= m) p2 *= f[to[i]][j + o[x].mx - o[to[i]].mx];
		}
		f[x][j] = p1 + p2;
	}
}
int main() {
	scanf("%d %d", &n, &m);
	lg2[0] = -1;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		lg2[i] = lg2[i >> 1] + 1;
		rmq[0][i] = a[i];
	}
	for (int j = 1; j <= 16; ++j) {
		for (int i = 1; i <= n - (1 << j) + 1; ++i)
			rmq[j][i] = std::max(rmq[j - 1][i], rmq[j - 1][i + (1 << (j - 1))]);
	}
	for (int i = 1; i <= m; ++i)
		scanf("%d %d %lf", &o[i].l, &o[i].r, &o[i].p);
	++m;
	o[m].l = 1; o[m].r = n; o[m].p = 0;
	sort(o + 1, o + m + 1);
	for (int i = 1; i <= m; ++i) o[i].mx = getMax(o[i].l, o[i].r);
	for (int i = 2; i <= m; ++i) {
		for (int j = i - 1; j >= 1; --j) {
			if (o[j].l <= o[i].l && o[j].r >= o[i].r) {
				insert(j, i);
				break;
			}
		}
	}
	dfs(1);
	double ans = o[1].mx * f[1][0];
	for (int i = 1; i <= m; ++i)
		ans += (o[1].mx + i) * (f[1][i] - f[1][i - 1]);
	printf("%.9lf\n", ans);
	return 0;
}