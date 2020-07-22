#include <cstdio>
#include <cstring>
const int Goal[6][6] = {
	{0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1},
	{0, 0, 1, 1, 1, 1},
	{0, 0, 0, 2, 1, 1},
	{0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0}};
const int dx[8] = {-2, -2, -1, -1, +1, +1, +2, +2};
const int dy[8] = {+1, -1, +2, -2, +2, -2, +1, -1};
int st[6][6];
inline int diff() {
	int cnt = 0;
	for (int i = 1; i <= 5; ++i)
		for (int j = 1; j <= 5; ++j)
			cnt += (Goal[i][j] != st[i][j]);
	return cnt;
}
inline void swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}
int step = 0;
bool dfs(int t, int x, int y) {
	if (t == step)
		return diff() == 0;
	for (int i = 0; i < 8; ++i) {
		int X = x + dx[i], Y = y + dy[i];
		if (X < 1 || x > 5 || Y < 1 || Y > 5) continue;
		swap(st[y][x], st[Y][X]);
		if (diff() + t <= step && dfs(t + 1, X, Y)) return true;
		swap(st[y][x], st[Y][X]);
	}
	return false;
}
int main() {
	int T = 0;
	scanf("%d\n", &T);
	for (int t = 1; t <= T; ++t) {
		memset(st, 0, sizeof st);
		int c = 0;
		int x0 = 0, y0 = 0;
		for (int i = 1; i <= 5; ++i) {
			for (int j = 1; j <= 5; ++j) {
				do
					c = getchar();
				while (c != '1' && c != '0' && c != '*');
				st[i][j] = (c == '0' ? 0 : (c == '1' ? 1 : 2));
				if (c == '*') {
					y0 = i;
					x0 = j;
				}
			}
		}
		if (diff() == 0) {
			printf("0");
			continue;
		}
		bool sign = false;
		for (step = 1; step <= 15; ++step)
			if (dfs(0, x0, y0)) {
				sign = true;
				break;
			}
		if (sign)
			printf("%d\n", step);
		else
			printf("-1\n");
	}
	return 0;
}