#include <iostream>
using namespace std;
int map[101];
int f[3][65][65];
int biao[80], num[65], cnt = 0;
inline int cont(int a) {
	int ret = 0;
	while (a) {
		if (a & 1)
			ret++;
		a >>= 1;
	}
	return ret;
}
inline bool chick1(int i) {
	if (i & (i << 1) || i & (i << 2))
		return false;
	return true;
}
inline bool chickMap(int i, int a) { return (map[i] & biao[a]) == biao[a]; }
inline bool chickLine(int a, int b) { return !(biao[a] & biao[b]); }
inline int max(int a, int b) { return a > b ? a : b; }
int main() {
	int n = 0, m = 10;
	scanf("%d%d", &n, &m);
	char c = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> c;
			(map[i] <<= 1) |= (c == 'P');
		}
	}
	for (int i = 0; i < (1 << m); ++i)
		if (chick1(i)) {
			biao[cnt] = i;
			num[cnt] = cont(i);
			cnt++;
		}

	for (int a = 0; a != cnt; a++)
		if (chickMap(1, a))
			for (int i = 0; i != cnt; i++)
				f[1][a][i] = num[a];
	for (int i = 2; i <= n; ++i) {
		for (int a = 0; a != cnt; ++a) {
			if (chickMap(i, a))
				for (int b = 0; b != cnt; ++b) {
					f[i % 3][a][b] = 0;
					if (chickMap(i - 1, b) && chickLine(a, b))
						for (int c = 0; c != cnt; ++c) {
							if (chickMap(i - 2, c) && chickLine(a, c) && chickLine(b, c))
								f[i % 3][a][b] = max(f[i % 3][a][b], f[(i - 1) % 3][b][c] + num[a]);
						}
				}
		}
	}
	int ans = 0;
	for (int i = 0; i != cnt; ++i)
		for (int j = 0; j != cnt; ++j)
			ans = max(ans, f[n % 3][i][j]);
	cout << ans;
	return 0;
}