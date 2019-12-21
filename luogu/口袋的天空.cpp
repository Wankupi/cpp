#include <algorithm>
#include <cstdio>
struct Bian {
	int u, e, v;
} b[10001];
bool operator<(const Bian &l, const Bian &r) { return l.v < r.v; }
int fa[1001];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
inline void merge(int a, int b) { fa[find(b)] = find(a); }
int main() {
	int n = 0, m = 0, k = 0;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; ++i)
		scanf("%d%d%d", &b[i].u, &b[i].e, &b[i].v);
	std::sort(b + 1, b + m + 1);
	int cnt = n, sum = 0;
	for (int i = 1; i <= n; ++i)
		fa[i] = i;
	for (int i = 1; i <= m; ++i) {
		int x = find(b[i].u), y = find(b[i].e);
		if (x == y)
			continue;
		merge(x, y);
		sum += b[i].v;
		if (--cnt == k)
			break;
	}
	if (cnt == k)
		printf("%d", sum);
	else
		printf("No Answer");
	return 0;
}