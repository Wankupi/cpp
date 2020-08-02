#include <cstdio>
int sg[25], t[50];
void init() {
	sg[1] = 0;
	for (int i = 2; i <= 21; ++i) {
		for (int j = 1; j < i; ++j) {
			for (int k = 1; k <= j; ++k)
				t[sg[j] ^ sg[k]] = i;
		}
		for (int v = 0; t[v] == i; ++v)
			++sg[i];
	}
}
int n = 0;
int a[25], delta = 0;
void solve() {
	int cnt = 0;
	bool sign = true;
	for (int i = n; i > 0; --i) {
		for (int j = i - 1; j >= 1; --j) {
			for (int k = j; k >= 1; --k) {
				if ((delta ^ sg[i] ^ sg[j] ^ sg[k]) == 0) {
					++cnt;
					if (sign) {
						printf("%d %d %d\n", n - i, n - j, n - k);
						sign = false;
					}
				}
			}
		}
	}
	printf("%d\n", cnt);
}
int main() {
	init();
	int T = 0;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		scanf("%d", &n);
		for (int i = n; i >= 1; --i)
			scanf("%d", a + i);
		delta = 0;
		for (int i = 1; i <= n; ++i)
			if (a[i] & 1) delta ^= sg[i];
		if (delta == 0) {
			puts("-1 -1 -1\n0");
			continue;
		}
		else
			solve();
	}
	return 0;
}