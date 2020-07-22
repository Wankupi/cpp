#include <cstdio>
void swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}
int n = 0;
int a[11], b[11];

void changeL(int cur, int l, int r) { // 向前换
	for (int i = 1; i <= r - l + 1; ++i)
		for (int j = cur + i - 1; j <= l + i - 1; ++j)
			swap(a[j], a[l + i - 1]);
}
/*
changeL( cur , L, R )
inv
changeL (cur, cur + R- L+1,R)
*/
int assess() {
	int ret = 0;
	for (int i = 1; i <= n; ++i)
		ret += (a[i] != a[i - 1] + 1);
	return ret;
}
inline bool check() {
	for (int i = 1; i <= n; ++i) if (a[i] != i) return false;
	return true;
}

int step = 0;
bool dfs(int dep) {
	if (dep == step) return check();
	if (assess() + dep * 3 > step * 3) return false;
	for (int cur = 1; cur <= n; ++cur) {
		while (a[cur] == a[cur - 1] + 1) ++cur;
		for (int l = cur + 1; l <= n; ++l) {
			while (l < n && a[l] == a[l - 1] + 1) ++l;
			for (int r = l; r <= n; ++r) {
				while (r < n && a[r + 1] == a[r] + 1) ++r;
				changeL(cur, l, r);
				if (dfs(dep + 1))
					return true;
				changeL(cur, cur + r - l + 1, r);
			}
		}
	}
	return false;
}

int main() {
	int cnt = 0;
	while(scanf("%d",&n) != EOF) {
		if (n == 0) break;
		++cnt;
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		step = 0;
		if (!check()) {
			for (step = 1; step <= n - 1; ++step)
				if (dfs(0)) {
					break;
				}
		}
		printf("Case %d: %d\n", cnt, step);
	}
	return 0;
}
