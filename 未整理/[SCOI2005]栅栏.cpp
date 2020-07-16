#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n = 0, m = 0;
int offer[55], need[1002];
int s[1002];
int Osum = 0;
int mid = 0;
int use[55], waste = 0;
bool dfs(int x, int y) { //需求考虑到第x个（从大到小） 已有木板考虑到第y个
	if (x == 0) return true;
	if (Osum - waste < s[mid]) return false;
	for (int i = y; i <= n; ++i)
		if (offer[i] - use[i] >= need[x]) {
			use[i] += need[x];
			if (offer[i] - use[i] < need[1]) waste += offer[i] - use[i];

			if (need[x] == need[x - 1]) { if (dfs(x - 1, i)) return true; }
			else if (dfs(x - 1, 1)) return true;

			if (offer[i] - use[i] < need[1]) waste -= offer[i] - use[i];
			use[i] -= need[x];
		}
	return false;
}
inline bool cmp(int a, int b) { return b < a; }
int main() {
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d", offer + i);
		Osum += offer[i];
	}
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", need + i);
	sort(offer + 1, offer + m + 1, cmp);
	sort(need + 1, need + n + 1);
	for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + need[i];
	while (s[n] > Osum) --n;
	int l = 1, r = n;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (dfs(mid, 1))
			l = mid + 1;
		else r = mid - 1;
		memset(use, 0, sizeof use);
		waste = 0;
	}
	printf("%d", l - 1);
	return 0;
}