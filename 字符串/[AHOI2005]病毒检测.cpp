#include <bitset>
#include <cstdio>
#include <cstring>
using namespace std;

short f[256];
char T[1003], s[503];

int lenT = 0, n = 0;
int tr[250003][4], cnt = 0;
int end_cnt[250003];
void insert(char const *str) {
	int p = 0;
	while (*str) {
		int c = f[int(*str++)];
		if (tr[p][c] == 0) tr[p][c] = ++cnt;
		p = tr[p][c];
	}
	++end_cnt[p];
}

bitset<1000> vis[250003];
int ans = 0;
void dfs(int x, int p) {
	if (p == lenT) {
		ans += end_cnt[x];
		end_cnt[x] = 0;
		return;
	}
	if (vis[x][p]) return;
	vis[x].set(p);
	int c = f[int(T[p])];
	if (0 <= c && c <= 3) {
		if (tr[x][c])
			dfs(tr[x][c], p + 1);
	}
	else if (T[p] == '*') {
		dfs(x, p + 1);
		for (int i = 0; i < 4; ++i)
			if (tr[x][i]) {
				dfs(tr[x][i], p + 1);
				dfs(tr[x][i], p);
			}
	}
	else {
		for (int i = 0; i < 4; ++i)
			if (tr[x][i])
				dfs(tr[x][i], p + 1);
	}
}

int main() {
	f['A'] = 0; f['T'] = 1; f['C'] = 2; f['G'] = 3;
	f['?'] = f['*'] = -1;
	scanf("%s", T); lenT = strlen(T);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s);
		insert(s);
	}
	dfs(0, 0);
	printf("%d", n - ans);
	return 0;
}