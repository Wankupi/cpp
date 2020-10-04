#include <algorithm>
#include <cstdio>
using namespace std;
int const mod = 1000000000;
int const dx[] = {+1, 0}, dy[] = {0, +1};
int n = 0, m = 0;
char a[13][13];
int id[13][13], cP = 0;
int G[100][100];
int ans = 1;
void gauss() { // delete the last colunm and line
	for (int i = 1; i < cP; ++i) {
		for (int j = i + 1; j < cP; ++j) {
			while (G[j][i]) {
				long long d = G[i][i] / G[j][i];
				for (int k = i; k < cP; ++k)
					G[i][k] = (G[i][k] - d * G[j][k] % mod + mod) % mod;
				swap(G[i], G[j]);
				ans = -ans;
			}
		}
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", a[i] + 1);
		for (int j = 1; j <= m; ++j)
			if (a[i][j] == '.')
				id[i][j] = ++cP;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] != '.') continue;
			int I = id[i][j];
			for (int k = 0; k < 2; ++k) {
				int x = i + dx[k], y = j + dy[k];
				int U = id[x][y];
				if (!U) continue;
				++G[I][I];
				++G[U][U];
				--G[I][U];
				--G[U][I];
			}
		}
	}
	gauss();
	for (int i = 1; i < cP; ++i)
		ans = 1ll * ans * G[i][i] % mod;
	ans = (ans + mod) % mod;
	printf("%d", ans);
	return 0;
}