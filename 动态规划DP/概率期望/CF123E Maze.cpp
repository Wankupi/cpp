#include <cstdio>
#include <iostream>
typedef long long ll;
const int maxn = 100003;
int n = 0;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt = 0;
void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int extr[maxn], Exit[maxn];
ll SumIn = 0, SumOut = 0;
ll down[maxn];
int siz[maxn];
double ans = 0.0;
void dfs(int x, int fa) {
	siz[x] = 1;
	down[x] = extr[x];
	double addition = 0.0; 
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa) {
			dfs(to[i], x);
			siz[x] += siz[to[i]];
			down[x] += down[to[i]];
			addition += double(down[to[i]]) / double(SumIn) * siz[to[i]];
		}
	addition += double(SumIn - down[x]) / double(SumIn) * (n - siz[x]);
	ans += addition * double(Exit[x]) / double(SumOut);
}

int main() {
	scanf("%d", &n);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", extr + i, Exit + i);
		SumIn += extr[i];
		SumOut += Exit[i];
	}
	dfs(1, 1);
	printf("%.12lf", ans);
	return 0;
}