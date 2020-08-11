#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 1000007;
int n = 0;
char s[maxn];
int sa[maxn];
int A[maxn], B[maxn], t[maxn];
int *rank = A, *tp = B;
int m = 0;
inline void Qsort() {
	for (int i = 0; i <= m; ++i) t[i] = 0;
	for (int i = 1; i <= n; ++i) ++t[rank[i]];
	for (int i = 1; i <= m; ++i) t[i] += t[i - 1];
	for (int i = n; i >= 1; --i) sa[t[rank[tp[i]]]--] = tp[i];
}
void SAsort() {
	m = 256;
	for (int i = 1; i <= n; ++i) rank[i] = s[i], tp[i] = i;
	Qsort();
	for (int len = 1, p = 0; p < n && len < n; m = p, len <<= 1) {
		p = 0;
		for (int i = 1; i <= len; ++i) tp[++p] = n - len + i;
		for (int i = 1; i <= n; ++i) if (sa[i] > len) tp[++p] = sa[i] - len;
		Qsort();
		tp[sa[1]] = p = 1;
		for (int i = 2; i <= n; ++i) tp[sa[i]] = (rank[sa[i - 1]] == rank[sa[i]] && rank[sa[i - 1] + len] == rank[sa[i] + len] ? p : ++p);
		std::swap(rank, tp);
	}
}
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	SAsort();
	for (int i = 1; i <= n; ++i) printf("%d ", sa[i]);
	return 0;
}