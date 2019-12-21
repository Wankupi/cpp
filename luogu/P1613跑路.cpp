#include <cstdio>
#include <queue>
int n = 0, m = 0;
int dis[51][51];
bool able[51][51][65];
int min(int a, int b) { return a < b ? a : b; }
int main() {
	scanf("%d%d", &n, &m);
	int a = 0, b = 0;
	for (int i = 1; i <= n;++i)
		for (int j = 1; j <= n;++j)
			dis[i][j] = 100;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &a, &b);
		dis[a][b] = 1;
		able[a][b][0] = true;
	}
	for (int t = 1; t <= 64;++t)
		for (int k = 1; k <= n;++k)
			for (int i = 1; i <= n;++i)
				for (int j = 1; j <= n;++j)
					if(able[i][k][t-1]&&able[k][j][t-1]){
						able[i][j][t] = true;
						dis[i][j] = 1;
					}
	for (int k = 1; k <= n;++k)
		for (int i = 1; i <= n;++i)
			for (int j = 1; j <= n;++j)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	printf("%d", dis[1][n]);
	return 0;
}