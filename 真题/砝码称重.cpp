#include <cstdio>
bool f[1001];
int a[10];
const int w[] = { 0, 1,2,3,5,10,20 };
int main() {
	f[0] = 1;
	for (int i = 1; i <= 6; ++i)
		scanf("%d", a + i);
	for (int i = 1; i <= 6; ++i) {
		for (int j = 1; j <= a[i]; ++j) {
			for (int k = 1000; k >= w[i]; --k)
				if (f[k - w[i]]) f[k] = true;
		}
	}
	int ans = 0;
	for (int i = 1; i <= 1000; ++i)
		ans += f[i];
	printf("Total=%d", ans);
	return 0;
}