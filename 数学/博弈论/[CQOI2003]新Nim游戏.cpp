#include <algorithm>
#include <cstdio>
int n = 0;
unsigned int a[105];
unsigned long long sum = 0;
unsigned int base[33];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		sum += a[i];
	}
	std::sort(a + 1, a + n + 1);
	for (int i = n; i >= 1; --i) {
		int t = a[i];
		for (int j = 31; ~j; --j) {
			if ((t >> j) & 1) {
				if (!base[j]) {
					base[j] = t;
					break;
				} else
					t ^= base[j];
			}
		}
		if (t) sum -= a[i];
	}
	printf("%llu", sum);
	return 0;
}