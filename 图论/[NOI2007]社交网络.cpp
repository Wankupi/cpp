#include <cstdio>
#include <cstring>
typedef long long ll;
int n = 0, m = 0;
int dis[103][103];
ll cnt[103][103];
double ans[103];
int main() {
	scanf("%d%d", &n, &m);
	memset(dis, 0x3f, sizeof dis);
	int a = 0, b = 0, c = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		dis[a][b] = dis[b][a] = c;
		cnt[a][b] = cnt[b][a] = 1;
	}
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			if (cnt[i][k])
				for (int j = 1; j <= n; ++j)
					if (dis[i][j] > dis[i][k] + dis[k][j]) {
						dis[i][j] = dis[i][k] + dis[k][j];
						cnt[i][j] = cnt[i][k] * cnt[k][j];
					} else if (dis[i][j] == dis[i][k] + dis[k][j])
						cnt[i][j] += cnt[i][k] * cnt[k][j];
	for (int v = 1; v <= n; ++v)
		for (int s = 1; s <= n; ++s) {
			if (s == v) continue;
			for (int t = 1; t <= n; ++t) {
				if (t == v || s == t) continue;
				if (dis[s][t] == dis[s][v] + dis[v][t])
					ans[v] += double(cnt[s][v] * cnt[v][t]) / double(cnt[s][t]);
			}
		}
	for (int i = 1; i <= n; ++i)
		printf("%.3lf\n", ans[i]);
	return 0;
}