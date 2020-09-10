#include <cstdio>
#include <map>
using namespace std;
int const maxn = 1000005;
int n = 0, a[maxn];
map<int, int> tr[maxn << 1];
int cnt = 1, last = 1, len[maxn << 1], fa[maxn << 1];
long long ans = 0;
void insert(int x) {
	int p = last, new_p = ++cnt;
	len[new_p] = len[p] + 1;
	for (; tr[p][x] == 0; p = fa[p]) tr[p][x] = new_p;
	if (p == 0) fa[new_p] = 1;
	else {
		int q = tr[p][x];
		if (len[q] == len[p] + 1) fa[new_p] = q;
		else {
			int nq = ++cnt;
			len[nq] = len[p] + 1;
			tr[nq] = tr[q];
			fa[nq] = fa[q];
			fa[q] = fa[new_p] = nq;
			for (; tr[p][x] == q; p = fa[p]) tr[p][x] = nq;
		}
	}
	ans += len[new_p] - len[fa[new_p]];
	last = new_p;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) {
		insert(a[i]);
		printf("%lld\n", ans);
	}
	return 0;
}
