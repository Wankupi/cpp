#include <cstdio>
int n = 0;
int G['z' + 5]['z' + 5];
int d['z' + 5];
char res[1500];
void dfs(int x) {
	static int pos = n;
	for(int i = 'A';i<='z';++i)
		if(G[x][i]) {
			G[x][i] = G[i][x] = 0;
			dfs(i);
		}
	res[pos--] = x;
}
int main() {
	unsigned char str[3];
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str);
		G[str[0]][str[1]] = G[str[1]][str[0]] = 1;
		++d[str[0]];
		++d[str[1]];
	}
	int s = 0, cnt = 0;
	for (int i = 'A'; i <= 'z'; ++i)
		if (d[i] & 1) {
			if (!s) s = i;
			++cnt;
		}
	if (cnt != 0 && cnt != 2) {
		puts("No Solution");
		return 0;
	}
	if (s == 0)
		for (int i = 'A'; i <= 'z'; ++i)
			if (d[i]) {
				s = i;
				break;
			}
	dfs(s);
	puts(res);
	return 0;
}