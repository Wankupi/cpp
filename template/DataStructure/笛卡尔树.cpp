#include <cstdio>
void read(int &x) {
	x = 0;
	int c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9')
		x = 10 * x + c - '0', c = getchar();
}
int n = 0;
int p[10000001];
int ls[10000001], rs[10000001];
int stack[10000001], top = 0;
int main() {
	read(n);
	for (int i = 1; i <= n; ++i)
		read(p[i]);
	int last = 0;
	for (int i = 1; i <= n; ++i) {
		last = top;
		while (top && p[stack[top]] > p[i])
			--top;
		if (top) rs[stack[top]] = i;
		if (top < last) ls[i] = stack[top + 1];
		stack[++top] = i;
	}
	long long ansL = 0, ansR = 0;
	for(int i =1;i<=n;++i) {
		ansL ^= (long long)(i) * (ls[i] + 1ll);
		ansR ^= (long long)(i) * (rs[i] + 1ll);
	}
	printf("%lld %lld", ansL, ansR);
	return 0;
}