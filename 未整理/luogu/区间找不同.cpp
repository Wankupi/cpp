#include <cstdio>
void read(int &x) {
	x = 0; int c = getchar();
	while (c < '0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
}
const int maxn = 100001;
int n = 0, q = 0;
int a[maxn], v[maxn], maxL[maxn];
inline int max(int a, int b) { return a < b ? b : a; }
int main() {
	read(n); read(q);
	for (int i = 1; i <= n; ++i)
		read(a[i]);
	for (int i = 1; i <= n; ++i) {
		maxL[i] = max(v[a[i]], maxL[i - 1]);
		v[a[i]] = i;
	}
	int l = 0, r = 0;
	for (int i = 1; i <= q; ++i) {
		read(l); read(r);
		puts(maxL[r] < l ? "Yes" : "No");
	}
	return 0;
}