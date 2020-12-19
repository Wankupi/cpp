#include <cstdio>
typedef long long ll;
int const maxn = 5000003;
int n = 0;
int f[maxn], p[maxn], d[maxn];
ll ans = 0;
inline void TreePrufer() {
	for (int i = 1; i < n; ++i) scanf("%d", f + i), ++d[f[i]];
	for (int i = 1, j = 1; i <= n - 2; ++i, ++j) {
		while (d[j]) ++j;
		p[i] = f[j];
		while (i <= n - 2 && --d[p[i]] == 0 && p[i] < j)
			p[i + 1] = f[p[i]],  ++i;
	}
	for (int i = 1; i <= n - 2; ++i) ans ^= ll(i) * p[i];
}

inline void PruferTree() {
	for (int i = 1; i <= n - 2; ++i) scanf("%d", p + i), ++d[p[i]];
	p[n - 1] = n;
	for (int i = 1, j = 1; i < n; ++i, ++j) {
		while (d[j]) ++j;
		f[j] = p[i];
		while (i < n && --d[p[i]] == 0 && p[i] < j) f[p[i]] = p[i + 1], ++i;
	}
	for (int i = 1; i < n; ++i) ans ^= ll(i) * f[i];
}
int main() {
	int opt = 0;
	scanf("%d %d", &n, &opt);
	if (opt == 1) TreePrufer(); else PruferTree();
	printf("%lld", ans);
	return 0;
}