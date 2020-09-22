#include <algorithm>
#include <cstdio>
using namespace std;
int const maxn = 200003;
int n = 0;
int a[maxn];
int tr[maxn * 20][2], L[maxn * 20], R[maxn * 20], cnt = 0;
void insert(int x, int pos) {
	int p = 0;
	for (int j = 29; ~j; --j) {
		if (tr[p][(x >> j) & 1] == 0) tr[p][(x >> j) & 1] = ++cnt, L[cnt] = pos;
		p = tr[p][(x >> j) & 1];
		if (pos > R[p]) R[p] = pos;
	}
}
int find_minXor(int p, int x, int j) {
	int r = 0;
	for (; ~j; --j) {
		int c = (x >> j) & 1;
		if (tr[p][c])
			p = tr[p][c];
		else {
			r |= (1 << j);
			p = tr[p][c ^ 1];
		}
	}
	return r;
}
long long ans = 0;
void dfs(int p, int j) {
	if (tr[p][0]) dfs(tr[p][0], j - 1);
	if (tr[p][1]) dfs(tr[p][1], j - 1);
	int Minval = 0x7fffffff;
	if (tr[p][0] && tr[p][1]) {
		int c = (R[tr[p][1]] - L[tr[p][1]] <= R[tr[p][0]] - L[tr[p][0]]);
		for (int i = L[tr[p][c]]; i <= R[tr[p][c]]; ++i) {
			int k = find_minXor(tr[p][c ^ 1], a[i], j - 1) | (1 << j);
			if (k < Minval) Minval = k;
		}
		ans += Minval;
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i)
		insert(a[i], i);
	dfs(0, 29);
	printf("%lld", ans);
	return 0;
}