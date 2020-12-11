#include <cstdio>
int n = 0;
int a[600001];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		a[i + n] = a[i];
	}
	int i = 1, j = 2, k = 0;
	while (i <= n && j <= n) {
		if (i == j) ++j;
		k = 0;
		while (k < n && a[i + k] == a[j + k]) ++k;
		if (k >= n) break;
		if (a[i + k] < a[j + k]) j += k + 1;
		else i += k + 1;
	}
	i = (i < j ? i : j);
	for (int p = i; p - i + 1 <= n; ++p) printf("%d ", a[p]);
	return 0;
}