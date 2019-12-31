#include <cstdio>
void read(int &x) {
	x = 0; int c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar();}
}
int n = 0;
int a[262150], f[60][262145];
int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		f[a[i]][i] = i + 1;
	}
	int ans = 0;
	for (int j = 1; j <= 58; ++j)
		for (int i = 1; i <= n; ++i) {
			if (!f[j][i]) f[j][i] = f[j - 1][f[j - 1][i]];
			if (f[j][i]) ans = j;
		}
	printf("%d", ans);
	return 0;
}