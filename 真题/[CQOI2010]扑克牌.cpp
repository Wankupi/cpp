#include <algorithm>
#include <cstdio>

int n = 0, m = 0;
int c[53];
bool check(int x) {
	long long rest = 0;
	for (int i = 1; i <= n; ++i)
		if (c[i] < x) rest += x - c[i];
	return rest <= m && rest <= x;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", c + i);
	std::sort(c + 1, c + n + 1);
	int l = c[1], r = c[n] + m, mid = 0;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid))
			l = mid + 1;
		else
			r = mid - 1;
	}
	printf("%d", l - 1);
	return 0;
}
