#include <bitset>
#include <cstdio>
#include <iostream>
using namespace std;
int n = 0, m = 0;
int N = 0;
inline int f(int y, int x) { return y * m + x; }
bitset<1603> a[1603];
int ans[1605];
void Gauss() {
	for (int i = 0; i < N; ++i) {
		int k = i;
		while (k + 1 < N && !a[k][i])
			++k;
		if (k != i && a[k][i]) swap(a[i], a[k]);
		if (!a[i][i]) a[i][i] = a[i][N + 1] = 1;
		for (int j = 0; j < N; ++j)
			if (i != j && a[j][i]) a[j] ^= a[i];
	}
}
int main() {
	scanf("%d%d", &n, &m);
	N = n * m;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			a[f(i, j)][f(i, j)] = true;
			if (i > 0) a[f(i, j)][f(i - 1, j)] = true;
			if (j > 0) a[f(i, j)][f(i, j - 1)] = true;
			if (i + 1 < n) a[f(i, j)][f(i + 1, j)] = true;
			if (j + 1 < m) a[f(i, j)][f(i, j + 1)] = true;
		}
	Gauss();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			printf("%d ", int(a[f(i, j)][N + 1]));
		putchar('\n');
	}
	return 0;
}