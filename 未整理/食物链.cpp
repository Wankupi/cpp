#include <cstdio>
#include <cctype>
void read(int &x) {
	char c = getchar(); bool f = false; x = 0;
	while (!isdigit(c)) { if (c == '-') f = true; c = getchar(); }
	while (isdigit(c)) { x = (x << 1) + (x << 3) + c - '0'; c = getchar(); }
	if (f) x = -x;
}
int fa[3 * 50001];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void merge(int x, int y) {
	fa[find(x)] = find(y);
}
int main() {
	int n = 0, k = 0;
	read(n); read(k);
	for (int i = 1; i <= 3 * n; ++i)
		fa[i] = i;
	int ans = 0;
	int opt = 0, x = 0, y = 0;
	for (int i = 1; i <= k; ++i) {
		read(opt); read(x); read(y);
		if (x > n || y > n) { ++ans; continue; }
		if (opt == 1) {//同类
			if (find(x + n) == find(y) || find(x + 2 * n) == find(y)) { ++ans; continue; }
			merge(x, y);
			merge(x + n, y + n);
			merge(x + 2 * n, y + 2 * n);
		}
		else if (opt == 2) {//X eat y
			if (x == y || find(x) == find(y) ||
				find(x + n) == find(y)){
				++ans; continue;
			}
			merge(y + n, x);
			merge(y + 2 * n, x + n);
			merge(x + 2 * n, y);
		}
	}
	printf("%d", ans);
	return 0;
}