#include <cstdio>
#include <algorithm>
int n = 0, m = 0, t = 0;
char G[23][23];
int ca[23], cb[23];
int va[23], vb[23];
bool f[1 << 21], g[1 << 21];

inline int countBit(int x) { int r = 0; while (x) { r += (x & 1); x >>= 1; } return r; }
inline void checkA(int x) {
	int ls = 0, cnt = 0;
	for (int j = 0; j < n; ++j) if ((x >> j) & 1) { ls |= ca[j]; ++cnt; }
	f[x] = (countBit(ls) >= cnt);
}
inline void checkB(int x) {
	int ls = 0, cnt = 0;
	for (int j = 0; j < m; ++j) if ((x >> j) & 1) { ls |= cb[j]; ++cnt; }
	g[x] = (countBit(ls) >= cnt);
}
inline void FMT(bool *ar, int N) {
	for (int len = 1; len < N; len <<= 1)
		for (int i = 0; i < N; i += len << 1)
			for (int j = 0; j < len; ++j)
				ar[i + len + j] = ar[i + len + j] && ar[i + j];
}
int sa[1 << 21], sb[1 << 21], cntA = 0, cntB = 0;
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%s", G[i]);
		for (int j = 0; j < m; ++j) if (G[i][j] == '1') { ca[i] |= 1 << j; cb[j] |= 1 << i; }
	}
	for (int i = 0; i < n; ++i) scanf("%d", va + i);
	for (int i = 0; i < m; ++i) scanf("%d", vb + i);
	scanf("%d", &t);

	for (int i = 0; i < (1 << n); ++i) checkA(i);
	for (int i = 0; i < (1 << m); ++i) checkB(i);
	FMT(f, 1 << n); FMT(g, 1 << m);
	for (int i = 0; i < (1 << n); ++i)
		if (f[i]) {
			for (int j = 0; j < n; ++j) if ((i >> j) & 1) sa[cntA] += va[j];
			++cntA;
		}
	for (int i = 0; i < (1 << m); ++i)
		if (g[i]) {
			for (int j = 0; j < m; ++j) if ((i >> j) & 1) sb[cntB] += vb[j];
			++cntB;
		}

	std::sort(sa, sa + cntA);
	std::sort(sb, sb + cntB);
	long long ans = 0;
	for (int i = 0, j = cntB; i < cntA; ++i) {
		while (j > 0 && sb[j - 1] + sa[i] >= t) --j;
		ans += cntB - j;
	}
	printf("%lld", ans);
	return 0;
}