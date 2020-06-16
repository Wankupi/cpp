#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000010;
int n = 0, m = 122;
char s[maxn];
int sa[maxn];
int X[maxn], Y[maxn], c[maxn];
void GetSA() {
	int *x = X, *y = Y;
	for (int i = 1; i <= n; ++i) ++c[ x[i] = s[i] ];
	for (int i = 2; i <= m; ++i)
		c[i] += c[i - 1];
	for (int i = n; i; --i)
		sa[c[x[i]]--] = i;
	for (int k = 1; k <= n; k <<= 1) {
		int cnt = 0;
		for (int i = n - k + 1; i <= n; ++i)
			y[++cnt] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > k) y[++cnt] = sa[i] - k;

		for (int i = 1; i <= m; ++i)
			c[i] = 0;
		for (int i = 1; i <= n; ++i)
			++c[x[i]];
		for (int i = 1; i <= m; ++i)
			c[i] += c[i - 1];
		for (int i = n; i; --i)
			sa[c[x[y[i]]]--] = y[i], y[i] = 0;
		swap(x, y);
		x[sa[1]] = 1;
		cnt = 1;
		for (int i = 2; i <= n; ++i) {
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? cnt : ++cnt;
		}
		if (cnt == n) break;
		m = cnt;
	}
}
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	GetSA();
	for (int i = 1; i <= n; ++i)
		printf("%d ", sa[i]);
	return 0;
}