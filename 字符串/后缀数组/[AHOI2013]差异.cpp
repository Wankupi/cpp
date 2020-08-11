#include <cstdio>
#include <algorithm>
#include <cstring>
const int maxn = 500003;
char s[maxn];
int n = 0, m = 0;
int sa[maxn], A[maxn], B[maxn], t[maxn], height[maxn];
int *rank = A, *tp = B;
inline void Qsort() {
	for (int i = 0; i <= m; ++i) t[i] = 0;
	for (int i = 1; i <= n; ++i) ++t[rank[i]];
	for (int i = 1; i <= m; ++i) t[i] += t[i - 1];
	for (int i = n; i; --i) sa[t[rank[tp[i]]]--] = tp[i];
}
void SuffixSort() {
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
void getHeight() {
	for (int i = 1, k = 0; i <= n; ++i) {
		if (rank[i] == 1) { k = height[1] = 0; continue; }
		if (k) --k;
		int j = sa[rank[i] - 1];
		while (i + k <= n && s[i + k] == s[j + k]) ++k;
		height[rank[i]] = k;
	}
}
int L[maxn], R[maxn];
int stack[maxn], top = 0;
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	SuffixSort();
	getHeight();
	stack[1] = 1;
	top = 1;
	for (int i = 2; i <= n; ++i) {
		while (top > 0 && height[stack[top]] > height[i]) R[stack[top--]] = i - 1;
		L[i] = stack[top] + 1;
		stack[++top] = i;
	}
	while (top > 0) R[stack[top--]] = n;
	long long ans = 0;
	for (int i = 2; i <= n; ++i)
		ans += (1ll + i - L[i]) * (1ll + R[i] - i) * height[i];
	ans = (long long)(n) * (n + 1ll) * (n - 1ll) / 2 - 2 * ans;
	printf("%lld", ans);
	return 0;
}
