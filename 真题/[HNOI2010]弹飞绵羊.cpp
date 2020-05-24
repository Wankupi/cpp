#include <cmath>
#include <cstdio>
struct Data { int to, step; };
int n = 0, block = 0;
int a[200003], r[200003];
Data b[200003];
int main() {
	scanf("%d", &n);
	block = sqrt(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		r[i] = (i < block ? (block - 1) : r[i - block] + block);
		if (r[i] >= n) r[i] = n - 1;
	}
	for (int i = n - 1; i >= 0; --i)
		if (i + a[i] > r[i]) {
			b[i].to = i + a[i];
			b[i].step = 1;
		}
		else {
			b[i].to = b[i + a[i]].to;
			b[i].step = b[i + a[i]].step + 1;
		}
	int m = 0, x = 0, y = 0, z = 0;
	scanf("%d", &m);
	for (int t = 1; t <= m; ++t) {
		scanf("%d%d", &x, &y);
		if (x == 1) {
			int sum = 0;
			while (y < n) {
				sum += b[y].step;
				y = b[y].to;
			}
			printf("%d\n", sum);
		}
		else {
			scanf("%d", &z);
			a[y] = z;
			for (int i = y; r[i] == r[y]; --i)
				if (i + a[i] > r[i]) {
					b[i].to = i + a[i];
					b[i].step = 1;
				} else {
					b[i].to = b[i + a[i]].to;
					b[i].step = b[i + a[i]].step + 1;
				}
		}
	}
	return 0;
}