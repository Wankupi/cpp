#include <cmath>
#include <cstdio>
int n = 0;
long long h = 0, r = 0;
long long x[1010], y[1010], z[1010];
int fa[1010];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int a, int b) { fa[find(b)] = find(a); }
void init() {
	scanf("%d%lld%lld", &n, &h, &r);
	fa[n + 1] = n + 1;
	fa[n + 2] = n + 2;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld%lld%lld", x + i, y + i, z + i);
		fa[i] = i;
		if (z[i] <= r && z[i] >= -r)
			merge(n + 1, i);
		if (z[i] + r >= h)
			merge(n + 2, i);
	}
}
inline bool distance(int a, int b) {
	return ((x[a] - x[b]) * (x[a] - x[b]) +
		(y[a] - y[b]) * (y[a] - y[b]) +
			(z[a] - z[b]) * (z[a] - z[b])) <= 4 * r * r;
}
int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		init();
		bool sign = false;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j)
				if (find(i) != find(j) && distance(i, j))
					merge(i, j);
			if (find(n + 2) == find(n + 1)) {
				sign = true;
				break;
			}
		}
		puts(sign ? "Yes" : "No");
	}
	return 0;
}