#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cctype>
#define mod 19260817;
int n = 0, m = 0;
int a[110];
inline int read() {
	long long x = 0;
	char c = getchar(); bool fu = false;
	while (!isdigit(c)) { if (c == '-') fu = true; c = getchar(); }
	while (isdigit(c)) {
		x = ((x << 1) + (x << 3) + c - '0') % mod;
		c = getchar();
	}
	return fu ? -x : x;
}
inline bool func(int x) {
	long long ans = 0;
	for (int i = n; ~i; --i)
		ans = (ans * x + a[i]) % mod;
	return ans == 0;
}
int ans[10000], cnt = 0;
int main() {
	n = read(); m = read();
	for (int i = 0; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= m; ++i)
		if (func(i)) ans[cnt++] = i;
	printf("%d", cnt);
	for (int i = 0; i != cnt; ++i)
		printf("\n%d", ans[i]);
	return 0;
}