#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 40001;
inline int min(int a, int b) { return a < b ? a : b; }
int n = 0, m = 0, block = 0, bc = 0;
int a[maxn], b[maxn], nC = 0; // nC is the number of colors. 
int id[maxn];
inline int L(int i) { return block * (i - 1) + 1; }
inline int R(int i) { return min(block * i, n); }
int p[201][201], s[201][maxn];
inline int which(int pos) { return (pos - 1) / block + 1; }
void read_and_ReNumber() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	int *End = unique(b + 1, b + n + 1);
	nC = End - b - 1;
	for (int i = 1; i <= n; ++i)
		a[i] = lower_bound(b + 1, End, a[i]) - b;
}
inline int CountColorBlock(int l, int r, int C) { return s[r][C] - s[l - 1][C]; }
void PreTask() {
	block = sqrt(n);
	for (int i = 1; i <= n; ++i)
		id[i] = (i <= block ? 1 : id[i - block] + 1);
	bc = id[n];
	// 处理 前i块 第j色 的数量
	for (int i = 1; i <= n; ++i)
		++s[id[i]][a[i]];
	for (int i = 1; i <= bc; ++i)
		for (int j = 1; j <= nC; ++j)
			s[i][j] += s[i - 1][j];
	for (int i = 1; i <= bc; ++i)
		for (int j = i; j <= bc; ++j) {
			p[i][j] = p[i][j - 1];
			for (int k = L(j); k <= R(j); ++k)
				if (CountColorBlock(i, j, a[k]) > CountColorBlock(i, j, p[i][j]) ||
					(CountColorBlock(i, j, a[k]) == CountColorBlock(i, j, p[i][j]) && a[k] < p[i][j]))
					p[i][j] = a[k];
		}
}
int t[maxn];
int query(int l, int r) {
	int ans = 0, times = 0;
	if (id[r] - id[l] <= 1) {
		for (int i = l; i <= r; ++i) ++t[a[i]];
		for (int i = l; i <= r; ++i) {
			if (t[a[i]] > times || (t[a[i]] == times && a[i] < ans)) { ans = a[i]; times = t[a[i]]; }
			--t[a[i]];
		}
	}
	else {
		int ml = id[l] + 1, mr = id[r] - 1;
		ans = p[ml][mr];
		times = CountColorBlock(ml, mr, ans);
		for (int i = l; i <= R(id[l]); ++i) ++t[a[i]];
		for (int i = L(id[r]); i <= r; ++i) ++t[a[i]];
		for (int i = l; i <= R(id[l]); ++i) {
			int cn = t[a[i]] + CountColorBlock(ml, mr, a[i]);
			if (cn > times || (cn == times && a[i] < ans)) { ans = a[i]; times = cn; }
			--t[a[i]];
		}
		for (int i = L(id[r]); i <= r; ++i) {
			int cn = t[a[i]] + CountColorBlock(ml, mr, a[i]);
			if (cn > times || (cn == times && a[i] < ans)) { ans = a[i]; times = cn; }
			--t[a[i]];
		}
	}
	return b[ans];
}
int main() {
	read_and_ReNumber();
	PreTask();
	int LastAns = 0, l = 0, r = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &l, &r);
		l = (l + LastAns - 1) % n + 1;
		r = (r + LastAns - 1) % n + 1;
		if (l > r) swap(l, r);
		LastAns = query(l, r);
		printf("%d\n", LastAns);
	}
	return 0;
}