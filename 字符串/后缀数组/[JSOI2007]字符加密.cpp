#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 200007;
int n = 0, N = 0, m = 0;
char s[200007];
int sa[maxn], A[maxn], B[maxn], t[maxn];
int *rank = A, *tp = B;
inline void Qsort() {
	for (int i = 0; i <= m; ++i) t[i] = 0;
	for (int i = 1; i <= N; ++i) ++t[rank[i]];
	for (int i = 1; i <= m; ++i) t[i] += t[i - 1];
	for (int i = N; i >= 1; --i) sa[t[rank[tp[i]]]--] = tp[i];
}
void SurffixSort() {
	m = 256;
	for (int i = 1; i <= N; ++i) rank[i] = s[i], tp[i] = i;
	Qsort();
	for (int len = 1, p = 0; len < N && p < N; m = p, len <<= 1) {
		p = 0;
		for (int i = 1; i <= len; ++i) tp[++p] = N - len + i;
		for (int i = 1; i <= N; ++i) if (sa[i] > len) tp[++p] = sa[i] - len;
		Qsort();
		tp[sa[1]] = p = 1;
		for (int i = 2; i <= N; ++i) tp[sa[i]] = (rank[sa[i - 1]] == rank[sa[i]] && rank[sa[i - 1] + len] == rank[sa[i] + len] ? p : ++p);
		std::swap(rank, tp);
	}
}
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; ++i)
		s[i + n] = s[i];
	N = 2 * n;
	SurffixSort();
	for (int i = 1; i <= N; ++i) if (sa[i] <= n) putchar(s[sa[i] + n - 1]);
	return 0;
}
