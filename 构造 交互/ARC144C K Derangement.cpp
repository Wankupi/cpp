#include <cstdio>
#include <set>
using namespace std;

int a[300003];
bool used[300003];

int main() {
	int n = 0, k = 0;
	scanf("%d %d", &n, &k);
	if (n < 2 * k) {
		printf("-1\n");
		return 0;
	}
	int add = 0;
	while (n >= 2 * k) {
		if (n >= 4 * k) {
			for (int i = 1; i <= k; ++i) printf("%d ", i + k + add);
			for (int i = 1; i <= k; ++i) printf("%d ", i + add);
			n -= 2 * k;
			add += 2 * k;
		}
		else if (n > 3 * k) {
			for (int i = 1; i <= k; ++i) printf("%d ", i + k + add);
			for (int i = k + 1; i <= n - 2 * k; ++i) printf("%d ", i - k + add);
			for (int i = n - 2 * k + 1; i <= n - k; ++i) printf("%d ", i + k + add);
			for (int i = n - k + 1; i <= 3 * k; ++i) printf("%d ", i - 2 * k + add);
			for (int i = 3 * k + 1; i <= n; ++i) printf("%d ", i - k + add);
			n = 0;
		}
		else {
			for (int i = 1; i <= n - k; ++i) printf("%d ", i + k + add);
			for (int i = n - k + 1; i <= n; ++i) printf("%d ", i - n + k + add);
			n = 0;
		}
	}
	return 0;
}